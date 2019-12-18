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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct pcie_port {scalar_t__ msi_irq; int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  elbi_base; } ;
struct dw_pcie {int /*<<< orphan*/  dbi_base; struct pcie_port pp; } ;
struct meson_pcie {TYPE_1__ mem_res; struct dw_pcie pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dw_pcie_host_init (struct pcie_port*) ; 
 int /*<<< orphan*/  meson_pcie_host_ops ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_add_pcie_port(struct meson_pcie *mp,
			       struct platform_device *pdev)
{
	struct dw_pcie *pci = &mp->pci;
	struct pcie_port *pp = &pci->pp;
	struct device *dev = &pdev->dev;
	int ret;

	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		pp->msi_irq = platform_get_irq(pdev, 0);
		if (pp->msi_irq < 0) {
			dev_err(dev, "failed to get MSI IRQ\n");
			return pp->msi_irq;
		}
	}

	pp->ops = &meson_pcie_host_ops;
	pci->dbi_base = mp->mem_res.elbi_base;

	ret = dw_pcie_host_init(pp);
	if (ret) {
		dev_err(dev, "failed to initialize host\n");
		return ret;
	}

	return 0;
}