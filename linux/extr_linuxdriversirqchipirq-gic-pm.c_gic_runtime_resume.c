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
 int /*<<< orphan*/  gic_cpu_restore (struct gic_chip_data*) ; 
 int /*<<< orphan*/  gic_dist_restore (struct gic_chip_data*) ; 
 int pm_clk_resume (struct device*) ; 

__attribute__((used)) static int gic_runtime_resume(struct device *dev)
{
	struct gic_chip_data *gic = dev_get_drvdata(dev);
	int ret;

	ret = pm_clk_resume(dev);
	if (ret)
		return ret;

	/*
	 * On the very first resume, the pointer to the driver data
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