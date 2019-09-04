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
struct pci_dev {scalar_t__ devfn; TYPE_2__* resource; TYPE_1__* bus; } ;
struct TYPE_4__ {scalar_t__ flags; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int DEVICE_COUNT_RESOURCE ; 

__attribute__((used)) static void rc_pci_fixup(struct pci_dev *dev)
{
	/*
	 * Prevent enumeration of root complex.
	 */
	if (dev->bus->parent == NULL && dev->devfn == 0) {
		int i;

		for (i = 0; i < DEVICE_COUNT_RESOURCE; i++) {
			dev->resource[i].start = 0;
			dev->resource[i].end   = 0;
			dev->resource[i].flags = 0;
		}
	}
}