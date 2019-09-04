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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned char ALI1535_SMBIO_EN ; 
 int ALI1535_SMB_IOSIZE ; 
 int EBUSY ; 
 int ENODEV ; 
 int IORESOURCE_IO ; 
 int /*<<< orphan*/  SMBBA ; 
 int /*<<< orphan*/  SMBCFG ; 
 int /*<<< orphan*/  SMBCLK ; 
 int /*<<< orphan*/  SMBHSTCFG ; 
 int /*<<< orphan*/  SMBREV ; 
 int acpi_check_region (unsigned char,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ ali1535_driver ; 
 int ali1535_offset ; 
 unsigned char ali1535_smba ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned char pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (unsigned char,int) ; 
 int /*<<< orphan*/  request_region (unsigned char,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ali1535_setup(struct pci_dev *dev)
{
	int retval;
	unsigned char temp;

	/* Check the following things:
		- SMB I/O address is initialized
		- Device is enabled
		- We can use the addresses
	*/

	retval = pci_enable_device(dev);
	if (retval) {
		dev_err(&dev->dev, "ALI1535_smb can't enable device\n");
		goto exit;
	}

	/* Determine the address of the SMBus area */
	pci_read_config_word(dev, SMBBA, &ali1535_offset);
	dev_dbg(&dev->dev, "ALI1535_smb is at offset 0x%04x\n", ali1535_offset);
	ali1535_offset &= (0xffff & ~(ALI1535_SMB_IOSIZE - 1));
	if (ali1535_offset == 0) {
		dev_warn(&dev->dev,
			"ALI1535_smb region uninitialized - upgrade BIOS?\n");
		retval = -ENODEV;
		goto exit;
	}

	if (pci_resource_flags(dev, 0) & IORESOURCE_IO)
		ali1535_smba = pci_resource_start(dev, 0) + ali1535_offset;
	else
		ali1535_smba = ali1535_offset;

	retval = acpi_check_region(ali1535_smba, ALI1535_SMB_IOSIZE,
				   ali1535_driver.name);
	if (retval)
		goto exit;

	if (!request_region(ali1535_smba, ALI1535_SMB_IOSIZE,
			    ali1535_driver.name)) {
		dev_err(&dev->dev, "ALI1535_smb region 0x%lx already in use!\n",
			ali1535_smba);
		retval = -EBUSY;
		goto exit;
	}

	/* check if whole device is enabled */
	pci_read_config_byte(dev, SMBCFG, &temp);
	if ((temp & ALI1535_SMBIO_EN) == 0) {
		dev_err(&dev->dev, "SMB device not enabled - upgrade BIOS?\n");
		retval = -ENODEV;
		goto exit_free;
	}

	/* Is SMB Host controller enabled? */
	pci_read_config_byte(dev, SMBHSTCFG, &temp);
	if ((temp & 1) == 0) {
		dev_err(&dev->dev, "SMBus controller not enabled - upgrade BIOS?\n");
		retval = -ENODEV;
		goto exit_free;
	}

	/* set SMB clock to 74KHz as recommended in data sheet */
	pci_write_config_byte(dev, SMBCLK, 0x20);

	/*
	  The interrupt routing for SMB is set up in register 0x77 in the
	  1533 ISA Bridge device, NOT in the 7101 device.
	  Don't bother with finding the 1533 device and reading the register.
	if ((....... & 0x0F) == 1)
		dev_dbg(&dev->dev, "ALI1535 using Interrupt 9 for SMBus.\n");
	*/
	pci_read_config_byte(dev, SMBREV, &temp);
	dev_dbg(&dev->dev, "SMBREV = 0x%X\n", temp);
	dev_dbg(&dev->dev, "ALI1535_smba = 0x%lx\n", ali1535_smba);

	return 0;

exit_free:
	release_region(ali1535_smba, ALI1535_SMB_IOSIZE);
exit:
	return retval;
}