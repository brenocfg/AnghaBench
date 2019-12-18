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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct dw_plat_pcie {struct dw_pcie* pci; } ;
struct dw_pcie_ep {int /*<<< orphan*/  addr_size; int /*<<< orphan*/  phys_base; int /*<<< orphan*/ * ops; } ;
struct dw_pcie {int /*<<< orphan*/  dbi_base2; struct dw_pcie_ep ep; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int dw_pcie_ep_init (struct dw_pcie_ep*) ; 
 int /*<<< orphan*/  pcie_ep_ops ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int dw_plat_add_pcie_ep(struct dw_plat_pcie *dw_plat_pcie,
			       struct platform_device *pdev)
{
	int ret;
	struct dw_pcie_ep *ep;
	struct resource *res;
	struct device *dev = &pdev->dev;
	struct dw_pcie *pci = dw_plat_pcie->pci;

	ep = &pci->ep;
	ep->ops = &pcie_ep_ops;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi2");
	pci->dbi_base2 = devm_ioremap_resource(dev, res);
	if (IS_ERR(pci->dbi_base2))
		return PTR_ERR(pci->dbi_base2);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "addr_space");
	if (!res)
		return -EINVAL;

	ep->phys_base = res->start;
	ep->addr_size = resource_size(res);

	ret = dw_pcie_ep_init(ep);
	if (ret) {
		dev_err(dev, "Failed to initialize endpoint\n");
		return ret;
	}
	return 0;
}