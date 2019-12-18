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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct pci_host_bridge {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  axi_offset; } ;
struct iproc_pcie {int type; int need_ob_cfg; int /*<<< orphan*/  map_irq; int /*<<< orphan*/  phy; scalar_t__ need_ib_cfg; TYPE_1__ ob; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  base; struct device* dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
typedef  enum iproc_pcie_type { ____Placeholder_iproc_pcie_type } iproc_pcie_type ;

/* Variables and functions */
 int ENOMEM ; 
#define  IPROC_PCIE_PAXC 129 
#define  IPROC_PCIE_PAXC_V2 128 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_of_pci_get_host_bridge_resources (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pci_host_bridge* devm_pci_alloc_host_bridge (struct device*,int) ; 
 int /*<<< orphan*/  devm_pci_remap_cfgspace (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_optional_get (struct device*,char*) ; 
 int iproc_pcie_setup (struct iproc_pcie*,int /*<<< orphan*/ *) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_irq_parse_and_map_pci ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_resource_list (int /*<<< orphan*/ *) ; 
 struct iproc_pcie* pci_host_bridge_priv (struct pci_host_bridge*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iproc_pcie*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  resources ; 

__attribute__((used)) static int iproc_pcie_pltfm_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct iproc_pcie *pcie;
	struct device_node *np = dev->of_node;
	struct resource reg;
	resource_size_t iobase = 0;
	LIST_HEAD(resources);
	struct pci_host_bridge *bridge;
	int ret;

	bridge = devm_pci_alloc_host_bridge(dev, sizeof(*pcie));
	if (!bridge)
		return -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);

	pcie->dev = dev;
	pcie->type = (enum iproc_pcie_type) of_device_get_match_data(dev);

	ret = of_address_to_resource(np, 0, &reg);
	if (ret < 0) {
		dev_err(dev, "unable to obtain controller resources\n");
		return ret;
	}

	pcie->base = devm_pci_remap_cfgspace(dev, reg.start,
					     resource_size(&reg));
	if (!pcie->base) {
		dev_err(dev, "unable to map controller registers\n");
		return -ENOMEM;
	}
	pcie->base_addr = reg.start;

	if (of_property_read_bool(np, "brcm,pcie-ob")) {
		u32 val;

		ret = of_property_read_u32(np, "brcm,pcie-ob-axi-offset",
					   &val);
		if (ret) {
			dev_err(dev,
				"missing brcm,pcie-ob-axi-offset property\n");
			return ret;
		}
		pcie->ob.axi_offset = val;
		pcie->need_ob_cfg = true;
	}

	/*
	 * DT nodes are not used by all platforms that use the iProc PCIe
	 * core driver. For platforms that require explicit inbound mapping
	 * configuration, "dma-ranges" would have been present in DT
	 */
	pcie->need_ib_cfg = of_property_read_bool(np, "dma-ranges");

	/* PHY use is optional */
	pcie->phy = devm_phy_optional_get(dev, "pcie-phy");
	if (IS_ERR(pcie->phy))
		return PTR_ERR(pcie->phy);

	ret = devm_of_pci_get_host_bridge_resources(dev, 0, 0xff, &resources,
						    &iobase);
	if (ret) {
		dev_err(dev, "unable to get PCI host bridge resources\n");
		return ret;
	}

	/* PAXC doesn't support legacy IRQs, skip mapping */
	switch (pcie->type) {
	case IPROC_PCIE_PAXC:
	case IPROC_PCIE_PAXC_V2:
		break;
	default:
		pcie->map_irq = of_irq_parse_and_map_pci;
	}

	ret = iproc_pcie_setup(pcie, &resources);
	if (ret) {
		dev_err(dev, "PCIe controller setup failed\n");
		pci_free_resource_list(&resources);
		return ret;
	}

	platform_set_drvdata(pdev, pcie);
	return 0;
}