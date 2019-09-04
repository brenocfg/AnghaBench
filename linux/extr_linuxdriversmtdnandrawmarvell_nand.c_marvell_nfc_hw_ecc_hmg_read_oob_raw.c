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
struct nand_chip {int pagebuf; int /*<<< orphan*/  oob_poi; int /*<<< orphan*/  data_buf; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int marvell_nfc_hw_ecc_hmg_do_read_page (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_hmg_read_oob_raw(struct mtd_info *mtd,
					       struct nand_chip *chip, int page)
{
	/* Invalidate page cache */
	chip->pagebuf = -1;

	return marvell_nfc_hw_ecc_hmg_do_read_page(chip, chip->data_buf,
						   chip->oob_poi, true, page);
}