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
 scalar_t__ SUN4V_CHIP_NIAGARA4 ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  smp_cross_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sun4v_chip_type ; 
 scalar_t__ tlb_type ; 
 int /*<<< orphan*/  xcall_fetch_glob_pmu ; 
 int /*<<< orphan*/  xcall_fetch_glob_pmu_n4 ; 

void smp_fetch_global_pmu(void)
{
	if (tlb_type == hypervisor &&
	    sun4v_chip_type >= SUN4V_CHIP_NIAGARA4)
		smp_cross_call(&xcall_fetch_glob_pmu_n4, 0, 0, 0);
	else
		smp_cross_call(&xcall_fetch_glob_pmu, 0, 0, 0);
}