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
struct gic_clk_data {int /*<<< orphan*/  num_clocks; } ;
struct gic_chip_pm {int /*<<< orphan*/  clks; struct gic_clk_data* clk_data; struct gic_chip_data* chip_data; } ;
struct gic_chip_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct gic_chip_pm* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gic_cpu_restore (struct gic_chip_data*) ; 
 int /*<<< orphan*/  gic_dist_restore (struct gic_chip_data*) ; 

__attribute__((used)) static int gic_runtime_resume(struct device *dev)
{
	struct gic_chip_pm *chip_pm = dev_get_drvdata(dev);
	struct gic_chip_data *gic = chip_pm->chip_data;
	const struct gic_clk_data *data = chip_pm->clk_data;
	int ret;

	ret = clk_bulk_prepare_enable(data->num_clocks, chip_pm->clks);
	if (ret) {
		dev_err(dev, "clk_enable failed: %d\n", ret);
		return ret;
	}

	/*
	 * On the very first resume, the pointer to chip_pm->chip_data
	 * will be NULL and this is intentional, because we do not
	 * want to restore the GIC on the very first resume. So if
	 * the pointer is not valid just return.
	 */
	if (!gic)
		return 0;

	gic_dist_restore(gic);
	gic_cpu_restore(gic);

	return 0;
}