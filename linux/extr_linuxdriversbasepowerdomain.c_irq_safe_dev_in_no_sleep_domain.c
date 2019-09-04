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
struct generic_pm_domain {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn_once (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genpd_is_always_on (struct generic_pm_domain const*) ; 
 int /*<<< orphan*/  genpd_is_irq_safe (struct generic_pm_domain const*) ; 
 scalar_t__ pm_runtime_is_irq_safe (struct device*) ; 

__attribute__((used)) static inline bool irq_safe_dev_in_no_sleep_domain(struct device *dev,
		const struct generic_pm_domain *genpd)
{
	bool ret;

	ret = pm_runtime_is_irq_safe(dev) && !genpd_is_irq_safe(genpd);

	/*
	 * Warn once if an IRQ safe device is attached to a no sleep domain, as
	 * to indicate a suboptimal configuration for PM. For an always on
	 * domain this isn't case, thus don't warn.
	 */
	if (ret && !genpd_is_always_on(genpd))
		dev_warn_once(dev, "PM domain %s will not be powered off\n",
				genpd->name);

	return ret;
}