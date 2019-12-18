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
struct nand_chip {int dummy; } ;
struct nand_bbt_descr {int dummy; } ;
struct mtd_oob_ops {int /*<<< orphan*/  mode; int /*<<< orphan*/ * datbuf; scalar_t__ ooboffs; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/  ooblen; } ;
struct mtd_info {int writesize; int /*<<< orphan*/  oobsize; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OPS_PLACE_OOB ; 
 scalar_t__ check_short_pattern (int /*<<< orphan*/ *,struct nand_bbt_descr*) ; 
 int /*<<< orphan*/  mtd_is_bitflip_or_eccerr (int) ; 
 int mtd_read_oob (struct mtd_info*,scalar_t__,struct mtd_oob_ops*) ; 
 int nand_bbm_get_next_page (struct nand_chip*,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 

__attribute__((used)) static int scan_block_fast(struct nand_chip *this, struct nand_bbt_descr *bd,
			   loff_t offs, uint8_t *buf)
{
	struct mtd_info *mtd = nand_to_mtd(this);

	struct mtd_oob_ops ops;
	int ret, page_offset;

	ops.ooblen = mtd->oobsize;
	ops.oobbuf = buf;
	ops.ooboffs = 0;
	ops.datbuf = NULL;
	ops.mode = MTD_OPS_PLACE_OOB;

	page_offset = nand_bbm_get_next_page(this, 0);

	while (page_offset >= 0) {
		/*
		 * Read the full oob until read_oob is fixed to handle single
		 * byte reads for 16 bit buswidth.
		 */
		ret = mtd_read_oob(mtd, offs + (page_offset * mtd->writesize),
				   &ops);
		/* Ignore ECC errors when checking for BBM */
		if (ret && !mtd_is_bitflip_or_eccerr(ret))
			return ret;

		if (check_short_pattern(buf, bd))
			return 1;

		page_offset = nand_bbm_get_next_page(this, page_offset + 1);
	}

	return 0;
}