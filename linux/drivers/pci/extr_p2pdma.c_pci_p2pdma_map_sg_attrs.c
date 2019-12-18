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
struct scatterlist {int dummy; } ;
struct pci_p2pdma_pagemap {int /*<<< orphan*/  provider; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  pgmap; } ;

/* Variables and functions */
#define  PCI_P2PDMA_MAP_BUS_ADDR 129 
#define  PCI_P2PDMA_MAP_THRU_HOST_BRIDGE 128 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int __pci_p2pdma_map_sg (struct pci_p2pdma_pagemap*,struct device*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 int dma_map_sg_attrs (struct device*,struct scatterlist*,int,int,unsigned long) ; 
 int pci_p2pdma_map_type (int /*<<< orphan*/ ,struct pci_dev*) ; 
 TYPE_1__* sg_page (struct scatterlist*) ; 
 struct pci_p2pdma_pagemap* to_p2p_pgmap (int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

int pci_p2pdma_map_sg_attrs(struct device *dev, struct scatterlist *sg,
		int nents, enum dma_data_direction dir, unsigned long attrs)
{
	struct pci_p2pdma_pagemap *p2p_pgmap =
		to_p2p_pgmap(sg_page(sg)->pgmap);
	struct pci_dev *client;

	if (WARN_ON_ONCE(!dev_is_pci(dev)))
		return 0;

	client = to_pci_dev(dev);

	switch (pci_p2pdma_map_type(p2p_pgmap->provider, client)) {
	case PCI_P2PDMA_MAP_THRU_HOST_BRIDGE:
		return dma_map_sg_attrs(dev, sg, nents, dir, attrs);
	case PCI_P2PDMA_MAP_BUS_ADDR:
		return __pci_p2pdma_map_sg(p2p_pgmap, dev, sg, nents);
	default:
		WARN_ON_ONCE(1);
		return 0;
	}
}