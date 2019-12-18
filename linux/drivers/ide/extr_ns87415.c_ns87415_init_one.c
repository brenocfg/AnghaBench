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
struct pci_dev {int /*<<< orphan*/  devfn; } ;
struct ide_port_info {int /*<<< orphan*/ * tp_ops; int /*<<< orphan*/  init_iops; } ;

/* Variables and functions */
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int ide_pci_init_one (struct pci_dev*,struct ide_port_info*,int /*<<< orphan*/ *) ; 
 struct ide_port_info ns87415_chipset ; 
 int /*<<< orphan*/  superio_init_iops ; 
 int /*<<< orphan*/  superio_tp_ops ; 

__attribute__((used)) static int ns87415_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct ide_port_info d = ns87415_chipset;

#ifdef CONFIG_SUPERIO
	if (PCI_SLOT(dev->devfn) == 0xE) {
		/* Built-in - assume it's under superio. */
		d.init_iops = superio_init_iops;
		d.tp_ops = &superio_tp_ops;
	}
#endif
	return ide_pci_init_one(dev, &d, NULL);
}