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
struct TYPE_3__ {int /*<<< orphan*/  (* dma_get_required_mask ) (struct pci_dev*) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dma_get_required_mask ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __dma_get_required_mask (struct device*) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 TYPE_2__ ppc_md ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

u64 dma_get_required_mask(struct device *dev)
{
	if (ppc_md.dma_get_required_mask)
		return ppc_md.dma_get_required_mask(dev);

	if (dev_is_pci(dev)) {
		struct pci_dev *pdev = to_pci_dev(dev);
		struct pci_controller *phb = pci_bus_to_host(pdev->bus);
		if (phb->controller_ops.dma_get_required_mask)
			return phb->controller_ops.dma_get_required_mask(pdev);
	}

	return __dma_get_required_mask(dev);
}