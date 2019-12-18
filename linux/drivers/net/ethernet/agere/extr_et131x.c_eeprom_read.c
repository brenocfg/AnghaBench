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
struct pci_dev {int dummy; } ;
struct et131x_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LBCIF_ADDRESS_REGISTER ; 
 int /*<<< orphan*/  LBCIF_CONTROL_LBCIF_ENABLE ; 
 int /*<<< orphan*/  LBCIF_CONTROL_REGISTER ; 
 int LBCIF_STATUS_ACK_ERROR ; 
 int eeprom_wait_ready (struct pci_dev*,int*) ; 
 scalar_t__ pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int eeprom_read(struct et131x_adapter *adapter, u32 addr, u8 *pdata)
{
	struct pci_dev *pdev = adapter->pdev;
	int err;
	u32 status;

	/* A single byte read is similar to the single byte write, with the
	 * exception of the data flow:
	 */
	err = eeprom_wait_ready(pdev, NULL);
	if (err < 0)
		return err;
	/* Write to the LBCIF Control Register:  bit 7=1, bit 6=0, bit 3=0,
	 * and bits 1:0 both =0.  Bit 5 should be set according to the type
	 * of EEPROM being accessed (1=two byte addressing, 0=one byte
	 * addressing).
	 */
	if (pci_write_config_byte(pdev, LBCIF_CONTROL_REGISTER,
				  LBCIF_CONTROL_LBCIF_ENABLE))
		return -EIO;
	/* Write the address to the LBCIF Address Register (I2C read will
	 * begin).
	 */
	if (pci_write_config_dword(pdev, LBCIF_ADDRESS_REGISTER, addr))
		return -EIO;
	/* Monitor bit 0 of the LBCIF Status Register.  When = 1, I2C read
	 * is complete. (if bit 1 =1 and bit 0 stays = 0, a hardware failure
	 * has occurred).
	 */
	err = eeprom_wait_ready(pdev, &status);
	if (err < 0)
		return err;
	/* Regardless of error status, read data byte from LBCIF Data
	 * Register.
	 */
	*pdata = err;

	return (status & LBCIF_STATUS_ACK_ERROR) ? -EIO : 0;
}