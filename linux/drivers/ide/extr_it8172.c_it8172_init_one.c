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
struct pci_dev {int class; } ;

/* Variables and functions */
 int ENODEV ; 
 int PCI_CLASS_STORAGE_IDE ; 
 int ide_pci_init_one (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  it8172_port_info ; 

__attribute__((used)) static int it8172_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	if ((dev->class >> 8) != PCI_CLASS_STORAGE_IDE)
		return -ENODEV; /* IT8172 is more than an IDE controller */
	return ide_pci_init_one(dev, &it8172_port_info, NULL);
}