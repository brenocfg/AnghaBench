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
typedef  int uint8_t ;
typedef  scalar_t__ u32 ;
struct nand_chip {size_t page_shift; int bbt_erase_shift; } ;
struct nand_bbt_descr {int options; int reserved_block_code; } ;
struct TYPE_2__ {int /*<<< orphan*/  badblocks; int /*<<< orphan*/  bbtblocks; } ;
struct mtd_info {size_t writesize; TYPE_1__ ecc_stats; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BBT_BLOCK_FACTORY_BAD ; 
 int /*<<< orphan*/  BBT_BLOCK_RESERVED ; 
 int /*<<< orphan*/  BBT_BLOCK_WORN ; 
 int NAND_BBT_NRBITS_MSK ; 
 scalar_t__ add_marker_len (struct nand_bbt_descr*) ; 
 int /*<<< orphan*/  bbt_mark_entry (struct nand_chip*,int,int /*<<< orphan*/ ) ; 
 size_t min (size_t,size_t) ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int mtd_read (struct mtd_info*,size_t,size_t,size_t*,int*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int read_bbt(struct nand_chip *this, uint8_t *buf, int page, int num,
		    struct nand_bbt_descr *td, int offs)
{
	struct mtd_info *mtd = nand_to_mtd(this);
	int res, ret = 0, i, j, act = 0;
	size_t retlen, len, totlen;
	loff_t from;
	int bits = td->options & NAND_BBT_NRBITS_MSK;
	uint8_t msk = (uint8_t)((1 << bits) - 1);
	u32 marker_len;
	int reserved_block_code = td->reserved_block_code;

	totlen = (num * bits) >> 3;
	marker_len = add_marker_len(td);
	from = ((loff_t)page) << this->page_shift;

	while (totlen) {
		len = min(totlen, (size_t)(1 << this->bbt_erase_shift));
		if (marker_len) {
			/*
			 * In case the BBT marker is not in the OOB area it
			 * will be just in the first page.
			 */
			len -= marker_len;
			from += marker_len;
			marker_len = 0;
		}
		res = mtd_read(mtd, from, len, &retlen, buf);
		if (res < 0) {
			if (mtd_is_eccerr(res)) {
				pr_info("nand_bbt: ECC error in BBT at 0x%012llx\n",
					from & ~mtd->writesize);
				return res;
			} else if (mtd_is_bitflip(res)) {
				pr_info("nand_bbt: corrected error in BBT at 0x%012llx\n",
					from & ~mtd->writesize);
				ret = res;
			} else {
				pr_info("nand_bbt: error reading BBT\n");
				return res;
			}
		}

		/* Analyse data */
		for (i = 0; i < len; i++) {
			uint8_t dat = buf[i];
			for (j = 0; j < 8; j += bits, act++) {
				uint8_t tmp = (dat >> j) & msk;
				if (tmp == msk)
					continue;
				if (reserved_block_code && (tmp == reserved_block_code)) {
					pr_info("nand_read_bbt: reserved block at 0x%012llx\n",
						 (loff_t)(offs + act) <<
						 this->bbt_erase_shift);
					bbt_mark_entry(this, offs + act,
							BBT_BLOCK_RESERVED);
					mtd->ecc_stats.bbtblocks++;
					continue;
				}
				/*
				 * Leave it for now, if it's matured we can
				 * move this message to pr_debug.
				 */
				pr_info("nand_read_bbt: bad block at 0x%012llx\n",
					 (loff_t)(offs + act) <<
					 this->bbt_erase_shift);
				/* Factory marked bad or worn out? */
				if (tmp == 0)
					bbt_mark_entry(this, offs + act,
							BBT_BLOCK_FACTORY_BAD);
				else
					bbt_mark_entry(this, offs + act,
							BBT_BLOCK_WORN);
				mtd->ecc_stats.badblocks++;
			}
		}
		totlen -= len;
		from += len;
	}
	return ret;
}