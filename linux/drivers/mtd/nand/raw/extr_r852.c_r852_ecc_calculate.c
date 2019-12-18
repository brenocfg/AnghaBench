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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct sm_oob {int* ecc1; int* ecc2; } ;
struct r852_device {int ctlreg; scalar_t__ card_unstable; } ;
struct nand_chip {int dummy; } ;
typedef  int ecc2 ;
typedef  int ecc1 ;

/* Variables and functions */
 int /*<<< orphan*/  R852_CTL ; 
 int R852_CTL_ECC_ACCESS ; 
 int R852_CTL_ECC_ENABLE ; 
 int /*<<< orphan*/  R852_DATALINE ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct r852_device* r852_get_dev (int /*<<< orphan*/ ) ; 
 int r852_read_reg_dword (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg (struct r852_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r852_ecc_calculate(struct nand_chip *chip, const uint8_t *dat,
			      uint8_t *ecc_code)
{
	struct r852_device *dev = r852_get_dev(nand_to_mtd(chip));
	struct sm_oob *oob = (struct sm_oob *)ecc_code;
	uint32_t ecc1, ecc2;

	if (dev->card_unstable)
		return 0;

	dev->ctlreg &= ~R852_CTL_ECC_ENABLE;
	r852_write_reg(dev, R852_CTL, dev->ctlreg | R852_CTL_ECC_ACCESS);

	ecc1 = r852_read_reg_dword(dev, R852_DATALINE);
	ecc2 = r852_read_reg_dword(dev, R852_DATALINE);

	oob->ecc1[0] = (ecc1) & 0xFF;
	oob->ecc1[1] = (ecc1 >> 8) & 0xFF;
	oob->ecc1[2] = (ecc1 >> 16) & 0xFF;

	oob->ecc2[0] = (ecc2) & 0xFF;
	oob->ecc2[1] = (ecc2 >> 8) & 0xFF;
	oob->ecc2[2] = (ecc2 >> 16) & 0xFF;

	r852_write_reg(dev, R852_CTL, dev->ctlreg);
	return 0;
}