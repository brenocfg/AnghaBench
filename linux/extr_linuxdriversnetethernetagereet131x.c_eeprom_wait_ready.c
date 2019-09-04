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
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  LBCIF_DWORD1_GROUP ; 
 int MAX_NUM_REGISTER_POLLS ; 
 scalar_t__ pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int eeprom_wait_ready(struct pci_dev *pdev, u32 *status)
{
	u32 reg;
	int i;

	/* 1. Check LBCIF Status Register for bits 6 & 3:2 all equal to 0 and
	 *    bits 7,1:0 both equal to 1, at least once after reset.
	 *    Subsequent operations need only to check that bits 1:0 are equal
	 *    to 1 prior to starting a single byte read/write
	 */
	for (i = 0; i < MAX_NUM_REGISTER_POLLS; i++) {
		if (pci_read_config_dword(pdev, LBCIF_DWORD1_GROUP, &reg))
			return -EIO;

		/* I2C idle and Phy Queue Avail both true */
		if ((reg & 0x3000) == 0x3000) {
			if (status)
				*status = reg;
			return reg & 0xFF;
		}
	}
	return -ETIMEDOUT;
}