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
typedef  scalar_t__ u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/ * resource; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  PCI_CLASS_DEVICE ; 
 scalar_t__ PCI_CLASS_SERIAL_SMBUS ; 
 size_t SIS96x_BAR ; 
 int SMB_IOSIZE ; 
 int acpi_check_resource_conflict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_add_adapter (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int pci_resource_start (struct pci_dev*,size_t) ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ sis96x_adapter ; 
 TYPE_2__ sis96x_driver ; 
 int sis96x_smbus_base ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int sis96x_probe(struct pci_dev *dev,
				const struct pci_device_id *id)
{
	u16 ww = 0;
	int retval;

	if (sis96x_smbus_base) {
		dev_err(&dev->dev, "Only one device supported.\n");
		return -EBUSY;
	}

	pci_read_config_word(dev, PCI_CLASS_DEVICE, &ww);
	if (PCI_CLASS_SERIAL_SMBUS != ww) {
		dev_err(&dev->dev, "Unsupported device class 0x%04x!\n", ww);
		return -ENODEV;
	}

	sis96x_smbus_base = pci_resource_start(dev, SIS96x_BAR);
	if (!sis96x_smbus_base) {
		dev_err(&dev->dev, "SiS96x SMBus base address "
			"not initialized!\n");
		return -EINVAL;
	}
	dev_info(&dev->dev, "SiS96x SMBus base address: 0x%04x\n",
			sis96x_smbus_base);

	retval = acpi_check_resource_conflict(&dev->resource[SIS96x_BAR]);
	if (retval)
		return -ENODEV;

	/* Everything is happy, let's grab the memory and set things up. */
	if (!request_region(sis96x_smbus_base, SMB_IOSIZE,
			    sis96x_driver.name)) {
		dev_err(&dev->dev, "SMBus registers 0x%04x-0x%04x "
			"already in use!\n", sis96x_smbus_base,
			sis96x_smbus_base + SMB_IOSIZE - 1);

		sis96x_smbus_base = 0;
		return -EINVAL;
	}

	/* set up the sysfs linkage to our parent device */
	sis96x_adapter.dev.parent = &dev->dev;

	snprintf(sis96x_adapter.name, sizeof(sis96x_adapter.name),
		"SiS96x SMBus adapter at 0x%04x", sis96x_smbus_base);

	if ((retval = i2c_add_adapter(&sis96x_adapter))) {
		dev_err(&dev->dev, "Couldn't register adapter!\n");
		release_region(sis96x_smbus_base, SMB_IOSIZE);
		sis96x_smbus_base = 0;
	}

	return retval;
}