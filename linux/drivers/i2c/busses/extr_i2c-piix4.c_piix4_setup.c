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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_CSB5 ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 scalar_t__ PCI_VENDOR_ID_SERVERWORKS ; 
 int /*<<< orphan*/  SMBBA ; 
 int /*<<< orphan*/  SMBHSTCFG ; 
 int /*<<< orphan*/  SMBIOSIZE ; 
 int /*<<< orphan*/  SMBREV ; 
 scalar_t__ acpi_check_region (unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned short,...) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 scalar_t__ force ; 
 int force_addr ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  piix4_dmi_blacklist ; 
 int /*<<< orphan*/  piix4_dmi_ibm ; 
 TYPE_1__ piix4_driver ; 
 int /*<<< orphan*/  release_region (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int srvrworks_csb5_delay ; 

__attribute__((used)) static int piix4_setup(struct pci_dev *PIIX4_dev,
		       const struct pci_device_id *id)
{
	unsigned char temp;
	unsigned short piix4_smba;

	if ((PIIX4_dev->vendor == PCI_VENDOR_ID_SERVERWORKS) &&
	    (PIIX4_dev->device == PCI_DEVICE_ID_SERVERWORKS_CSB5))
		srvrworks_csb5_delay = 1;

	/* On some motherboards, it was reported that accessing the SMBus
	   caused severe hardware problems */
	if (dmi_check_system(piix4_dmi_blacklist)) {
		dev_err(&PIIX4_dev->dev,
			"Accessing the SMBus on this system is unsafe!\n");
		return -EPERM;
	}

	/* Don't access SMBus on IBM systems which get corrupted eeproms */
	if (dmi_check_system(piix4_dmi_ibm) &&
			PIIX4_dev->vendor == PCI_VENDOR_ID_INTEL) {
		dev_err(&PIIX4_dev->dev, "IBM system detected; this module "
			"may corrupt your serial eeprom! Refusing to load "
			"module!\n");
		return -EPERM;
	}

	/* Determine the address of the SMBus areas */
	if (force_addr) {
		piix4_smba = force_addr & 0xfff0;
		force = 0;
	} else {
		pci_read_config_word(PIIX4_dev, SMBBA, &piix4_smba);
		piix4_smba &= 0xfff0;
		if(piix4_smba == 0) {
			dev_err(&PIIX4_dev->dev, "SMBus base address "
				"uninitialized - upgrade BIOS or use "
				"force_addr=0xaddr\n");
			return -ENODEV;
		}
	}

	if (acpi_check_region(piix4_smba, SMBIOSIZE, piix4_driver.name))
		return -ENODEV;

	if (!request_region(piix4_smba, SMBIOSIZE, piix4_driver.name)) {
		dev_err(&PIIX4_dev->dev, "SMBus region 0x%x already in use!\n",
			piix4_smba);
		return -EBUSY;
	}

	pci_read_config_byte(PIIX4_dev, SMBHSTCFG, &temp);

	/* If force_addr is set, we program the new address here. Just to make
	   sure, we disable the PIIX4 first. */
	if (force_addr) {
		pci_write_config_byte(PIIX4_dev, SMBHSTCFG, temp & 0xfe);
		pci_write_config_word(PIIX4_dev, SMBBA, piix4_smba);
		pci_write_config_byte(PIIX4_dev, SMBHSTCFG, temp | 0x01);
		dev_info(&PIIX4_dev->dev, "WARNING: SMBus interface set to "
			"new address %04x!\n", piix4_smba);
	} else if ((temp & 1) == 0) {
		if (force) {
			/* This should never need to be done, but has been
			 * noted that many Dell machines have the SMBus
			 * interface on the PIIX4 disabled!? NOTE: This assumes
			 * I/O space and other allocations WERE done by the
			 * Bios!  Don't complain if your hardware does weird
			 * things after enabling this. :') Check for Bios
			 * updates before resorting to this.
			 */
			pci_write_config_byte(PIIX4_dev, SMBHSTCFG,
					      temp | 1);
			dev_notice(&PIIX4_dev->dev,
				   "WARNING: SMBus interface has been FORCEFULLY ENABLED!\n");
		} else {
			dev_err(&PIIX4_dev->dev,
				"SMBus Host Controller not enabled!\n");
			release_region(piix4_smba, SMBIOSIZE);
			return -ENODEV;
		}
	}

	if (((temp & 0x0E) == 8) || ((temp & 0x0E) == 2))
		dev_dbg(&PIIX4_dev->dev, "Using IRQ for SMBus\n");
	else if ((temp & 0x0E) == 0)
		dev_dbg(&PIIX4_dev->dev, "Using SMI# for SMBus\n");
	else
		dev_err(&PIIX4_dev->dev, "Illegal Interrupt configuration "
			"(or code out of date)!\n");

	pci_read_config_byte(PIIX4_dev, SMBREV, &temp);
	dev_info(&PIIX4_dev->dev,
		 "SMBus Host Controller at 0x%x, revision %d\n",
		 piix4_smba, temp);

	return piix4_smba;
}