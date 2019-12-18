#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {scalar_t__ subsystem_vendor; scalar_t__ vendor; scalar_t__ device; int subsystem_device; } ;
struct TYPE_3__ {int channel; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA40 ; 
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_CSB5IDE ; 
 scalar_t__ PCI_VENDOR_ID_SERVERWORKS ; 
 scalar_t__ PCI_VENDOR_ID_SUN ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ata66_svwks_cobalt(ide_hwif_t *hwif)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);

	if (dev->subsystem_vendor == PCI_VENDOR_ID_SUN &&
	    dev->vendor	== PCI_VENDOR_ID_SERVERWORKS &&
	    dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB5IDE)
		return ((1 << (hwif->channel + 14)) &
			dev->subsystem_device) ? ATA_CBL_PATA80 : ATA_CBL_PATA40;
	return ATA_CBL_PATA40;
}