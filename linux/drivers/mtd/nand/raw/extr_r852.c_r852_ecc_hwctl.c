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
struct r852_device {int ctlreg; scalar_t__ card_unstable; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
#define  NAND_ECC_READ 130 
#define  NAND_ECC_READSYN 129 
#define  NAND_ECC_WRITE 128 
 int /*<<< orphan*/  R852_CTL ; 
 int R852_CTL_ECC_ACCESS ; 
 int R852_CTL_ECC_ENABLE ; 
 int /*<<< orphan*/  R852_DATALINE ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 struct r852_device* r852_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_read_reg_dword (struct r852_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg (struct r852_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r852_ecc_hwctl(struct nand_chip *chip, int mode)
{
	struct r852_device *dev = r852_get_dev(nand_to_mtd(chip));

	if (dev->card_unstable)
		return;

	switch (mode) {
	case NAND_ECC_READ:
	case NAND_ECC_WRITE:
		/* enable ecc generation/check*/
		dev->ctlreg |= R852_CTL_ECC_ENABLE;

		/* flush ecc buffer */
		r852_write_reg(dev, R852_CTL,
			dev->ctlreg | R852_CTL_ECC_ACCESS);

		r852_read_reg_dword(dev, R852_DATALINE);
		r852_write_reg(dev, R852_CTL, dev->ctlreg);
		return;

	case NAND_ECC_READSYN:
		/* disable ecc generation */
		dev->ctlreg &= ~R852_CTL_ECC_ENABLE;
		r852_write_reg(dev, R852_CTL, dev->ctlreg);
	}
}