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
struct nand_ecc_ctrl {int bytes; int steps; } ;
struct nand_chip {struct nand_ecc_ctrl ecc; } ;
struct mtd_info {int oobsize; int writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_change_write_column_op (struct nand_chip*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_write_buf (struct nand_chip*,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void sunxi_nfc_hw_ecc_write_extra_oob(struct nand_chip *nand,
					     u8 *oob, int *cur_off,
					     int page)
{
	struct mtd_info *mtd = nand_to_mtd(nand);
	struct nand_ecc_ctrl *ecc = &nand->ecc;
	int offset = ((ecc->bytes + 4) * ecc->steps);
	int len = mtd->oobsize - offset;

	if (len <= 0)
		return;

	if (!cur_off || *cur_off != offset)
		nand_change_write_column_op(nand, offset + mtd->writesize,
					    NULL, 0, false);

	sunxi_nfc_randomizer_write_buf(nand, oob + offset, len, false, page);

	if (cur_off)
		*cur_off = mtd->oobsize + mtd->writesize;
}