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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct altera_pcie {int irq; void* hip_base; TYPE_1__* pcie_data; void* cra_base; struct platform_device* pdev; } ;
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ALTERA_PCIE_V2 ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  altera_pcie_isr ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct altera_pcie*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int altera_pcie_parse_dt(struct altera_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	struct platform_device *pdev = pcie->pdev;
	struct resource *cra;
	struct resource *hip;

	cra = platform_get_resource_byname(pdev, IORESOURCE_MEM, "Cra");
	pcie->cra_base = devm_ioremap_resource(dev, cra);
	if (IS_ERR(pcie->cra_base))
		return PTR_ERR(pcie->cra_base);

	if (pcie->pcie_data->version == ALTERA_PCIE_V2) {
		hip = platform_get_resource_byname(pdev, IORESOURCE_MEM, "Hip");
		pcie->hip_base = devm_ioremap_resource(&pdev->dev, hip);
		if (IS_ERR(pcie->hip_base))
			return PTR_ERR(pcie->hip_base);
	}

	/* setup IRQ */
	pcie->irq = platform_get_irq(pdev, 0);
	if (pcie->irq < 0) {
		dev_err(dev, "failed to get IRQ: %d\n", pcie->irq);
		return pcie->irq;
	}

	irq_set_chained_handler_and_data(pcie->irq, altera_pcie_isr, pcie);
	return 0;
}