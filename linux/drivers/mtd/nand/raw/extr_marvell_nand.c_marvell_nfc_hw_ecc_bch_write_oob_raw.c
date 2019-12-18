#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int (* write_page_raw ) (struct nand_chip*,int /*<<< orphan*/ *,int,int) ;} ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nand_get_data_buf (struct nand_chip*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int stub1 (struct nand_chip*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int marvell_nfc_hw_ecc_bch_write_oob_raw(struct nand_chip *chip,
						int page)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 *buf = nand_get_data_buf(chip);

	memset(buf, 0xFF, mtd->writesize);

	return chip->ecc.write_page_raw(chip, buf, true, page);
}