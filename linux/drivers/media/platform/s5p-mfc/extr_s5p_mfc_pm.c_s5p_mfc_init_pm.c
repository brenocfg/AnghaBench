#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_clocks; int /*<<< orphan*/ * device; int /*<<< orphan*/ ** clocks; int /*<<< orphan*/ * clock_gate; int /*<<< orphan*/ * clk_names; } ;
struct s5p_mfc_dev {TYPE_2__* variant; TYPE_1__* plat_dev; TYPE_3__ pm; } ;
struct TYPE_5__ {int num_clocks; scalar_t__ use_clock_gating; int /*<<< orphan*/ * clk_names; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_ref ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*,int /*<<< orphan*/ ) ; 
 struct s5p_mfc_dev* p_dev ; 
 TYPE_3__* pm ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 

int s5p_mfc_init_pm(struct s5p_mfc_dev *dev)
{
	int i;

	pm = &dev->pm;
	p_dev = dev;

	pm->num_clocks = dev->variant->num_clocks;
	pm->clk_names = dev->variant->clk_names;
	pm->device = &dev->plat_dev->dev;
	pm->clock_gate = NULL;

	/* clock control */
	for (i = 0; i < pm->num_clocks; i++) {
		pm->clocks[i] = devm_clk_get(pm->device, pm->clk_names[i]);
		if (IS_ERR(pm->clocks[i])) {
			/* additional clocks are optional */
			if (i && PTR_ERR(pm->clocks[i]) == -ENOENT) {
				pm->clocks[i] = NULL;
				continue;
			}
			mfc_err("Failed to get clock: %s\n",
				pm->clk_names[i]);
			return PTR_ERR(pm->clocks[i]);
		}
	}

	if (dev->variant->use_clock_gating)
		pm->clock_gate = pm->clocks[0];

	pm_runtime_enable(pm->device);
	atomic_set(&clk_ref, 0);
	return 0;
}