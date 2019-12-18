#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; scalar_t__ of_node; struct imx_pm_domain* platform_data; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* power_on ) (TYPE_1__*) ;} ;
struct imx_pm_domain {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM_GENERIC_DOMAINS ; 
 int /*<<< orphan*/  DL_FLAG_AUTOREMOVE_CONSUMER ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_link_add (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int imx_pgc_parse_dt (struct device*,struct imx_pm_domain*) ; 
 int /*<<< orphan*/  imx_pgc_put_clocks (struct imx_pm_domain*) ; 
 int of_genpd_add_provider_simple (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  pm_genpd_init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pm_genpd_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int imx_pgc_power_domain_probe(struct platform_device *pdev)
{
	struct imx_pm_domain *domain = pdev->dev.platform_data;
	struct device *dev = &pdev->dev;
	int ret;

	/* if this PD is associated with a DT node try to parse it */
	if (dev->of_node) {
		ret = imx_pgc_parse_dt(dev, domain);
		if (ret)
			return ret;
	}

	/* initially power on the domain */
	if (domain->base.power_on)
		domain->base.power_on(&domain->base);

	if (IS_ENABLED(CONFIG_PM_GENERIC_DOMAINS)) {
		pm_genpd_init(&domain->base, NULL, false);
		ret = of_genpd_add_provider_simple(dev->of_node, &domain->base);
		if (ret)
			goto genpd_err;
	}

	device_link_add(dev, dev->parent, DL_FLAG_AUTOREMOVE_CONSUMER);

	return 0;

genpd_err:
	pm_genpd_remove(&domain->base);
	imx_pgc_put_clocks(domain);

	return ret;
}