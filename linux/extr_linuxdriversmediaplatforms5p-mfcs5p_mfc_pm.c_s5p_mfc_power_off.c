#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_clocks; int /*<<< orphan*/  device; int /*<<< orphan*/ * clocks; int /*<<< orphan*/  clock_gate; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 TYPE_1__* pm ; 
 int pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

int s5p_mfc_power_off(void)
{
	int i;

	/* finish software clock gating */
	clk_enable(pm->clock_gate);

	for (i = 0; i < pm->num_clocks; i++)
		clk_disable_unprepare(pm->clocks[i]);

	return pm_runtime_put_sync(pm->device);
}