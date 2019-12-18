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
struct pci_dev {int ignore_hotplug; TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */

void pci_ignore_hotplug(struct pci_dev *dev)
{
	struct pci_dev *bridge = dev->bus->self;

	dev->ignore_hotplug = 1;
	/* Propagate the "ignore hotplug" setting to the parent bridge. */
	if (bridge)
		bridge->ignore_hotplug = 1;
}