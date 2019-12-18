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
typedef  int u16 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ MS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QCA9887_EEPROM_ADDR_HI ; 
 int /*<<< orphan*/  QCA9887_EEPROM_ADDR_LO ; 
 int QCA9887_EEPROM_SELECT_READ ; 
 scalar_t__ SI_BASE_ADDRESS ; 
 int /*<<< orphan*/  SI_CS_DONE_ERR ; 
 int /*<<< orphan*/  SI_CS_DONE_INT ; 
 scalar_t__ SI_CS_OFFSET ; 
 int /*<<< orphan*/  SI_CS_RX_CNT ; 
 int /*<<< orphan*/  SI_CS_START ; 
 int /*<<< orphan*/  SI_CS_TX_CNT ; 
 scalar_t__ SI_RX_DATA0_OFFSET ; 
 scalar_t__ SI_TX_DATA0_OFFSET ; 
 int SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int ath10k_pci_read32 (struct ath10k*,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_pci_write32 (struct ath10k*,scalar_t__,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ath10k_pci_read_eeprom(struct ath10k *ar, u16 addr, u8 *out)
{
	u32 reg;
	int wait_limit;

	/* set device select byte and for the read operation */
	reg = QCA9887_EEPROM_SELECT_READ |
	      SM(addr, QCA9887_EEPROM_ADDR_LO) |
	      SM(addr >> 8, QCA9887_EEPROM_ADDR_HI);
	ath10k_pci_write32(ar, SI_BASE_ADDRESS + SI_TX_DATA0_OFFSET, reg);

	/* write transmit data, transfer length, and START bit */
	ath10k_pci_write32(ar, SI_BASE_ADDRESS + SI_CS_OFFSET,
			   SM(1, SI_CS_START) | SM(1, SI_CS_RX_CNT) |
			   SM(4, SI_CS_TX_CNT));

	/* wait max 1 sec */
	wait_limit = 100000;

	/* wait for SI_CS_DONE_INT */
	do {
		reg = ath10k_pci_read32(ar, SI_BASE_ADDRESS + SI_CS_OFFSET);
		if (MS(reg, SI_CS_DONE_INT))
			break;

		wait_limit--;
		udelay(10);
	} while (wait_limit > 0);

	if (!MS(reg, SI_CS_DONE_INT)) {
		ath10k_err(ar, "timeout while reading device EEPROM at %04x\n",
			   addr);
		return -ETIMEDOUT;
	}

	/* clear SI_CS_DONE_INT */
	ath10k_pci_write32(ar, SI_BASE_ADDRESS + SI_CS_OFFSET, reg);

	if (MS(reg, SI_CS_DONE_ERR)) {
		ath10k_err(ar, "failed to read device EEPROM at %04x\n", addr);
		return -EIO;
	}

	/* extract receive data */
	reg = ath10k_pci_read32(ar, SI_BASE_ADDRESS + SI_RX_DATA0_OFFSET);
	*out = reg;

	return 0;
}