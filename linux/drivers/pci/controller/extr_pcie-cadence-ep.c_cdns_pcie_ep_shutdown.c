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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct cdns_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdns_pcie_disable_phy (struct cdns_pcie*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct cdns_pcie* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int pm_runtime_put_sync (struct device*) ; 

__attribute__((used)) static void cdns_pcie_ep_shutdown(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct cdns_pcie *pcie = dev_get_drvdata(dev);
	int ret;

	ret = pm_runtime_put_sync(dev);
	if (ret < 0)
		dev_dbg(dev, "pm_runtime_put_sync failed\n");

	pm_runtime_disable(dev);

	cdns_pcie_disable_phy(pcie);
}