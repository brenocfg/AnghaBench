#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int dummy; } ;
struct device_node {struct device_node* parent; } ;
struct device {int /*<<< orphan*/  dma_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  table_group; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_required_mask ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 TYPE_2__* PCI_DN (struct device_node*) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  disable_ddw ; 
 TYPE_1__ dma_iommu_ops ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static u64 dma_get_required_mask_pSeriesLP(struct device *dev)
{
	if (!dev->dma_mask)
		return 0;

	if (!disable_ddw && dev_is_pci(dev)) {
		struct pci_dev *pdev = to_pci_dev(dev);
		struct device_node *dn;

		dn = pci_device_to_OF_node(pdev);

		/* search upwards for ibm,dma-window */
		for (; dn && PCI_DN(dn) && !PCI_DN(dn)->table_group;
				dn = dn->parent)
			if (of_get_property(dn, "ibm,dma-window", NULL))
				break;
		/* if there is a ibm,ddw-applicable property require 64 bits */
		if (dn && PCI_DN(dn) &&
				of_get_property(dn, "ibm,ddw-applicable", NULL))
			return DMA_BIT_MASK(64);
	}

	return dma_iommu_ops.get_required_mask(dev);
}