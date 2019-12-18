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
struct physdev_pci_device {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; scalar_t__ seg; } ;
struct physdev_manage_pci {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; scalar_t__ seg; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENOSYS ; 
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_pci_device*) ; 
 int /*<<< orphan*/  PHYSDEVOP_manage_pci_remove ; 
 int /*<<< orphan*/  PHYSDEVOP_pci_device_remove ; 
 scalar_t__ pci_domain_nr (TYPE_1__*) ; 
 scalar_t__ pci_seg_supported ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int xen_remove_device(struct device *dev)
{
	int r;
	struct pci_dev *pci_dev = to_pci_dev(dev);

	if (pci_seg_supported) {
		struct physdev_pci_device device = {
			.seg = pci_domain_nr(pci_dev->bus),
			.bus = pci_dev->bus->number,
			.devfn = pci_dev->devfn
		};

		r = HYPERVISOR_physdev_op(PHYSDEVOP_pci_device_remove,
					  &device);
	} else if (pci_domain_nr(pci_dev->bus))
		r = -ENOSYS;
	else {
		struct physdev_manage_pci manage_pci = {
			.bus = pci_dev->bus->number,
			.devfn = pci_dev->devfn
		};

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_remove,
					  &manage_pci);
	}

	return r;
}