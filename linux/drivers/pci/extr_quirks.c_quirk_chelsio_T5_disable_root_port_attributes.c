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
struct pci_dev {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  quirk_disable_root_port_attributes (struct pci_dev*) ; 

__attribute__((used)) static void quirk_chelsio_T5_disable_root_port_attributes(struct pci_dev *pdev)
{
	/*
	 * This mask/compare operation selects for Physical Function 4 on a
	 * T5.  We only need to fix up the Root Port once for any of the
	 * PFs.  PF[0..3] have PCI Device IDs of 0x50xx, but PF4 is uniquely
	 * 0x54xx so we use that one.
	 */
	if ((pdev->device & 0xff00) == 0x5400)
		quirk_disable_root_port_attributes(pdev);
}