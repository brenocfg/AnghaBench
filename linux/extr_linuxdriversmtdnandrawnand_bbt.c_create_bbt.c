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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int bbt_erase_shift; int numchips; int chipsize; int bbt_options; } ;
struct nand_bbt_descr {int options; } ;
struct TYPE_2__ {int /*<<< orphan*/  badblocks; } ;
struct mtd_info {int size; int erasesize; int writesize; TYPE_1__ ecc_stats; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BBT_BLOCK_FACTORY_BAD ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_SCAN2NDPAGE ; 
 int NAND_BBT_SCANLASTPAGE ; 
 int /*<<< orphan*/  bbt_mark_entry (struct nand_chip*,int,int /*<<< orphan*/ ) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,unsigned long long) ; 
 int scan_block_fast (struct mtd_info*,struct nand_bbt_descr*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int create_bbt(struct mtd_info *mtd, uint8_t *buf,
	struct nand_bbt_descr *bd, int chip)
{
	struct nand_chip *this = mtd_to_nand(mtd);
	int i, numblocks, numpages;
	int startblock;
	loff_t from;

	pr_info("Scanning device for bad blocks\n");

	if (bd->options & NAND_BBT_SCAN2NDPAGE)
		numpages = 2;
	else
		numpages = 1;

	if (chip == -1) {
		numblocks = mtd->size >> this->bbt_erase_shift;
		startblock = 0;
		from = 0;
	} else {
		if (chip >= this->numchips) {
			pr_warn("create_bbt(): chipnr (%d) > available chips (%d)\n",
			       chip + 1, this->numchips);
			return -EINVAL;
		}
		numblocks = this->chipsize >> this->bbt_erase_shift;
		startblock = chip * numblocks;
		numblocks += startblock;
		from = (loff_t)startblock << this->bbt_erase_shift;
	}

	if (this->bbt_options & NAND_BBT_SCANLASTPAGE)
		from += mtd->erasesize - (mtd->writesize * numpages);

	for (i = startblock; i < numblocks; i++) {
		int ret;

		BUG_ON(bd->options & NAND_BBT_NO_OOB);

		ret = scan_block_fast(mtd, bd, from, buf, numpages);
		if (ret < 0)
			return ret;

		if (ret) {
			bbt_mark_entry(this, i, BBT_BLOCK_FACTORY_BAD);
			pr_warn("Bad eraseblock %d at 0x%012llx\n",
				i, (unsigned long long)from);
			mtd->ecc_stats.badblocks++;
		}

		from += (1 << this->bbt_erase_shift);
	}
	return 0;
}