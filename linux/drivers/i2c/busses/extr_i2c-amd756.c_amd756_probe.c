#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t NFORCE ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMBBA ; 
 int /*<<< orphan*/  SMBBANFORCE ; 
 int /*<<< orphan*/  SMBGCFG ; 
 int /*<<< orphan*/  SMBREV ; 
 scalar_t__ SMB_ADDR_OFFSET ; 
 int /*<<< orphan*/  SMB_IOSIZE ; 
 int acpi_check_region (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ amd756_driver ; 
 int amd756_ioport ; 
 TYPE_2__ amd756_smbus ; 
 char** chipname ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  release_region (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 

__attribute__((used)) static int amd756_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int nforce = (id->driver_data == NFORCE);
	int error;
	u8 temp;
	
	if (amd756_ioport) {
		dev_err(&pdev->dev, "Only one device supported "
		       "(you have a strange motherboard, btw)\n");
		return -ENODEV;
	}

	if (nforce) {
		if (PCI_FUNC(pdev->devfn) != 1)
			return -ENODEV;

		pci_read_config_word(pdev, SMBBANFORCE, &amd756_ioport);
		amd756_ioport &= 0xfffc;
	} else { /* amd */
		if (PCI_FUNC(pdev->devfn) != 3)
			return -ENODEV;

		pci_read_config_byte(pdev, SMBGCFG, &temp);
		if ((temp & 128) == 0) {
			dev_err(&pdev->dev,
				"Error: SMBus controller I/O not enabled!\n");
			return -ENODEV;
		}

		/* Determine the address of the SMBus areas */
		/* Technically it is a dword but... */
		pci_read_config_word(pdev, SMBBA, &amd756_ioport);
		amd756_ioport &= 0xff00;
		amd756_ioport += SMB_ADDR_OFFSET;
	}

	error = acpi_check_region(amd756_ioport, SMB_IOSIZE,
				  amd756_driver.name);
	if (error)
		return -ENODEV;

	if (!request_region(amd756_ioport, SMB_IOSIZE, amd756_driver.name)) {
		dev_err(&pdev->dev, "SMB region 0x%x already in use!\n",
			amd756_ioport);
		return -ENODEV;
	}

	pci_read_config_byte(pdev, SMBREV, &temp);
	dev_dbg(&pdev->dev, "SMBREV = 0x%X\n", temp);
	dev_dbg(&pdev->dev, "AMD756_smba = 0x%X\n", amd756_ioport);

	/* set up the sysfs linkage to our parent device */
	amd756_smbus.dev.parent = &pdev->dev;

	snprintf(amd756_smbus.name, sizeof(amd756_smbus.name),
		 "SMBus %s adapter at %04x", chipname[id->driver_data],
		 amd756_ioport);

	error = i2c_add_adapter(&amd756_smbus);
	if (error)
		goto out_err;

	return 0;

 out_err:
	release_region(amd756_ioport, SMB_IOSIZE);
	return error;
}