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
typedef  int u64 ;
typedef  int u32 ;
struct nand_chip {int bbt_options; int bbt_erase_shift; int /*<<< orphan*/  base; } ;
struct nand_bbt_descr {int len; int options; int offs; scalar_t__ veroffs; } ;
struct mtd_info {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_NRBITS_MSK ; 
 int NAND_BBT_PERCHIP ; 
 int NAND_BBT_SAVECONTENT ; 
 int NAND_BBT_USE_FLASH ; 
 int NAND_BBT_VERSION ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int nanddev_target_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void verify_bbt_descr(struct nand_chip *this, struct nand_bbt_descr *bd)
{
	u64 targetsize = nanddev_target_size(&this->base);
	struct mtd_info *mtd = nand_to_mtd(this);
	u32 pattern_len;
	u32 bits;
	u32 table_size;

	if (!bd)
		return;

	pattern_len = bd->len;
	bits = bd->options & NAND_BBT_NRBITS_MSK;

	BUG_ON((this->bbt_options & NAND_BBT_NO_OOB) &&
			!(this->bbt_options & NAND_BBT_USE_FLASH));
	BUG_ON(!bits);

	if (bd->options & NAND_BBT_VERSION)
		pattern_len++;

	if (bd->options & NAND_BBT_NO_OOB) {
		BUG_ON(!(this->bbt_options & NAND_BBT_USE_FLASH));
		BUG_ON(!(this->bbt_options & NAND_BBT_NO_OOB));
		BUG_ON(bd->offs);
		if (bd->options & NAND_BBT_VERSION)
			BUG_ON(bd->veroffs != bd->len);
		BUG_ON(bd->options & NAND_BBT_SAVECONTENT);
	}

	if (bd->options & NAND_BBT_PERCHIP)
		table_size = targetsize >> this->bbt_erase_shift;
	else
		table_size = mtd->size >> this->bbt_erase_shift;
	table_size >>= 3;
	table_size *= bits;
	if (bd->options & NAND_BBT_NO_OOB)
		table_size += pattern_len;
	BUG_ON(table_size > (1 << this->bbt_erase_shift));
}