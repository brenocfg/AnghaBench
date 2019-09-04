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
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; scalar_t__ parent; } ;

/* Variables and functions */

__attribute__((used)) static inline struct pci_dev *bridge_root_dev(struct pci_dev *dev)
{
	while (dev->bus->parent) {
		/* Move up the chain of bridges. */
		dev = dev->bus->self;
	}

	return dev;
}