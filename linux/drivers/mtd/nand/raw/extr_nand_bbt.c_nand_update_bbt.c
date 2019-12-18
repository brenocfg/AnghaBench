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
struct nand_chip {int bbt_erase_shift; int page_shift; int chip_shift; int /*<<< orphan*/  bbt; struct nand_bbt_descr* bbt_md; struct nand_bbt_descr* bbt_td; } ;
struct nand_bbt_descr {int options; int /*<<< orphan*/ * version; } ;
struct mtd_info {int oobsize; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NAND_BBT_PERCHIP ; 
 int NAND_BBT_WRITE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int write_bbt (struct nand_chip*,int /*<<< orphan*/ *,struct nand_bbt_descr*,struct nand_bbt_descr*,int) ; 

__attribute__((used)) static int nand_update_bbt(struct nand_chip *this, loff_t offs)
{
	struct mtd_info *mtd = nand_to_mtd(this);
	int len, res = 0;
	int chip, chipsel;
	uint8_t *buf;
	struct nand_bbt_descr *td = this->bbt_td;
	struct nand_bbt_descr *md = this->bbt_md;

	if (!this->bbt || !td)
		return -EINVAL;

	/* Allocate a temporary buffer for one eraseblock incl. oob */
	len = (1 << this->bbt_erase_shift);
	len += (len >> this->page_shift) * mtd->oobsize;
	buf = kmalloc(len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	/* Do we have a bbt per chip? */
	if (td->options & NAND_BBT_PERCHIP) {
		chip = (int)(offs >> this->chip_shift);
		chipsel = chip;
	} else {
		chip = 0;
		chipsel = -1;
	}

	td->version[chip]++;
	if (md)
		md->version[chip]++;

	/* Write the bad block table to the device? */
	if (td->options & NAND_BBT_WRITE) {
		res = write_bbt(this, buf, td, md, chipsel);
		if (res < 0)
			goto out;
	}
	/* Write the mirror bad block table to the device? */
	if (md && (md->options & NAND_BBT_WRITE)) {
		res = write_bbt(this, buf, md, td, chipsel);
	}

 out:
	kfree(buf);
	return res;
}