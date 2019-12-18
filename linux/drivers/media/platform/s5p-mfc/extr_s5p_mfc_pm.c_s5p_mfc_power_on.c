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
struct TYPE_2__ {int num_clocks; int /*<<< orphan*/  device; int /*<<< orphan*/ * clocks; int /*<<< orphan*/  clock_gate; int /*<<< orphan*/ * clk_names; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pm ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 

int s5p_mfc_power_on(void)
{
	int i, ret = 0;

	ret = pm_runtime_get_sync(pm->device);
	if (ret < 0)
		return ret;

	/* clock control */
	for (i = 0; i < pm->num_clocks; i++) {
		ret = clk_prepare_enable(pm->clocks[i]);
		if (ret < 0) {
			mfc_err("clock prepare failed for clock: %s\n",
				pm->clk_names[i]);
			i++;
			goto err;
		}
	}

	/* prepare for software clock gating */
	clk_disable(pm->clock_gate);

	return 0;
err:
	while (--i > 0)
		clk_disable_unprepare(pm->clocks[i]);
	pm_runtime_put(pm->device);
	return ret;
}