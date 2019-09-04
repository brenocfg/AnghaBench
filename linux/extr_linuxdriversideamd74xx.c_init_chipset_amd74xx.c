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
typedef  int u8 ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;

/* Variables and functions */
 int AMD_IDE_CONFIG ; 
 scalar_t__ PCI_DEVICE_ID_AMD_COBRA_7401 ; 
 scalar_t__ PCI_DEVICE_ID_AMD_VIPER_7409 ; 
 scalar_t__ PCI_DEVICE_ID_AMD_VIPER_7411 ; 
 scalar_t__ PCI_VENDOR_ID_AMD ; 
 int /*<<< orphan*/  amd7409_cable_detect (struct pci_dev*) ; 
 int /*<<< orphan*/  amd7411_cable_detect (struct pci_dev*) ; 
 int amd_offset (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,int) ; 

__attribute__((used)) static int init_chipset_amd74xx(struct pci_dev *dev)
{
	u8 t = 0, offset = amd_offset(dev);

/*
 * Check 80-wire cable presence.
 */

	if (dev->vendor == PCI_VENDOR_ID_AMD &&
	    dev->device == PCI_DEVICE_ID_AMD_COBRA_7401)
		; /* no UDMA > 2 */
	else if (dev->vendor == PCI_VENDOR_ID_AMD &&
		 dev->device == PCI_DEVICE_ID_AMD_VIPER_7409)
		amd7409_cable_detect(dev);
	else
		amd7411_cable_detect(dev);

/*
 * Take care of prefetch & postwrite.
 */

	pci_read_config_byte(dev, AMD_IDE_CONFIG + offset, &t);
	/*
	 * Check for broken FIFO support.
	 */
	if (dev->vendor == PCI_VENDOR_ID_AMD &&
	    dev->device == PCI_DEVICE_ID_AMD_VIPER_7411)
		t &= 0x0f;
	else
		t |= 0xf0;
	pci_write_config_byte(dev, AMD_IDE_CONFIG + offset, t);

	return 0;
}