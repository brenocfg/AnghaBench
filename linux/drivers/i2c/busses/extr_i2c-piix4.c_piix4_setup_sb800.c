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
typedef  int u8 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int revision; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ PCI_DEVICE_ID_AMD_HUDSON2_SMBUS ; 
 scalar_t__ PCI_DEVICE_ID_AMD_KERNCZ_SMBUS ; 
 scalar_t__ PCI_VENDOR_ID_AMD ; 
 scalar_t__ PCI_VENDOR_ID_HYGON ; 
 scalar_t__ SB800_PIIX4_PORT_IDX ; 
 scalar_t__ SB800_PIIX4_PORT_IDX_ALT ; 
 scalar_t__ SB800_PIIX4_PORT_IDX_KERNCZ ; 
 int /*<<< orphan*/  SB800_PIIX4_PORT_IDX_MASK ; 
 int /*<<< orphan*/  SB800_PIIX4_PORT_IDX_MASK_KERNCZ ; 
 int SB800_PIIX4_PORT_IDX_SEL ; 
 int /*<<< orphan*/  SB800_PIIX4_PORT_IDX_SHIFT ; 
 int /*<<< orphan*/  SB800_PIIX4_PORT_IDX_SHIFT_KERNCZ ; 
 int SB800_PIIX4_SMB_IDX ; 
 int SMBIOSIZE ; 
 scalar_t__ acpi_check_region (unsigned short,int,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,unsigned int,...) ; 
 scalar_t__ force ; 
 scalar_t__ force_addr ; 
 int inb_p (int) ; 
 int /*<<< orphan*/  outb_p (int,int) ; 
 TYPE_1__ piix4_driver ; 
 int /*<<< orphan*/  piix4_port_mask_sb800 ; 
 scalar_t__ piix4_port_sel_sb800 ; 
 int /*<<< orphan*/  piix4_port_shift_sb800 ; 
 int /*<<< orphan*/  release_region (int,int) ; 
 int /*<<< orphan*/  request_muxed_region (int,int,char*) ; 
 int /*<<< orphan*/  request_region (unsigned short,int,char*) ; 

__attribute__((used)) static int piix4_setup_sb800(struct pci_dev *PIIX4_dev,
			     const struct pci_device_id *id, u8 aux)
{
	unsigned short piix4_smba;
	u8 smba_en_lo, smba_en_hi, smb_en, smb_en_status, port_sel;
	u8 i2ccfg, i2ccfg_offset = 0x10;

	/* SB800 and later SMBus does not support forcing address */
	if (force || force_addr) {
		dev_err(&PIIX4_dev->dev, "SMBus does not support "
			"forcing address!\n");
		return -EINVAL;
	}

	/* Determine the address of the SMBus areas */
	if ((PIIX4_dev->vendor == PCI_VENDOR_ID_AMD &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
	     PIIX4_dev->revision >= 0x41) ||
	    (PIIX4_dev->vendor == PCI_VENDOR_ID_AMD &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS &&
	     PIIX4_dev->revision >= 0x49) ||
	    (PIIX4_dev->vendor == PCI_VENDOR_ID_HYGON &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS))
		smb_en = 0x00;
	else
		smb_en = (aux) ? 0x28 : 0x2c;

	if (!request_muxed_region(SB800_PIIX4_SMB_IDX, 2, "sb800_piix4_smb")) {
		dev_err(&PIIX4_dev->dev,
			"SMB base address index region 0x%x already in use.\n",
			SB800_PIIX4_SMB_IDX);
		return -EBUSY;
	}

	outb_p(smb_en, SB800_PIIX4_SMB_IDX);
	smba_en_lo = inb_p(SB800_PIIX4_SMB_IDX + 1);
	outb_p(smb_en + 1, SB800_PIIX4_SMB_IDX);
	smba_en_hi = inb_p(SB800_PIIX4_SMB_IDX + 1);

	release_region(SB800_PIIX4_SMB_IDX, 2);

	if (!smb_en) {
		smb_en_status = smba_en_lo & 0x10;
		piix4_smba = smba_en_hi << 8;
		if (aux)
			piix4_smba |= 0x20;
	} else {
		smb_en_status = smba_en_lo & 0x01;
		piix4_smba = ((smba_en_hi << 8) | smba_en_lo) & 0xffe0;
	}

	if (!smb_en_status) {
		dev_err(&PIIX4_dev->dev,
			"SMBus Host Controller not enabled!\n");
		return -ENODEV;
	}

	if (acpi_check_region(piix4_smba, SMBIOSIZE, piix4_driver.name))
		return -ENODEV;

	if (!request_region(piix4_smba, SMBIOSIZE, piix4_driver.name)) {
		dev_err(&PIIX4_dev->dev, "SMBus region 0x%x already in use!\n",
			piix4_smba);
		return -EBUSY;
	}

	/* Aux SMBus does not support IRQ information */
	if (aux) {
		dev_info(&PIIX4_dev->dev,
			 "Auxiliary SMBus Host Controller at 0x%x\n",
			 piix4_smba);
		return piix4_smba;
	}

	/* Request the SMBus I2C bus config region */
	if (!request_region(piix4_smba + i2ccfg_offset, 1, "i2ccfg")) {
		dev_err(&PIIX4_dev->dev, "SMBus I2C bus config region "
			"0x%x already in use!\n", piix4_smba + i2ccfg_offset);
		release_region(piix4_smba, SMBIOSIZE);
		return -EBUSY;
	}
	i2ccfg = inb_p(piix4_smba + i2ccfg_offset);
	release_region(piix4_smba + i2ccfg_offset, 1);

	if (i2ccfg & 1)
		dev_dbg(&PIIX4_dev->dev, "Using IRQ for SMBus\n");
	else
		dev_dbg(&PIIX4_dev->dev, "Using SMI# for SMBus\n");

	dev_info(&PIIX4_dev->dev,
		 "SMBus Host Controller at 0x%x, revision %d\n",
		 piix4_smba, i2ccfg >> 4);

	/* Find which register is used for port selection */
	if (PIIX4_dev->vendor == PCI_VENDOR_ID_AMD ||
	    PIIX4_dev->vendor == PCI_VENDOR_ID_HYGON) {
		if (PIIX4_dev->device == PCI_DEVICE_ID_AMD_KERNCZ_SMBUS ||
		    (PIIX4_dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
		     PIIX4_dev->revision >= 0x1F)) {
			piix4_port_sel_sb800 = SB800_PIIX4_PORT_IDX_KERNCZ;
			piix4_port_mask_sb800 = SB800_PIIX4_PORT_IDX_MASK_KERNCZ;
			piix4_port_shift_sb800 = SB800_PIIX4_PORT_IDX_SHIFT_KERNCZ;
		} else {
			piix4_port_sel_sb800 = SB800_PIIX4_PORT_IDX_ALT;
			piix4_port_mask_sb800 = SB800_PIIX4_PORT_IDX_MASK;
			piix4_port_shift_sb800 = SB800_PIIX4_PORT_IDX_SHIFT;
		}
	} else {
		if (!request_muxed_region(SB800_PIIX4_SMB_IDX, 2,
					  "sb800_piix4_smb")) {
			release_region(piix4_smba, SMBIOSIZE);
			return -EBUSY;
		}

		outb_p(SB800_PIIX4_PORT_IDX_SEL, SB800_PIIX4_SMB_IDX);
		port_sel = inb_p(SB800_PIIX4_SMB_IDX + 1);
		piix4_port_sel_sb800 = (port_sel & 0x01) ?
				       SB800_PIIX4_PORT_IDX_ALT :
				       SB800_PIIX4_PORT_IDX;
		piix4_port_mask_sb800 = SB800_PIIX4_PORT_IDX_MASK;
		piix4_port_shift_sb800 = SB800_PIIX4_PORT_IDX_SHIFT;
		release_region(SB800_PIIX4_SMB_IDX, 2);
	}

	dev_info(&PIIX4_dev->dev,
		 "Using register 0x%02x for SMBus port selection\n",
		 (unsigned int)piix4_port_sel_sb800);

	return piix4_smba;
}