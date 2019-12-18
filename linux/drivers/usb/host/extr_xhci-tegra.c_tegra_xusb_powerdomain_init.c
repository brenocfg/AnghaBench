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
struct tegra_xusb {void* genpd_dl_ss; void* genpd_dev_ss; void* genpd_dl_host; void* genpd_dev_host; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DL_FLAG_PM_RUNTIME ; 
 int DL_FLAG_STATELESS ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* dev_pm_domain_attach_by_name (struct device*,char*) ; 
 void* device_link_add (struct device*,void*,int) ; 

__attribute__((used)) static int tegra_xusb_powerdomain_init(struct device *dev,
				       struct tegra_xusb *tegra)
{
	int err;

	tegra->genpd_dev_host = dev_pm_domain_attach_by_name(dev, "xusb_host");
	if (IS_ERR(tegra->genpd_dev_host)) {
		err = PTR_ERR(tegra->genpd_dev_host);
		dev_err(dev, "failed to get host pm-domain: %d\n", err);
		return err;
	}

	tegra->genpd_dev_ss = dev_pm_domain_attach_by_name(dev, "xusb_ss");
	if (IS_ERR(tegra->genpd_dev_ss)) {
		err = PTR_ERR(tegra->genpd_dev_ss);
		dev_err(dev, "failed to get superspeed pm-domain: %d\n", err);
		return err;
	}

	tegra->genpd_dl_host = device_link_add(dev, tegra->genpd_dev_host,
					       DL_FLAG_PM_RUNTIME |
					       DL_FLAG_STATELESS);
	if (!tegra->genpd_dl_host) {
		dev_err(dev, "adding host device link failed!\n");
		return -ENODEV;
	}

	tegra->genpd_dl_ss = device_link_add(dev, tegra->genpd_dev_ss,
					     DL_FLAG_PM_RUNTIME |
					     DL_FLAG_STATELESS);
	if (!tegra->genpd_dl_ss) {
		dev_err(dev, "adding superspeed device link failed!\n");
		return -ENODEV;
	}

	return 0;
}