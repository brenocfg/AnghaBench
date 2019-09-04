#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {scalar_t__ device; int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int device; int revision; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FEATURE_I2CBLOCK ; 
#define  PCI_DEVICE_ID_VIA_8233A 139 
#define  PCI_DEVICE_ID_VIA_8233_0 138 
#define  PCI_DEVICE_ID_VIA_8235 137 
#define  PCI_DEVICE_ID_VIA_8237 136 
#define  PCI_DEVICE_ID_VIA_8237A 135 
#define  PCI_DEVICE_ID_VIA_8237S 134 
#define  PCI_DEVICE_ID_VIA_8251 133 
 scalar_t__ PCI_DEVICE_ID_VIA_82C596_3 ; 
#define  PCI_DEVICE_ID_VIA_82C686_4 132 
#define  PCI_DEVICE_ID_VIA_CX700 131 
#define  PCI_DEVICE_ID_VIA_VX800 130 
#define  PCI_DEVICE_ID_VIA_VX855 129 
#define  PCI_DEVICE_ID_VIA_VX900 128 
 int /*<<< orphan*/  SMBBA2 ; 
 int SMBHSTCFG ; 
 int acpi_check_region (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ force ; 
 int force_addr ; 
 int i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/ * pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 
 scalar_t__ pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int,unsigned char) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 TYPE_3__ vt596_adapter ; 
 TYPE_2__ vt596_driver ; 
 int /*<<< orphan*/  vt596_features ; 
 int /*<<< orphan*/ * vt596_pdev ; 
 int vt596_smba ; 

__attribute__((used)) static int vt596_probe(struct pci_dev *pdev,
		       const struct pci_device_id *id)
{
	unsigned char temp;
	int error;

	/* Determine the address of the SMBus areas */
	if (force_addr) {
		vt596_smba = force_addr & 0xfff0;
		force = 0;
		goto found;
	}

	if ((pci_read_config_word(pdev, id->driver_data, &vt596_smba)) ||
	    !(vt596_smba & 0x0001)) {
		/* try 2nd address and config reg. for 596 */
		if (id->device == PCI_DEVICE_ID_VIA_82C596_3 &&
		    !pci_read_config_word(pdev, SMBBA2, &vt596_smba) &&
		    (vt596_smba & 0x0001)) {
			SMBHSTCFG = 0x84;
		} else {
			/* no matches at all */
			dev_err(&pdev->dev, "Cannot configure "
				"SMBus I/O Base address\n");
			return -ENODEV;
		}
	}

	vt596_smba &= 0xfff0;
	if (vt596_smba == 0) {
		dev_err(&pdev->dev, "SMBus base address "
			"uninitialized - upgrade BIOS or use "
			"force_addr=0xaddr\n");
		return -ENODEV;
	}

found:
	error = acpi_check_region(vt596_smba, 8, vt596_driver.name);
	if (error)
		return -ENODEV;

	if (!request_region(vt596_smba, 8, vt596_driver.name)) {
		dev_err(&pdev->dev, "SMBus region 0x%x already in use!\n",
			vt596_smba);
		return -ENODEV;
	}

	pci_read_config_byte(pdev, SMBHSTCFG, &temp);
	/* If force_addr is set, we program the new address here. Just to make
	   sure, we disable the VT596 first. */
	if (force_addr) {
		pci_write_config_byte(pdev, SMBHSTCFG, temp & 0xfe);
		pci_write_config_word(pdev, id->driver_data, vt596_smba);
		pci_write_config_byte(pdev, SMBHSTCFG, temp | 0x01);
		dev_warn(&pdev->dev, "WARNING: SMBus interface set to new "
			 "address 0x%04x!\n", vt596_smba);
	} else if (!(temp & 0x01)) {
		if (force) {
			/* NOTE: This assumes I/O space and other allocations
			 * WERE done by the Bios!  Don't complain if your
			 * hardware does weird things after enabling this.
			 * :') Check for Bios updates before resorting to
			 * this.
			 */
			pci_write_config_byte(pdev, SMBHSTCFG, temp | 0x01);
			dev_info(&pdev->dev, "Enabling SMBus device\n");
		} else {
			dev_err(&pdev->dev, "SMBUS: Error: Host SMBus "
				"controller not enabled! - upgrade BIOS or "
				"use force=1\n");
			error = -ENODEV;
			goto release_region;
		}
	}

	dev_dbg(&pdev->dev, "VT596_smba = 0x%X\n", vt596_smba);

	switch (pdev->device) {
	case PCI_DEVICE_ID_VIA_CX700:
	case PCI_DEVICE_ID_VIA_VX800:
	case PCI_DEVICE_ID_VIA_VX855:
	case PCI_DEVICE_ID_VIA_VX900:
	case PCI_DEVICE_ID_VIA_8251:
	case PCI_DEVICE_ID_VIA_8237:
	case PCI_DEVICE_ID_VIA_8237A:
	case PCI_DEVICE_ID_VIA_8237S:
	case PCI_DEVICE_ID_VIA_8235:
	case PCI_DEVICE_ID_VIA_8233A:
	case PCI_DEVICE_ID_VIA_8233_0:
		vt596_features |= FEATURE_I2CBLOCK;
		break;
	case PCI_DEVICE_ID_VIA_82C686_4:
		/* The VT82C686B (rev 0x40) does support I2C block
		   transactions, but the VT82C686A (rev 0x30) doesn't */
		if (pdev->revision >= 0x40)
			vt596_features |= FEATURE_I2CBLOCK;
		break;
	}

	vt596_adapter.dev.parent = &pdev->dev;
	snprintf(vt596_adapter.name, sizeof(vt596_adapter.name),
		 "SMBus Via Pro adapter at %04x", vt596_smba);

	vt596_pdev = pci_dev_get(pdev);
	error = i2c_add_adapter(&vt596_adapter);
	if (error) {
		pci_dev_put(vt596_pdev);
		vt596_pdev = NULL;
		goto release_region;
	}

	/* Always return failure here.  This is to allow other drivers to bind
	 * to this pci device.  We don't really want to have control over the
	 * pci device, we only wanted to read as few register values from it.
	 */
	return -ENODEV;

release_region:
	release_region(vt596_smba, 8);
	return error;
}