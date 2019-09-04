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
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ANY_ID ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_match_id (struct pci_device_id const*,struct pci_dev*) ; 

__attribute__((used)) static struct pci_dev *next_northbridge(struct pci_dev *dev,
					const struct pci_device_id *ids)
{
	do {
		dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, dev);
		if (!dev)
			break;
	} while (!pci_match_id(ids, dev));
	return dev;
}