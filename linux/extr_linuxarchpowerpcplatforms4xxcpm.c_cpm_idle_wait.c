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
 unsigned long MSR_CE ; 
 unsigned long MSR_DE ; 
 unsigned long MSR_EE ; 
 unsigned long MSR_WE ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long mfmsr () ; 
 int /*<<< orphan*/  mtmsr (unsigned long) ; 

__attribute__((used)) static void cpm_idle_wait(void)
{
	unsigned long msr_save;

	/* save off initial state */
	msr_save = mfmsr();
	/* sync required when CPM0_ER[CPU] is set */
	mb();
	/* set wait state MSR */
	mtmsr(msr_save|MSR_WE|MSR_EE|MSR_CE|MSR_DE);
	isync();
	/* return to initial state */
	mtmsr(msr_save);
	isync();
}