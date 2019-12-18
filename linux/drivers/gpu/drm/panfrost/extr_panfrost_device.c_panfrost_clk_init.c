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
struct panfrost_device {scalar_t__ clock; scalar_t__ bus_clock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned long) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_clk_get_optional (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int panfrost_clk_init(struct panfrost_device *pfdev)
{
	int err;
	unsigned long rate;

	pfdev->clock = devm_clk_get(pfdev->dev, NULL);
	if (IS_ERR(pfdev->clock)) {
		dev_err(pfdev->dev, "get clock failed %ld\n", PTR_ERR(pfdev->clock));
		return PTR_ERR(pfdev->clock);
	}

	rate = clk_get_rate(pfdev->clock);
	dev_info(pfdev->dev, "clock rate = %lu\n", rate);

	err = clk_prepare_enable(pfdev->clock);
	if (err)
		return err;

	pfdev->bus_clock = devm_clk_get_optional(pfdev->dev, "bus");
	if (IS_ERR(pfdev->bus_clock)) {
		dev_err(pfdev->dev, "get bus_clock failed %ld\n",
			PTR_ERR(pfdev->bus_clock));
		return PTR_ERR(pfdev->bus_clock);
	}

	if (pfdev->bus_clock) {
		rate = clk_get_rate(pfdev->bus_clock);
		dev_info(pfdev->dev, "bus_clock rate = %lu\n", rate);

		err = clk_prepare_enable(pfdev->bus_clock);
		if (err)
			goto disable_clock;
	}

	return 0;

disable_clock:
	clk_disable_unprepare(pfdev->clock);

	return err;
}