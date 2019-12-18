#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int strength; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {TYPE_1__ ecc; } ;
struct vf610_nfc {int data_access; TYPE_2__ chip; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; } ;

/* Variables and functions */
 scalar_t__ ECC_SRAM_ADDR ; 
 scalar_t__ ECC_STATUS ; 
 int ECC_STATUS_ERR_COUNT ; 
 int ECC_STATUS_MASK ; 
 scalar_t__ NFC_MAIN_AREA (int /*<<< orphan*/ ) ; 
 struct vf610_nfc* chip_to_nfc (struct nand_chip*) ; 
 int nand_check_erased_ecc_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nand_read_oob_op (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int vf610_nfc_read (struct vf610_nfc*,scalar_t__) ; 

__attribute__((used)) static inline int vf610_nfc_correct_data(struct nand_chip *chip, uint8_t *dat,
					 uint8_t *oob, int page)
{
	struct vf610_nfc *nfc = chip_to_nfc(chip);
	struct mtd_info *mtd = nand_to_mtd(chip);
	u32 ecc_status_off = NFC_MAIN_AREA(0) + ECC_SRAM_ADDR + ECC_STATUS;
	u8 ecc_status;
	u8 ecc_count;
	int flips_threshold = nfc->chip.ecc.strength / 2;

	ecc_status = vf610_nfc_read(nfc, ecc_status_off) & 0xff;
	ecc_count = ecc_status & ECC_STATUS_ERR_COUNT;

	if (!(ecc_status & ECC_STATUS_MASK))
		return ecc_count;

	nfc->data_access = true;
	nand_read_oob_op(&nfc->chip, page, 0, oob, mtd->oobsize);
	nfc->data_access = false;

	/*
	 * On an erased page, bit count (including OOB) should be zero or
	 * at least less then half of the ECC strength.
	 */
	return nand_check_erased_ecc_chunk(dat, nfc->chip.ecc.size, oob,
					   mtd->oobsize, NULL, 0,
					   flips_threshold);
}