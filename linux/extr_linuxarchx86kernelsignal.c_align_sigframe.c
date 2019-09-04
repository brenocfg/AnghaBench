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

/* Variables and functions */
 int round_down (unsigned long,int) ; 

__attribute__((used)) static unsigned long align_sigframe(unsigned long sp)
{
#ifdef CONFIG_X86_32
	/*
	 * Align the stack pointer according to the i386 ABI,
	 * i.e. so that on function entry ((sp + 4) & 15) == 0.
	 */
	sp = ((sp + 4) & -16ul) - 4;
#else /* !CONFIG_X86_32 */
	sp = round_down(sp, 16) - 8;
#endif
	return sp;
}