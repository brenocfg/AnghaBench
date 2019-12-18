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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_INTERRUPT ; 
 int THERM_INT_THRESHOLD0_ENABLE ; 
 int THERM_INT_THRESHOLD1_ENABLE ; 
 int THERM_MASK_THRESHOLD0 ; 
 int THERM_MASK_THRESHOLD1 ; 
 int THERM_SHIFT_THRESHOLD0 ; 
 int THERM_SHIFT_THRESHOLD1 ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void enable_pkg_thres_interrupt(void)
{
	u8 thres_0, thres_1;
	u32 l, h;

	rdmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
	/* only enable/disable if it had valid threshold value */
	thres_0 = (l & THERM_MASK_THRESHOLD0) >> THERM_SHIFT_THRESHOLD0;
	thres_1 = (l & THERM_MASK_THRESHOLD1) >> THERM_SHIFT_THRESHOLD1;
	if (thres_0)
		l |= THERM_INT_THRESHOLD0_ENABLE;
	if (thres_1)
		l |= THERM_INT_THRESHOLD1_ENABLE;
	wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
}