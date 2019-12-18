#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct imx_pm_domain* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct imx_pm_domain {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM_GENERIC_DOMAINS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_pgc_put_clocks (struct imx_pm_domain*) ; 
 int /*<<< orphan*/  of_genpd_del_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_genpd_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_pgc_power_domain_remove(struct platform_device *pdev)
{
	struct imx_pm_domain *domain = pdev->dev.platform_data;

	if (IS_ENABLED(CONFIG_PM_GENERIC_DOMAINS)) {
		of_genpd_del_provider(pdev->dev.of_node);
		pm_genpd_remove(&domain->base);
		imx_pgc_put_clocks(domain);
	}

	return 0;
}