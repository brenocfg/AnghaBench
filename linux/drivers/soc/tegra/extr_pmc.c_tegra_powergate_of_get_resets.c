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
struct tegra_powergate {int /*<<< orphan*/  reset; TYPE_1__* pmc; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  of_reset_control_array_get_exclusive_released (struct device_node*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int reset_control_acquire (int /*<<< orphan*/ ) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_powergate_of_get_resets(struct tegra_powergate *pg,
					 struct device_node *np, bool off)
{
	struct device *dev = pg->pmc->dev;
	int err;

	pg->reset = of_reset_control_array_get_exclusive_released(np);
	if (IS_ERR(pg->reset)) {
		err = PTR_ERR(pg->reset);
		dev_err(dev, "failed to get device resets: %d\n", err);
		return err;
	}

	err = reset_control_acquire(pg->reset);
	if (err < 0) {
		pr_err("failed to acquire resets: %d\n", err);
		goto out;
	}

	if (off) {
		err = reset_control_assert(pg->reset);
	} else {
		err = reset_control_deassert(pg->reset);
		if (err < 0)
			goto out;

		reset_control_release(pg->reset);
	}

out:
	if (err) {
		reset_control_release(pg->reset);
		reset_control_put(pg->reset);
	}

	return err;
}