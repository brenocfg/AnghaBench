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
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_device_hook ) (struct pci_dev*) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pci_controller* pci_bus_to_host (int /*<<< orphan*/ ) ; 
 int pci_enable_resources (struct pci_dev*,int) ; 
 int /*<<< orphan*/  stub1 (struct pci_dev*) ; 

int pcibios_enable_device(struct pci_dev *dev, int mask)
{
	struct pci_controller *phb = pci_bus_to_host(dev->bus);

	if (phb->controller_ops.enable_device_hook)
		if (!phb->controller_ops.enable_device_hook(dev))
			return -EINVAL;

	return pci_enable_resources(dev, mask);
}