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
 unsigned long mfmsr () ; 
 int /*<<< orphan*/  mtmsr_isync (unsigned long) ; 

void __msr_check_and_clear(unsigned long bits)
{
	unsigned long oldmsr = mfmsr();
	unsigned long newmsr;

	newmsr = oldmsr & ~bits;

#ifdef CONFIG_VSX
	if (cpu_has_feature(CPU_FTR_VSX) && (bits & MSR_FP))
		newmsr &= ~MSR_VSX;
#endif

	if (oldmsr != newmsr)
		mtmsr_isync(newmsr);
}