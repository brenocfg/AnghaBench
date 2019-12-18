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
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DEFAULT_BASE ; 
 int I2C_PCF_CLK ; 
 int I2C_PCF_TRNS90 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_CONTAQ_82C693 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_CONTAQ ; 
 int base ; 
 int clock ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned char) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int mmapped ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int,unsigned char*) ; 

__attribute__((used)) static int elektor_match(struct device *dev, unsigned int id)
{
#ifdef __alpha__
	/* check to see we have memory mapped PCF8584 connected to the
	Cypress cy82c693 PCI-ISA bridge as on UP2000 board */
	if (base == 0) {
		struct pci_dev *cy693_dev;

		cy693_dev = pci_get_device(PCI_VENDOR_ID_CONTAQ,
					   PCI_DEVICE_ID_CONTAQ_82C693, NULL);
		if (cy693_dev) {
			unsigned char config;
			/* yeap, we've found cypress, let's check config */
			if (!pci_read_config_byte(cy693_dev, 0x47, &config)) {

				dev_dbg(dev, "found cy82c693, config "
					"register 0x47 = 0x%02x\n", config);

				/* UP2000 board has this register set to 0xe1,
				   but the most significant bit as seems can be
				   reset during the proper initialisation
				   sequence if guys from API decides to do that
				   (so, we can even enable Tsunami Pchip
				   window for the upper 1 Gb) */

				/* so just check for ROMCS at 0xe0000,
				   ROMCS enabled for writes
				   and external XD Bus buffer in use. */
				if ((config & 0x7f) == 0x61) {
					/* seems to be UP2000 like board */
					base = 0xe0000;
					mmapped = 1;
					/* UP2000 drives ISA with
					   8.25 MHz (PCI/4) clock
					   (this can be read from cypress) */
					clock = I2C_PCF_CLK | I2C_PCF_TRNS90;
					dev_info(dev, "found API UP2000 like "
						 "board, will probe PCF8584 "
						 "later\n");
				}
			}
			pci_dev_put(cy693_dev);
		}
	}
#endif

	/* sanity checks for mmapped I/O */
	if (mmapped && base < 0xc8000) {
		dev_err(dev, "incorrect base address (%#x) specified "
		       "for mmapped I/O\n", base);
		return 0;
	}

	if (base == 0) {
		base = DEFAULT_BASE;
	}
	return 1;
}