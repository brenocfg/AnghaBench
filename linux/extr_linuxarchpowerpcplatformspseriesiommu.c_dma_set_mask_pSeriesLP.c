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
typedef  scalar_t__ u64 ;
struct pci_dev {int dummy; } ;
struct device_node {struct device_node* parent; } ;
struct device {scalar_t__* dma_mask; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  table_group; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 int EIO ; 
 TYPE_1__* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct device_node*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  disable_ddw ; 
 int /*<<< orphan*/  dma_iommu_ops ; 
 int /*<<< orphan*/  dma_nommu_ops ; 
 int /*<<< orphan*/  dma_supported (struct device*,scalar_t__) ; 
 scalar_t__ enable_ddw (struct pci_dev*,struct device_node*) ; 
 int /*<<< orphan*/ * get_dma_ops (struct device*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  set_dma_offset (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  set_dma_ops (struct device*,int /*<<< orphan*/ *) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int dma_set_mask_pSeriesLP(struct device *dev, u64 dma_mask)
{
	bool ddw_enabled = false;
	struct device_node *pdn, *dn;
	struct pci_dev *pdev;
	const __be32 *dma_window = NULL;
	u64 dma_offset;

	if (!dev->dma_mask)
		return -EIO;

	if (!dev_is_pci(dev))
		goto check_mask;

	pdev = to_pci_dev(dev);

	/* only attempt to use a new window if 64-bit DMA is requested */
	if (!disable_ddw && dma_mask == DMA_BIT_MASK(64)) {
		dn = pci_device_to_OF_node(pdev);
		dev_dbg(dev, "node is %pOF\n", dn);

		/*
		 * the device tree might contain the dma-window properties
		 * per-device and not necessarily for the bus. So we need to
		 * search upwards in the tree until we either hit a dma-window
		 * property, OR find a parent with a table already allocated.
		 */
		for (pdn = dn; pdn && PCI_DN(pdn) && !PCI_DN(pdn)->table_group;
				pdn = pdn->parent) {
			dma_window = of_get_property(pdn, "ibm,dma-window", NULL);
			if (dma_window)
				break;
		}
		if (pdn && PCI_DN(pdn)) {
			dma_offset = enable_ddw(pdev, pdn);
			if (dma_offset != 0) {
				dev_info(dev, "Using 64-bit direct DMA at offset %llx\n", dma_offset);
				set_dma_offset(dev, dma_offset);
				set_dma_ops(dev, &dma_nommu_ops);
				ddw_enabled = true;
			}
		}
	}

	/* fall back on iommu ops */
	if (!ddw_enabled && get_dma_ops(dev) != &dma_iommu_ops) {
		dev_info(dev, "Restoring 32-bit DMA via iommu\n");
		set_dma_ops(dev, &dma_iommu_ops);
	}

check_mask:
	if (!dma_supported(dev, dma_mask))
		return -EIO;

	*dev->dma_mask = dma_mask;
	return 0;
}