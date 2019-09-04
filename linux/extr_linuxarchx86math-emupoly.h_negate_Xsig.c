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
typedef  int /*<<< orphan*/  Xsig ;

/* Variables and functions */

__attribute__((used)) static inline void negate_Xsig(Xsig *x)
{
	asm volatile ("movl %1,%%esi;\n"
		      "xorl %%ecx,%%ecx;\n"
		      "movl %%ecx,%%eax; subl (%%esi),%%eax; movl %%eax,(%%esi);\n"
		      "movl %%ecx,%%eax; sbbl 4(%%esi),%%eax; movl %%eax,4(%%esi);\n"
		      "movl %%ecx,%%eax; sbbl 8(%%esi),%%eax; movl %%eax,8(%%esi);\n":"=g"
		      (*x):"g"(x):"si", "ax", "cx");
}