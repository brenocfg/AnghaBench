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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_core_pmu_counters () ; 
 int /*<<< orphan*/  disable_nest_pmu_counters () ; 

__attribute__((used)) static void opal_imc_counters_shutdown(struct platform_device *pdev)
{
	/*
	 * Function only stops the engines which is bare minimum.
	 * TODO: Need to handle proper memory cleanup and pmu
	 * unregister.
	 */
	disable_nest_pmu_counters();
	disable_core_pmu_counters();
}