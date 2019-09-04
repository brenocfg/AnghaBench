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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  SMBIOSIZE ; 
 scalar_t__ acpi_check_region (unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned short) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned short) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,unsigned short,unsigned short*) ; 
 TYPE_1__ piix4_driver ; 
 int /*<<< orphan*/  request_region (unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int piix4_setup_aux(struct pci_dev *PIIX4_dev,
			   const struct pci_device_id *id,
			   unsigned short base_reg_addr)
{
	/* Set up auxiliary SMBus controllers found on some
	 * AMD chipsets e.g. SP5100 (SB700 derivative) */

	unsigned short piix4_smba;

	/* Read address of auxiliary SMBus controller */
	pci_read_config_word(PIIX4_dev, base_reg_addr, &piix4_smba);
	if ((piix4_smba & 1) == 0) {
		dev_dbg(&PIIX4_dev->dev,
			"Auxiliary SMBus controller not enabled\n");
		return -ENODEV;
	}

	piix4_smba &= 0xfff0;
	if (piix4_smba == 0) {
		dev_dbg(&PIIX4_dev->dev,
			"Auxiliary SMBus base address uninitialized\n");
		return -ENODEV;
	}

	if (acpi_check_region(piix4_smba, SMBIOSIZE, piix4_driver.name))
		return -ENODEV;

	if (!request_region(piix4_smba, SMBIOSIZE, piix4_driver.name)) {
		dev_err(&PIIX4_dev->dev, "Auxiliary SMBus region 0x%x "
			"already in use!\n", piix4_smba);
		return -EBUSY;
	}

	dev_info(&PIIX4_dev->dev,
		 "Auxiliary SMBus Host Controller at 0x%x\n",
		 piix4_smba);

	return piix4_smba;
}