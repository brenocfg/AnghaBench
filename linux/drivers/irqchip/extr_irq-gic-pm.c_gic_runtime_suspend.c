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
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gic_chip_pm* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gic_cpu_save (struct gic_chip_data*) ; 
 int /*<<< orphan*/  gic_dist_save (struct gic_chip_data*) ; 

__attribute__((used)) static int gic_runtime_suspend(struct device *dev)
{
	struct gic_chip_pm *chip_pm = dev_get_drvdata(dev);
	struct gic_chip_data *gic = chip_pm->chip_data;
	const struct gic_clk_data *data = chip_pm->clk_data;

	gic_dist_save(gic);
	gic_cpu_save(gic);

	clk_bulk_disable_unprepare(data->num_clocks, chip_pm->clks);

	return 0;
}