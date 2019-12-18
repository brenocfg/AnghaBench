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
struct imx6_pcie {void* pd_pcie_phy; void* pd_pcie; } ;
struct device_link {int dummy; } ;
struct device {scalar_t__ pm_domain; } ;

/* Variables and functions */
 int DL_FLAG_PM_RUNTIME ; 
 int DL_FLAG_RPM_ACTIVE ; 
 int DL_FLAG_STATELESS ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct imx6_pcie* dev_get_drvdata (struct device*) ; 
 void* dev_pm_domain_attach_by_name (struct device*,char*) ; 
 struct device_link* device_link_add (struct device*,void*,int) ; 

__attribute__((used)) static int imx6_pcie_attach_pd(struct device *dev)
{
	struct imx6_pcie *imx6_pcie = dev_get_drvdata(dev);
	struct device_link *link;

	/* Do nothing when in a single power domain */
	if (dev->pm_domain)
		return 0;

	imx6_pcie->pd_pcie = dev_pm_domain_attach_by_name(dev, "pcie");
	if (IS_ERR(imx6_pcie->pd_pcie))
		return PTR_ERR(imx6_pcie->pd_pcie);
	/* Do nothing when power domain missing */
	if (!imx6_pcie->pd_pcie)
		return 0;
	link = device_link_add(dev, imx6_pcie->pd_pcie,
			DL_FLAG_STATELESS |
			DL_FLAG_PM_RUNTIME |
			DL_FLAG_RPM_ACTIVE);
	if (!link) {
		dev_err(dev, "Failed to add device_link to pcie pd.\n");
		return -EINVAL;
	}

	imx6_pcie->pd_pcie_phy = dev_pm_domain_attach_by_name(dev, "pcie_phy");
	if (IS_ERR(imx6_pcie->pd_pcie_phy))
		return PTR_ERR(imx6_pcie->pd_pcie_phy);

	link = device_link_add(dev, imx6_pcie->pd_pcie_phy,
			DL_FLAG_STATELESS |
			DL_FLAG_PM_RUNTIME |
			DL_FLAG_RPM_ACTIVE);
	if (!link) {
		dev_err(dev, "Failed to add device_link to pcie_phy pd.\n");
		return -EINVAL;
	}

	return 0;
}