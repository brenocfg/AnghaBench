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
struct tegra_xusb {int /*<<< orphan*/  genpd_dev_host; int /*<<< orphan*/  genpd_dev_ss; scalar_t__ genpd_dl_host; scalar_t__ genpd_dl_ss; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_domain_detach (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_link_del (scalar_t__) ; 

__attribute__((used)) static void tegra_xusb_powerdomain_remove(struct device *dev,
					  struct tegra_xusb *tegra)
{
	if (tegra->genpd_dl_ss)
		device_link_del(tegra->genpd_dl_ss);
	if (tegra->genpd_dl_host)
		device_link_del(tegra->genpd_dl_host);
	if (!IS_ERR_OR_NULL(tegra->genpd_dev_ss))
		dev_pm_domain_detach(tegra->genpd_dev_ss, true);
	if (!IS_ERR_OR_NULL(tegra->genpd_dev_host))
		dev_pm_domain_detach(tegra->genpd_dev_host, true);
}