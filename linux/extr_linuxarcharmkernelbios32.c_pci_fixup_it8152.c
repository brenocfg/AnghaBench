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
struct pci_dev {int class; TYPE_1__* resource; } ;
struct TYPE_2__ {scalar_t__ flags; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_HOST ; 
 int PCI_NUM_RESOURCES ; 

__attribute__((used)) static void pci_fixup_it8152(struct pci_dev *dev)
{
	int i;
	/* fixup for ITE 8152 devices */
	/* FIXME: add defines for class 0x68000 and 0x80103 */
	if ((dev->class >> 8) == PCI_CLASS_BRIDGE_HOST ||
	    dev->class == 0x68000 ||
	    dev->class == 0x80103) {
		for (i = 0; i < PCI_NUM_RESOURCES; i++) {
			dev->resource[i].start = 0;
			dev->resource[i].end   = 0;
			dev->resource[i].flags = 0;
		}
	}
}