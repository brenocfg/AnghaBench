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
struct pci_dev {TYPE_1__* resource; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASE_ADDRESS_SPACE_IO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void pci_fixup_umc_ide(struct pci_dev *d)
{
	/*
	 * UM8886BF IDE controller sets region type bits incorrectly,
	 * therefore they look like memory despite of them being I/O.
	 */
	int i;

	dev_warn(&d->dev, "Fixing base address flags\n");
	for(i = 0; i < 4; i++)
		d->resource[i].flags |= PCI_BASE_ADDRESS_SPACE_IO;
}