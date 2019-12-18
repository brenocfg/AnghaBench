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
struct pci_dev {scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_pci_slot_eq(struct pci_dev* adev, struct pci_dev* bdev)
{
	if ((adev->subsystem_vendor == bdev->subsystem_vendor) &&
		(adev->subsystem_device == bdev->subsystem_device) &&
		(adev->bus->number == bdev->bus->number) &&
		(PCI_SLOT(adev->devfn) == PCI_SLOT(bdev->devfn)))
		return 1;
	return 0;
}