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
struct TYPE_2__ {struct device* parent; } ;
struct pci_host_bridge {int /*<<< orphan*/  swizzle_irq; int /*<<< orphan*/  map_irq; int /*<<< orphan*/ * ops; scalar_t__ busnr; struct advk_pcie* sysdata; TYPE_1__ dev; int /*<<< orphan*/  windows; } ;
struct advk_pcie {int /*<<< orphan*/  resources; int /*<<< orphan*/  base; struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_NO_THREAD ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int advk_pcie_init_irq_domain (struct advk_pcie*) ; 
 int advk_pcie_init_msi_irq_domain (struct advk_pcie*) ; 
 int /*<<< orphan*/  advk_pcie_irq_handler ; 
 int /*<<< orphan*/  advk_pcie_ops ; 
 int advk_pcie_parse_request_of_pci_ranges (struct advk_pcie*) ; 
 int /*<<< orphan*/  advk_pcie_remove_irq_domain (struct advk_pcie*) ; 
 int /*<<< orphan*/  advk_pcie_remove_msi_irq_domain (struct advk_pcie*) ; 
 int /*<<< orphan*/  advk_pcie_setup_hw (struct advk_pcie*) ; 
 int /*<<< orphan*/  advk_sw_pci_bridge_init (struct advk_pcie*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct pci_host_bridge* devm_pci_alloc_host_bridge (struct device*,int) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int,char*,struct advk_pcie*) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_irq_parse_and_map_pci ; 
 int /*<<< orphan*/  pci_common_swizzle ; 
 struct advk_pcie* pci_host_bridge_priv (struct pci_host_bridge*) ; 
 int pci_host_probe (struct pci_host_bridge*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int advk_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct advk_pcie *pcie;
	struct resource *res;
	struct pci_host_bridge *bridge;
	int ret, irq;

	bridge = devm_pci_alloc_host_bridge(dev, sizeof(struct advk_pcie));
	if (!bridge)
		return -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);
	pcie->pdev = pdev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pcie->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(pcie->base))
		return PTR_ERR(pcie->base);

	irq = platform_get_irq(pdev, 0);
	ret = devm_request_irq(dev, irq, advk_pcie_irq_handler,
			       IRQF_SHARED | IRQF_NO_THREAD, "advk-pcie",
			       pcie);
	if (ret) {
		dev_err(dev, "Failed to register interrupt\n");
		return ret;
	}

	ret = advk_pcie_parse_request_of_pci_ranges(pcie);
	if (ret) {
		dev_err(dev, "Failed to parse resources\n");
		return ret;
	}

	advk_pcie_setup_hw(pcie);

	advk_sw_pci_bridge_init(pcie);

	ret = advk_pcie_init_irq_domain(pcie);
	if (ret) {
		dev_err(dev, "Failed to initialize irq\n");
		return ret;
	}

	ret = advk_pcie_init_msi_irq_domain(pcie);
	if (ret) {
		dev_err(dev, "Failed to initialize irq\n");
		advk_pcie_remove_irq_domain(pcie);
		return ret;
	}

	list_splice_init(&pcie->resources, &bridge->windows);
	bridge->dev.parent = dev;
	bridge->sysdata = pcie;
	bridge->busnr = 0;
	bridge->ops = &advk_pcie_ops;
	bridge->map_irq = of_irq_parse_and_map_pci;
	bridge->swizzle_irq = pci_common_swizzle;

	ret = pci_host_probe(bridge);
	if (ret < 0) {
		advk_pcie_remove_msi_irq_domain(pcie);
		advk_pcie_remove_irq_domain(pcie);
		return ret;
	}

	return 0;
}