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
struct TYPE_2__ {int /*<<< orphan*/ * type; } ;
struct pci_dev {int /*<<< orphan*/  bus; TYPE_1__ dev; int /*<<< orphan*/  bus_list; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct pci_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bus_get (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_dev_type ; 

struct pci_dev *pci_alloc_dev(struct pci_bus *bus)
{
	struct pci_dev *dev;

	dev = kzalloc(sizeof(struct pci_dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	INIT_LIST_HEAD(&dev->bus_list);
	dev->dev.type = &pci_dev_type;
	dev->bus = pci_bus_get(bus);

	return dev;
}