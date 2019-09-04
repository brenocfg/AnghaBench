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
typedef  int u32 ;

/* Variables and functions */
 int HID0_DOZE ; 
 int HID0_NAP ; 
 int HID0_SLEEP ; 
 int MSR_WE ; 
 int /*<<< orphan*/  SPRN_HID0 ; 
 int mfmsr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mpc85xx_cpu_die(int cpu)
{
	u32 tmp;

	tmp = (mfspr(SPRN_HID0) & ~(HID0_DOZE|HID0_SLEEP)) | HID0_NAP;
	mtspr(SPRN_HID0, tmp);

	/* Enter NAP mode. */
	tmp = mfmsr();
	tmp |= MSR_WE;
	asm volatile(
		"msync\n"
		"mtmsr %0\n"
		"isync\n"
		:
		: "r" (tmp));
}