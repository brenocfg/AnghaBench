#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {scalar_t__ subsystem_vendor; scalar_t__ device; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ide_hwif_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA40 ; 
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_CSB6IDE ; 
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2 ; 
 scalar_t__ PCI_VENDOR_ID_DELL ; 
 scalar_t__ PCI_VENDOR_ID_SERVERWORKS ; 
 scalar_t__ PCI_VENDOR_ID_SUN ; 
 int /*<<< orphan*/  ata66_svwks_cobalt (TYPE_1__*) ; 
 int /*<<< orphan*/  ata66_svwks_dell (TYPE_1__*) ; 
 int /*<<< orphan*/  ata66_svwks_svwks (TYPE_1__*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 svwks_cable_detect(ide_hwif_t *hwif)
{
	struct pci_dev *dev = to_pci_dev(hwif->dev);

	/* Server Works */
	if (dev->subsystem_vendor == PCI_VENDOR_ID_SERVERWORKS)
		return ata66_svwks_svwks (hwif);
	
	/* Dell PowerEdge */
	if (dev->subsystem_vendor == PCI_VENDOR_ID_DELL)
		return ata66_svwks_dell (hwif);

	/* Cobalt Alpine */
	if (dev->subsystem_vendor == PCI_VENDOR_ID_SUN)
		return ata66_svwks_cobalt (hwif);

	/* Per Specified Design by OEM, and ASIC Architect */
	if ((dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE) ||
	    (dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB6IDE2))
		return ATA_CBL_PATA80;

	return ATA_CBL_PATA40;
}