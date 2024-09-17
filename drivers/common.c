/*
 *
 *		common.c
 *		常见设备驱动
 *
 *		2024/6/27 By Rainy101112
 *		基于 GPL-3.0 开源协议
 *		Copyright © 2020 ViudiraTech，保留所有权利。
 *
 */

#include "common.h"

/* 端口写（8位） */
inline void outb(uint16_t port, uint8_t value)
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

/* 端口读（8位） */
inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

/* 端口写（16位） */
inline void outw(uint16_t port, uint16_t value)
{
	asm volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

/* 端口读（16位） */
inline uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

/* 端口写（32位） */
inline void outl(uint16_t port, uint32_t value)
{
	asm volatile("outl %1, %0" : : "dN"(port), "a"(value));
}

/* 端口读（32位） */
inline uint32_t inl(uint16_t port)
{
	uint32_t ret;
	asm volatile("inl %1, %0" : "=a"(ret) : "dN"(port));
	return ret;
}

/* 从I/O端口批量地读取数据到内存（16位） */
inline void insw(uint16_t port, void *buf, unsigned long n)
{
	asm volatile("cld; rep; insw"
                 : "+D"(buf),
                 "+c"(n)
                 : "d"(port));
}

/* 从内存批量地写入数据到I/O端口（16位） */
inline void outsw(uint16_t port, const void *buf, unsigned long n)
{
	asm volatile("cld; rep; outsw"
                 : "+S"(buf),
                 "+c"(n)
                 : "d"(port));
}

/* 从I/O端口批量地读取数据到内存（32位） */
inline void insl(uint32_t port, void *addr, int cnt)
{
	asm volatile("cld;"
                 "repne; insl;"
                 : "=D" (addr), "=c" (cnt)
                 : "d" (port), "0" (addr), "1" (cnt)
                 : "memory", "cc");
}

/* 从内存批量地写入数据到I/O端口（32位） */
inline void outsl(uint32_t port, const void *addr, int cnt)
{
	asm volatile("cld;"
                 "repne; outsl;"
                 : "=S" (addr), "=c" (cnt)
                 : "d" (port), "0" (addr), "1" (cnt)
                 : "memory", "cc");
}

/* 获取当前的CR0寄存器的值 */
uint32_t get_cr0(void)
{
	uint32_t cr0;
	asm volatile("mov %%cr0, %0" : "=r"(cr0));
	return cr0;
}

/* 将值写入CR0寄存器 */
void set_cr0(uint32_t cr0)
{
	asm volatile("mov %0, %%cr0" : : "r"(cr0));
}

/* 开启中断 */
void enable_intr(void)
{
	asm volatile("sti");
}

/* 关闭中断 */
void disable_intr(void)
{
	asm volatile("cli" ::: "memory");
}

/* 内核停机 */
void krn_halt(void)
{
	disable_intr();
	while(1) {asm("hlt");}
}
