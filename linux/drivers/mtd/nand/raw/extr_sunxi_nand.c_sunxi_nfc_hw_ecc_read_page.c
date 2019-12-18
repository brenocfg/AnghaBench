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
typedef  int /*<<< orphan*/  u8 ;
struct nand_ecc_ctrl {int steps; int size; int bytes; } ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  cur_cs; struct nand_ecc_ctrl ecc; } ;
struct mtd_info {scalar_t__ writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_disable (struct nand_chip*) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_enable (struct nand_chip*) ; 
 int sunxi_nfc_hw_ecc_read_chunk (struct nand_chip*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__,int*,unsigned int*,int,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_hw_ecc_read_extra_oob (struct nand_chip*,int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_select_chip (struct nand_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_read_page(struct nand_chip *nand, uint8_t *buf,
				      int oob_required, int page)
{
	struct mtd_info *mtd = nand_to_mtd(nand);
	struct nand_ecc_ctrl *ecc = &nand->ecc;
	unsigned int max_bitflips = 0;
	int ret, i, cur_off = 0;
	bool raw_mode = false;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_read_page_op(nand, page, 0, NULL, 0);

	sunxi_nfc_hw_ecc_enable(nand);

	for (i = 0; i < ecc->steps; i++) {
		int data_off = i * ecc->size;
		int oob_off = i * (ecc->bytes + 4);
		u8 *data = buf + data_off;
		u8 *oob = nand->oob_poi + oob_off;

		ret = sunxi_nfc_hw_ecc_read_chunk(nand, data, data_off, oob,
						  oob_off + mtd->writesize,
						  &cur_off, &max_bitflips,
						  !i, oob_required, page);
		if (ret < 0)
			return ret;
		else if (ret)
			raw_mode = true;
	}

	if (oob_required)
		sunxi_nfc_hw_ecc_read_extra_oob(nand, nand->oob_poi, &cur_off,
						!raw_mode, page);

	sunxi_nfc_hw_ecc_disable(nand);

	return max_bitflips;
}