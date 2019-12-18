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
struct imx_pm_domain {int /*<<< orphan*/ * supply; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (struct device*,char*) ; 
 int imx_pgc_get_clocks (struct device*,struct imx_pm_domain*) ; 

__attribute__((used)) static int imx_pgc_parse_dt(struct device *dev, struct imx_pm_domain *domain)
{
	/* try to get the domain supply regulator */
	domain->supply = devm_regulator_get_optional(dev, "power");
	if (IS_ERR(domain->supply)) {
		if (PTR_ERR(domain->supply) == -ENODEV)
			domain->supply = NULL;
		else
			return PTR_ERR(domain->supply);
	}

	/* try to get all clocks needed for reset propagation */
	return imx_pgc_get_clocks(dev, domain);
}