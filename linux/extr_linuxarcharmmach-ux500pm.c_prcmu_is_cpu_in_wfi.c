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
 int /*<<< orphan*/  PRCM_ARM_WFI_STANDBY ; 
 int PRCM_ARM_WFI_STANDBY_WFI0 ; 
 int PRCM_ARM_WFI_STANDBY_WFI1 ; 
 int readl (int /*<<< orphan*/ ) ; 

bool prcmu_is_cpu_in_wfi(int cpu)
{
	return readl(PRCM_ARM_WFI_STANDBY) &
		(cpu ? PRCM_ARM_WFI_STANDBY_WFI1 : PRCM_ARM_WFI_STANDBY_WFI0);
}