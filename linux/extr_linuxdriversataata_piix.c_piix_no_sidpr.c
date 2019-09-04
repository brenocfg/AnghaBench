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
struct pci_dev {scalar_t__ vendor; int device; scalar_t__ subsystem_vendor; int subsystem_device; } ;
struct ata_host {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 scalar_t__ PCI_VENDOR_ID_SAMSUNG ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool piix_no_sidpr(struct ata_host *host)
{
	struct pci_dev *pdev = to_pci_dev(host->dev);

	/*
	 * Samsung DB-P70 only has three ATA ports exposed and
	 * curiously the unconnected first port reports link online
	 * while not responding to SRST protocol causing excessive
	 * detection delay.
	 *
	 * Unfortunately, the system doesn't carry enough DMI
	 * information to identify the machine but does have subsystem
	 * vendor and device set.  As it's unclear whether the
	 * subsystem vendor/device is used only for this specific
	 * board, the port can't be disabled solely with the
	 * information; however, turning off SIDPR access works around
	 * the problem.  Turn it off.
	 *
	 * This problem is reported in bnc#441240.
	 *
	 * https://bugzilla.novell.com/show_bug.cgi?id=441420
	 */
	if (pdev->vendor == PCI_VENDOR_ID_INTEL && pdev->device == 0x2920 &&
	    pdev->subsystem_vendor == PCI_VENDOR_ID_SAMSUNG &&
	    pdev->subsystem_device == 0xb049) {
		dev_warn(host->dev,
			 "Samsung DB-P70 detected, disabling SIDPR\n");
		return true;
	}

	return false;
}