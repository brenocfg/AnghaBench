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
struct ti_sci_pm_domain {struct ti_sci_handle const* ti_sci; } ;
struct ti_sci_handle {int dummy; } ;
struct generic_pm_domain {int dummy; } ;
struct device {int /*<<< orphan*/  pm_domain; } ;

/* Variables and functions */
 struct ti_sci_pm_domain* genpd_to_ti_sci_pd (struct generic_pm_domain*) ; 
 struct generic_pm_domain* pd_to_genpd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct ti_sci_handle *ti_sci_dev_to_sci_handle(struct device *dev)
{
	struct generic_pm_domain *pd = pd_to_genpd(dev->pm_domain);
	struct ti_sci_pm_domain *ti_sci_genpd = genpd_to_ti_sci_pd(pd);

	return ti_sci_genpd->ti_sci;
}