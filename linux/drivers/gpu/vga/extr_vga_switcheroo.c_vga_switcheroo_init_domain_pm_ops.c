#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  runtime_resume; int /*<<< orphan*/  runtime_suspend; } ;
struct dev_pm_domain {TYPE_2__ ops; } ;
struct TYPE_3__ {TYPE_2__* pm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_pm_domain_set (struct device*,struct dev_pm_domain*) ; 
 int /*<<< orphan*/  vga_switcheroo_runtime_resume ; 
 int /*<<< orphan*/  vga_switcheroo_runtime_suspend ; 

int vga_switcheroo_init_domain_pm_ops(struct device *dev,
				      struct dev_pm_domain *domain)
{
	/* copy over all the bus versions */
	if (dev->bus && dev->bus->pm) {
		domain->ops = *dev->bus->pm;
		domain->ops.runtime_suspend = vga_switcheroo_runtime_suspend;
		domain->ops.runtime_resume = vga_switcheroo_runtime_resume;

		dev_pm_domain_set(dev, domain);
		return 0;
	}
	dev_pm_domain_set(dev, NULL);
	return -EINVAL;
}