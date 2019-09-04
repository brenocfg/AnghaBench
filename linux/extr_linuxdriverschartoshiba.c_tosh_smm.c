#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SMMRegisters ;

/* Variables and functions */

int tosh_smm(SMMRegisters *regs)
{
	int eax;

	asm ("# load the values into the registers\n\t" \
		"pushl %%eax\n\t" \
		"movl 0(%%eax),%%edx\n\t" \
		"push %%edx\n\t" \
		"movl 4(%%eax),%%ebx\n\t" \
		"movl 8(%%eax),%%ecx\n\t" \
		"movl 12(%%eax),%%edx\n\t" \
		"movl 16(%%eax),%%esi\n\t" \
		"movl 20(%%eax),%%edi\n\t" \
		"popl %%eax\n\t" \
		"# call the System Management mode\n\t" \
		"inb $0xb2,%%al\n\t"
		"# fill out the memory with the values in the registers\n\t" \
		"xchgl %%eax,(%%esp)\n\t"
		"movl %%ebx,4(%%eax)\n\t" \
		"movl %%ecx,8(%%eax)\n\t" \
		"movl %%edx,12(%%eax)\n\t" \
		"movl %%esi,16(%%eax)\n\t" \
		"movl %%edi,20(%%eax)\n\t" \
		"popl %%edx\n\t" \
		"movl %%edx,0(%%eax)\n\t" \
		"# setup the return value to the carry flag\n\t" \
		"lahf\n\t" \
		"shrl $8,%%eax\n\t" \
		"andl $1,%%eax\n" \
		: "=a" (eax)
		: "a" (regs)
		: "%ebx", "%ecx", "%edx", "%esi", "%edi", "memory");

	return eax;
}