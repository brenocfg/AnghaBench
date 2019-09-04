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
struct gic_chip_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct gic_chip_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  gic_cpu_save (struct gic_chip_data*) ; 
 int /*<<< orphan*/  gic_dist_save (struct gic_chip_data*) ; 
 int pm_clk_suspend (struct device*) ; 

__attribute__((used)) static int gic_runtime_suspend(struct device *dev)
{
	struct gic_chip_data *gic = dev_get_drvdata(dev);

	gic_dist_save(gic);
	gic_cpu_save(gic);

	return pm_clk_suspend(dev);
}