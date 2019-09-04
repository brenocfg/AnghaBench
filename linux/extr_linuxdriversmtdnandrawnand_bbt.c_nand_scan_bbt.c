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
struct nand_chip {int bbt_erase_shift; int page_shift; int /*<<< orphan*/ * bbt; struct nand_bbt_descr* bbt_md; struct nand_bbt_descr* bbt_td; } ;
struct nand_bbt_descr {int options; } ;
struct mtd_info {int size; int oobsize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NAND_BBT_ABSPAGE ; 
 int check_create (struct mtd_info*,int /*<<< orphan*/ *,struct nand_bbt_descr*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_bbt_region (struct mtd_info*,struct nand_bbt_descr*) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int nand_memory_bbt (struct mtd_info*,struct nand_bbt_descr*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  read_abs_bbts (struct mtd_info*,int /*<<< orphan*/ *,struct nand_bbt_descr*,struct nand_bbt_descr*) ; 
 int /*<<< orphan*/  search_read_bbts (struct mtd_info*,int /*<<< orphan*/ *,struct nand_bbt_descr*,struct nand_bbt_descr*) ; 
 int /*<<< orphan*/  verify_bbt_descr (struct mtd_info*,struct nand_bbt_descr*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (int) ; 

__attribute__((used)) static int nand_scan_bbt(struct mtd_info *mtd, struct nand_bbt_descr *bd)
{
	struct nand_chip *this = mtd_to_nand(mtd);
	int len, res;
	uint8_t *buf;
	struct nand_bbt_descr *td = this->bbt_td;
	struct nand_bbt_descr *md = this->bbt_md;

	len = (mtd->size >> (this->bbt_erase_shift + 2)) ? : 1;
	/*
	 * Allocate memory (2bit per block) and clear the memory bad block
	 * table.
	 */
	this->bbt = kzalloc(len, GFP_KERNEL);
	if (!this->bbt)
		return -ENOMEM;

	/*
	 * If no primary table decriptor is given, scan the device to build a
	 * memory based bad block table.
	 */
	if (!td) {
		if ((res = nand_memory_bbt(mtd, bd))) {
			pr_err("nand_bbt: can't scan flash and build the RAM-based BBT\n");
			goto err;
		}
		return 0;
	}
	verify_bbt_descr(mtd, td);
	verify_bbt_descr(mtd, md);

	/* Allocate a temporary buffer for one eraseblock incl. oob */
	len = (1 << this->bbt_erase_shift);
	len += (len >> this->page_shift) * mtd->oobsize;
	buf = vmalloc(len);
	if (!buf) {
		res = -ENOMEM;
		goto err;
	}

	/* Is the bbt at a given page? */
	if (td->options & NAND_BBT_ABSPAGE) {
		read_abs_bbts(mtd, buf, td, md);
	} else {
		/* Search the bad block table using a pattern in oob */
		search_read_bbts(mtd, buf, td, md);
	}

	res = check_create(mtd, buf, bd);
	if (res)
		goto err;

	/* Prevent the bbt regions from erasing / writing */
	mark_bbt_region(mtd, td);
	if (md)
		mark_bbt_region(mtd, md);

	vfree(buf);
	return 0;

err:
	kfree(this->bbt);
	this->bbt = NULL;
	return res;
}