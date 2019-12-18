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
typedef  int u32 ;
struct pci_dev {scalar_t__ revision; } ;
struct et131x_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LBCIF_ADDRESS_REGISTER ; 
 int LBCIF_CONTROL_I2C_WRITE ; 
 int LBCIF_CONTROL_LBCIF_ENABLE ; 
 int /*<<< orphan*/  LBCIF_CONTROL_REGISTER ; 
 int /*<<< orphan*/  LBCIF_DATA_REGISTER ; 
 int LBCIF_STATUS_ACK_ERROR ; 
 int LBCIF_STATUS_GENERAL_ERROR ; 
 int MAX_NUM_WRITE_RETRIES ; 
 int eeprom_wait_ready (struct pci_dev*,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int eeprom_write(struct et131x_adapter *adapter, u32 addr, u8 data)
{
	struct pci_dev *pdev = adapter->pdev;
	int index = 0;
	int retries;
	int err = 0;
	int writeok = 0;
	u32 status;
	u32 val = 0;

	/* For an EEPROM, an I2C single byte write is defined as a START
	 * condition followed by the device address, EEPROM address, one byte
	 * of data and a STOP condition.  The STOP condition will trigger the
	 * EEPROM's internally timed write cycle to the nonvolatile memory.
	 * All inputs are disabled during this write cycle and the EEPROM will
	 * not respond to any access until the internal write is complete.
	 */
	err = eeprom_wait_ready(pdev, NULL);
	if (err < 0)
		return err;

	 /* 2. Write to the LBCIF Control Register:  bit 7=1, bit 6=1, bit 3=0,
	  *    and bits 1:0 both =0.  Bit 5 should be set according to the
	  *    type of EEPROM being accessed (1=two byte addressing, 0=one
	  *    byte addressing).
	  */
	if (pci_write_config_byte(pdev, LBCIF_CONTROL_REGISTER,
				  LBCIF_CONTROL_LBCIF_ENABLE |
					LBCIF_CONTROL_I2C_WRITE))
		return -EIO;

	/* Prepare EEPROM address for Step 3 */
	for (retries = 0; retries < MAX_NUM_WRITE_RETRIES; retries++) {
		if (pci_write_config_dword(pdev, LBCIF_ADDRESS_REGISTER, addr))
			break;
		/* Write the data to the LBCIF Data Register (the I2C write
		 * will begin).
		 */
		if (pci_write_config_byte(pdev, LBCIF_DATA_REGISTER, data))
			break;
		/* Monitor bit 1:0 of the LBCIF Status Register.  When bits
		 * 1:0 are both equal to 1, the I2C write has completed and the
		 * internal write cycle of the EEPROM is about to start.
		 * (bits 1:0 = 01 is a legal state while waiting from both
		 * equal to 1, but bits 1:0 = 10 is invalid and implies that
		 * something is broken).
		 */
		err = eeprom_wait_ready(pdev, &status);
		if (err < 0)
			return 0;

		/* Check bit 3 of the LBCIF Status Register.  If  equal to 1,
		 * an error has occurred.Don't break here if we are revision
		 * 1, this is so we do a blind write for load bug.
		 */
		if ((status & LBCIF_STATUS_GENERAL_ERROR) &&
		    adapter->pdev->revision == 0)
			break;

		/* Check bit 2 of the LBCIF Status Register.  If equal to 1 an
		 * ACK error has occurred on the address phase of the write.
		 * This could be due to an actual hardware failure or the
		 * EEPROM may still be in its internal write cycle from a
		 * previous write. This write operation was ignored and must be
		  *repeated later.
		 */
		if (status & LBCIF_STATUS_ACK_ERROR) {
			/* This could be due to an actual hardware failure
			 * or the EEPROM may still be in its internal write
			 * cycle from a previous write. This write operation
			 * was ignored and must be repeated later.
			 */
			udelay(10);
			continue;
		}

		writeok = 1;
		break;
	}

	udelay(10);

	while (1) {
		if (pci_write_config_byte(pdev, LBCIF_CONTROL_REGISTER,
					  LBCIF_CONTROL_LBCIF_ENABLE))
			writeok = 0;

		/* Do read until internal ACK_ERROR goes away meaning write
		 * completed
		 */
		do {
			pci_write_config_dword(pdev,
					       LBCIF_ADDRESS_REGISTER,
					       addr);
			do {
				pci_read_config_dword(pdev,
						      LBCIF_DATA_REGISTER,
						      &val);
			} while ((val & 0x00010000) == 0);
		} while (val & 0x00040000);

		if ((val & 0xFF00) != 0xC000 || index == 10000)
			break;
		index++;
	}
	return writeok ? 0 : -EIO;
}