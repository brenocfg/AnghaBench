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
struct pci_dev {scalar_t__ vendor; int device; TYPE_2__* bus; } ;
struct driver_data {int dummy; } ;
struct TYPE_4__ {TYPE_1__* parent; struct pci_dev* self; } ;
struct TYPE_3__ {struct pci_dev* self; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_ATI ; 
 int /*<<< orphan*/  mtip_disable_link_opts (struct driver_data*,struct pci_dev*) ; 

__attribute__((used)) static void mtip_fix_ero_nosnoop(struct driver_data *dd, struct pci_dev *pdev)
{
	/*
	 * This workaround is specific to AMD/ATI chipset with a PCI upstream
	 * device with device id 0x5aXX
	 */
	if (pdev->bus && pdev->bus->self) {
		if (pdev->bus->self->vendor == PCI_VENDOR_ID_ATI &&
		    ((pdev->bus->self->device & 0xff00) == 0x5a00)) {
			mtip_disable_link_opts(dd, pdev->bus->self);
		} else {
			/* Check further up the topology */
			struct pci_dev *parent_dev = pdev->bus->self;
			if (parent_dev->bus &&
				parent_dev->bus->parent &&
				parent_dev->bus->parent->self &&
				parent_dev->bus->parent->self->vendor ==
					 PCI_VENDOR_ID_ATI &&
				(parent_dev->bus->parent->self->device &
					0xff00) == 0x5a00) {
				mtip_disable_link_opts(dd,
					parent_dev->bus->parent->self);
			}
		}
	}
}