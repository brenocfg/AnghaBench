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
struct nand_chip {int bbt_erase_shift; } ;
struct nand_bbt_descr {int* pages; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BBT_BLOCK_WORN ; 
 int /*<<< orphan*/  bbt_mark_entry (struct nand_chip*,int,int /*<<< orphan*/ ) ; 
 int nand_markbad_bbm (struct nand_chip*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 

__attribute__((used)) static void mark_bbt_block_bad(struct nand_chip *this,
			       struct nand_bbt_descr *td,
			       int chip, int block)
{
	loff_t to;
	int res;

	bbt_mark_entry(this, block, BBT_BLOCK_WORN);

	to = (loff_t)block << this->bbt_erase_shift;
	res = nand_markbad_bbm(this, to);
	if (res)
		pr_warn("nand_bbt: error %d while marking block %d bad\n",
			res, block);

	td->pages[chip] = -1;
}