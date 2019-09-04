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
struct pci_dev {int revision; int /*<<< orphan*/  dev; } ;
struct et131x_adapter {int has_eeprom; int* eeprom_data; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ET1310_PCI_EEPROM_STATUS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  eeprom_read (struct et131x_adapter*,int,int*) ; 
 scalar_t__ eeprom_write (struct et131x_adapter*,int,int const) ; 
 scalar_t__ pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int et131x_init_eeprom(struct et131x_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	u8 eestatus;

	pci_read_config_byte(pdev, ET1310_PCI_EEPROM_STATUS, &eestatus);

	/* THIS IS A WORKAROUND:
	 * I need to call this function twice to get my card in a
	 * LG M1 Express Dual running. I tried also a msleep before this
	 * function, because I thought there could be some time conditions
	 * but it didn't work. Call the whole function twice also work.
	 */
	if (pci_read_config_byte(pdev, ET1310_PCI_EEPROM_STATUS, &eestatus)) {
		dev_err(&pdev->dev,
			"Could not read PCI config space for EEPROM Status\n");
		return -EIO;
	}

	/* Determine if the error(s) we care about are present. If they are
	 * present we need to fail.
	 */
	if (eestatus & 0x4C) {
		int write_failed = 0;

		if (pdev->revision == 0x01) {
			int	i;
			static const u8 eedata[4] = { 0xFE, 0x13, 0x10, 0xFF };

			/* Re-write the first 4 bytes if we have an eeprom
			 * present and the revision id is 1, this fixes the
			 * corruption seen with 1310 B Silicon
			 */
			for (i = 0; i < 3; i++)
				if (eeprom_write(adapter, i, eedata[i]) < 0)
					write_failed = 1;
		}
		if (pdev->revision  != 0x01 || write_failed) {
			dev_err(&pdev->dev,
				"Fatal EEPROM Status Error - 0x%04x\n",
				eestatus);

			/* This error could mean that there was an error
			 * reading the eeprom or that the eeprom doesn't exist.
			 * We will treat each case the same and not try to
			 * gather additional information that normally would
			 * come from the eeprom, like MAC Address
			 */
			adapter->has_eeprom = 0;
			return -EIO;
		}
	}
	adapter->has_eeprom = 1;

	/* Read the EEPROM for information regarding LED behavior. Refer to
	 * et131x_xcvr_init() for its use.
	 */
	eeprom_read(adapter, 0x70, &adapter->eeprom_data[0]);
	eeprom_read(adapter, 0x71, &adapter->eeprom_data[1]);

	if (adapter->eeprom_data[0] != 0xcd)
		/* Disable all optional features */
		adapter->eeprom_data[1] = 0x00;

	return 0;
}