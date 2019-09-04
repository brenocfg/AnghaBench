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
struct mtd_info {int oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_change_read_column_op (struct nand_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sunxi_nfc_randomizer_read_buf (struct mtd_info*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_read_buf (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sunxi_nfc_hw_ecc_read_extra_oob(struct mtd_info *mtd,
					    u8 *oob, int *cur_off,
					    bool randomize, int page)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &nand->ecc;
	int offset = ((ecc->bytes + 4) * ecc->steps);
	int len = mtd->oobsize - offset;

	if (len <= 0)
		return;

	if (!cur_off || *cur_off != offset)
		nand_change_read_column_op(nand, mtd->writesize, NULL, 0,
					   false);

	if (!randomize)
		sunxi_nfc_read_buf(mtd, oob + offset, len);
	else
		sunxi_nfc_randomizer_read_buf(mtd, oob + offset, len,
					      false, page);

	if (cur_off)
		*cur_off = mtd->oobsize + mtd->writesize;
}