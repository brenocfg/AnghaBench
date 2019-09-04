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
struct nand_chip {int bbt_erase_shift; int (* block_markbad ) (struct mtd_info*,int) ;} ;
struct nand_bbt_descr {int* pages; } ;
struct mtd_info {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BBT_BLOCK_WORN ; 
 int /*<<< orphan*/  bbt_mark_entry (struct nand_chip*,int,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int stub1 (struct mtd_info*,int) ; 

__attribute__((used)) static void mark_bbt_block_bad(struct nand_chip *this,
			       struct nand_bbt_descr *td,
			       int chip, int block)
{
	struct mtd_info *mtd = nand_to_mtd(this);
	loff_t to;
	int res;

	bbt_mark_entry(this, block, BBT_BLOCK_WORN);

	to = (loff_t)block << this->bbt_erase_shift;
	res = this->block_markbad(mtd, to);
	if (res)
		pr_warn("nand_bbt: error %d while marking block %d bad\n",
			res, block);

	td->pages[chip] = -1;
}