#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_5__ {int flags; scalar_t__ start; scalar_t__ end; } ;
struct dev_pagemap {TYPE_2__ res; int /*<<< orphan*/  ref; int /*<<< orphan*/  type; } ;
struct pci_p2pdma_pagemap {scalar_t__ bus_offset; struct pci_dev* provider; struct dev_pagemap pgmap; } ;
struct pci_dev {int /*<<< orphan*/  dev; TYPE_1__* p2pdma; } ;
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MEMORY_DEVICE_PCI_P2PDMA ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct dev_pagemap*) ; 
 struct pci_p2pdma_pagemap* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 void* devm_memremap_pages (int /*<<< orphan*/ *,struct dev_pagemap*) ; 
 int /*<<< orphan*/  devm_memunmap_pages (int /*<<< orphan*/ *,struct dev_pagemap*) ; 
 int gen_pool_add_owner (int /*<<< orphan*/ ,unsigned long,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_bus_address (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,TYPE_2__*) ; 
 int pci_p2pdma_setup (struct pci_dev*) ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 

int pci_p2pdma_add_resource(struct pci_dev *pdev, int bar, size_t size,
			    u64 offset)
{
	struct pci_p2pdma_pagemap *p2p_pgmap;
	struct dev_pagemap *pgmap;
	void *addr;
	int error;

	if (!(pci_resource_flags(pdev, bar) & IORESOURCE_MEM))
		return -EINVAL;

	if (offset >= pci_resource_len(pdev, bar))
		return -EINVAL;

	if (!size)
		size = pci_resource_len(pdev, bar) - offset;

	if (size + offset > pci_resource_len(pdev, bar))
		return -EINVAL;

	if (!pdev->p2pdma) {
		error = pci_p2pdma_setup(pdev);
		if (error)
			return error;
	}

	p2p_pgmap = devm_kzalloc(&pdev->dev, sizeof(*p2p_pgmap), GFP_KERNEL);
	if (!p2p_pgmap)
		return -ENOMEM;

	pgmap = &p2p_pgmap->pgmap;
	pgmap->res.start = pci_resource_start(pdev, bar) + offset;
	pgmap->res.end = pgmap->res.start + size - 1;
	pgmap->res.flags = pci_resource_flags(pdev, bar);
	pgmap->type = MEMORY_DEVICE_PCI_P2PDMA;

	p2p_pgmap->provider = pdev;
	p2p_pgmap->bus_offset = pci_bus_address(pdev, bar) -
		pci_resource_start(pdev, bar);

	addr = devm_memremap_pages(&pdev->dev, pgmap);
	if (IS_ERR(addr)) {
		error = PTR_ERR(addr);
		goto pgmap_free;
	}

	error = gen_pool_add_owner(pdev->p2pdma->pool, (unsigned long)addr,
			pci_bus_address(pdev, bar) + offset,
			resource_size(&pgmap->res), dev_to_node(&pdev->dev),
			pgmap->ref);
	if (error)
		goto pages_free;

	pci_info(pdev, "added peer-to-peer DMA memory %pR\n",
		 &pgmap->res);

	return 0;

pages_free:
	devm_memunmap_pages(&pdev->dev, pgmap);
pgmap_free:
	devm_kfree(&pdev->dev, pgmap);
	return error;
}