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
struct TYPE_4__ {scalar_t__ sd; } ;
struct TYPE_3__ {TYPE_2__ kobj; } ;
struct pci_dev {int /*<<< orphan*/  bus; TYPE_1__ dev; } ;

/* Variables and functions */
 int VIRTFN_ID_LEN ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iov_virtfn_bus (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_iov_virtfn_devfn (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_stop_and_remove_bus_device (struct pci_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sysfs_remove_link (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  virtfn_remove_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pci_iov_remove_virtfn(struct pci_dev *dev, int id)
{
	char buf[VIRTFN_ID_LEN];
	struct pci_dev *virtfn;

	virtfn = pci_get_domain_bus_and_slot(pci_domain_nr(dev->bus),
					     pci_iov_virtfn_bus(dev, id),
					     pci_iov_virtfn_devfn(dev, id));
	if (!virtfn)
		return;

	sprintf(buf, "virtfn%u", id);
	sysfs_remove_link(&dev->dev.kobj, buf);
	/*
	 * pci_stop_dev() could have been called for this virtfn already,
	 * so the directory for the virtfn may have been removed before.
	 * Double check to avoid spurious sysfs warnings.
	 */
	if (virtfn->dev.kobj.sd)
		sysfs_remove_link(&virtfn->dev.kobj, "physfn");

	pci_stop_and_remove_bus_device(virtfn);
	virtfn_remove_bus(dev->bus, virtfn->bus);

	/* balance pci_get_domain_bus_and_slot() */
	pci_dev_put(virtfn);
	pci_dev_put(dev);
}