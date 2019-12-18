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
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_INTERRUPT ; 
 int THERM_INT_THRESHOLD0_ENABLE ; 
 int THERM_INT_THRESHOLD1_ENABLE ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void disable_pkg_thres_interrupt(void)
{
	u32 l, h;

	rdmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);

	l &= ~(THERM_INT_THRESHOLD0_ENABLE | THERM_INT_THRESHOLD1_ENABLE);
	wrmsr(MSR_IA32_PACKAGE_THERM_INTERRUPT, l, h);
}