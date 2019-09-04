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
typedef  int u32 ;
struct nand_ecc_ctrl {int size; int bytes; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; struct nand_ecc_ctrl ecc; } ;
struct mtd_info {scalar_t__ writesize; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_disable (struct mtd_info*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_enable (struct mtd_info*) ; 
 int sunxi_nfc_hw_ecc_read_chunk (struct mtd_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,int*,unsigned int*,int,int,int) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_read_subpage(struct mtd_info *mtd,
					 struct nand_chip *chip,
					 u32 data_offs, u32 readlen,
					 u8 *bufpoi, int page)
{
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int ret, i, cur_off = 0;
	unsigned int max_bitflips = 0;

	nand_read_page_op(chip, page, 0, NULL, 0);

	sunxi_nfc_hw_ecc_enable(mtd);

	for (i = data_offs / ecc->size;
	     i < DIV_ROUND_UP(data_offs + readlen, ecc->size); i++) {
		int data_off = i * ecc->size;
		int oob_off = i * (ecc->bytes + 4);
		u8 *data = bufpoi + data_off;
		u8 *oob = chip->oob_poi + oob_off;

		ret = sunxi_nfc_hw_ecc_read_chunk(mtd, data, data_off,
						  oob,
						  oob_off + mtd->writesize,
						  &cur_off, &max_bitflips, !i,
						  false, page);
		if (ret < 0)
			return ret;
	}

	sunxi_nfc_hw_ecc_disable(mtd);

	return max_bitflips;
}