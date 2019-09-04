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
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int (* dma_set_mask ) (struct pci_dev*,int /*<<< orphan*/ ) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;
struct device {int /*<<< orphan*/ * dma_mask; } ;
struct TYPE_4__ {int (* dma_set_mask ) (struct device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int /*<<< orphan*/  dma_supported (struct device*,int /*<<< orphan*/ ) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 TYPE_2__ ppc_md ; 
 int stub1 (struct device*,int /*<<< orphan*/ ) ; 
 int stub2 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

int dma_set_mask(struct device *dev, u64 dma_mask)
{
	if (ppc_md.dma_set_mask)
		return ppc_md.dma_set_mask(dev, dma_mask);

	if (dev_is_pci(dev)) {
		struct pci_dev *pdev = to_pci_dev(dev);
		struct pci_controller *phb = pci_bus_to_host(pdev->bus);
		if (phb->controller_ops.dma_set_mask)
			return phb->controller_ops.dma_set_mask(pdev, dma_mask);
	}

	if (!dev->dma_mask || !dma_supported(dev, dma_mask))
		return -EIO;
	*dev->dma_mask = dma_mask;
	return 0;
}