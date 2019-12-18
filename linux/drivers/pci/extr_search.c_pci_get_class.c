#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_device_id {unsigned int class; int /*<<< orphan*/  class_mask; int /*<<< orphan*/  subdevice; int /*<<< orphan*/  subvendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ANY_ID ; 
 struct pci_dev* pci_get_dev_by_id (struct pci_device_id*,struct pci_dev*) ; 

struct pci_dev *pci_get_class(unsigned int class, struct pci_dev *from)
{
	struct pci_device_id id = {
		.vendor = PCI_ANY_ID,
		.device = PCI_ANY_ID,
		.subvendor = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
		.class_mask = PCI_ANY_ID,
		.class = class,
	};

	return pci_get_dev_by_id(&id, from);
}