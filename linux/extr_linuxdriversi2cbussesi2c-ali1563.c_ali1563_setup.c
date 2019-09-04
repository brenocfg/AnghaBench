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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI1563_SMBBA ; 
 int ALI1563_SMB_HOSTEN ; 
 int ALI1563_SMB_IOEN ; 
 int ALI1563_SMB_IOSIZE ; 
 int ENODEV ; 
 scalar_t__ acpi_check_region (int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ ali1563_pci_driver ; 
 int ali1563_smba ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  request_region (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ali1563_setup(struct pci_dev *dev)
{
	u16 ctrl;

	pci_read_config_word(dev, ALI1563_SMBBA, &ctrl);

	/* SMB I/O Base in high 12 bits and must be aligned with the
	 * size of the I/O space. */
	ali1563_smba = ctrl & ~(ALI1563_SMB_IOSIZE - 1);
	if (!ali1563_smba) {
		dev_warn(&dev->dev, "ali1563_smba Uninitialized\n");
		goto Err;
	}

	/* Check if device is enabled */
	if (!(ctrl & ALI1563_SMB_HOSTEN)) {
		dev_warn(&dev->dev, "Host Controller not enabled\n");
		goto Err;
	}
	if (!(ctrl & ALI1563_SMB_IOEN)) {
		dev_warn(&dev->dev, "I/O space not enabled, trying manually\n");
		pci_write_config_word(dev, ALI1563_SMBBA,
				      ctrl | ALI1563_SMB_IOEN);
		pci_read_config_word(dev, ALI1563_SMBBA, &ctrl);
		if (!(ctrl & ALI1563_SMB_IOEN)) {
			dev_err(&dev->dev,
				"I/O space still not enabled, giving up\n");
			goto Err;
		}
	}

	if (acpi_check_region(ali1563_smba, ALI1563_SMB_IOSIZE,
			      ali1563_pci_driver.name))
		goto Err;

	if (!request_region(ali1563_smba, ALI1563_SMB_IOSIZE,
			    ali1563_pci_driver.name)) {
		dev_err(&dev->dev, "Could not allocate I/O space at 0x%04x\n",
			ali1563_smba);
		goto Err;
	}
	dev_info(&dev->dev, "Found ALi1563 SMBus at 0x%04x\n", ali1563_smba);

	return 0;
Err:
	return -ENODEV;
}