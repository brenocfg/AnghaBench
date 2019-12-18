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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/  oob_poi; int /*<<< orphan*/  cur_cs; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int marvell_nfc_hw_ecc_hmg_do_write_page (struct nand_chip*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  marvell_nfc_select_target (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nand_get_data_buf (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_hmg_write_oob_raw(struct nand_chip *chip,
						int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 *buf = nand_get_data_buf(chip);

	memset(buf, 0xFF, mtd->writesize);

	marvell_nfc_select_target(chip, chip->cur_cs);
	return marvell_nfc_hw_ecc_hmg_do_write_page(chip, buf, chip->oob_poi,
						    true, page);
}