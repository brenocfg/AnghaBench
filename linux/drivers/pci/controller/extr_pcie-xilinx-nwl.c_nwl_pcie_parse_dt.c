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
struct platform_device {int dummy; } ;
struct nwl_pcie {int irq_intx; int /*<<< orphan*/  phys_ecam_base; void* ecam_base; int /*<<< orphan*/  phys_pcie_reg_base; void* pcireg_base; int /*<<< orphan*/  phys_breg_base; void* breg_base; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_pci_remap_cfg_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct nwl_pcie*) ; 
 int /*<<< orphan*/  nwl_pcie_leg_handler ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int nwl_pcie_parse_dt(struct nwl_pcie *pcie,
			     struct platform_device *pdev)
{
	struct device *dev = pcie->dev;
	struct resource *res;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "breg");
	pcie->breg_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(pcie->breg_base))
		return PTR_ERR(pcie->breg_base);
	pcie->phys_breg_base = res->start;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pcireg");
	pcie->pcireg_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(pcie->pcireg_base))
		return PTR_ERR(pcie->pcireg_base);
	pcie->phys_pcie_reg_base = res->start;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "cfg");
	pcie->ecam_base = devm_pci_remap_cfg_resource(dev, res);
	if (IS_ERR(pcie->ecam_base))
		return PTR_ERR(pcie->ecam_base);
	pcie->phys_ecam_base = res->start;

	/* Get intx IRQ number */
	pcie->irq_intx = platform_get_irq_byname(pdev, "intx");
	if (pcie->irq_intx < 0) {
		dev_err(dev, "failed to get intx IRQ %d\n", pcie->irq_intx);
		return pcie->irq_intx;
	}

	irq_set_chained_handler_and_data(pcie->irq_intx,
					 nwl_pcie_leg_handler, pcie);

	return 0;
}