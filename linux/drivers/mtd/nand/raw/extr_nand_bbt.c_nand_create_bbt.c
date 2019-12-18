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
struct nand_chip {int bbt_options; int /*<<< orphan*/  badblock_pattern; int /*<<< orphan*/ * bbt_md; int /*<<< orphan*/ * bbt_td; } ;

/* Variables and functions */
 int NAND_BBT_NO_OOB ; 
 int NAND_BBT_USE_FLASH ; 
 int /*<<< orphan*/  bbt_main_descr ; 
 int /*<<< orphan*/  bbt_main_no_oob_descr ; 
 int /*<<< orphan*/  bbt_mirror_descr ; 
 int /*<<< orphan*/  bbt_mirror_no_oob_descr ; 
 int nand_create_badblock_pattern (struct nand_chip*) ; 
 int nand_scan_bbt (struct nand_chip*,int /*<<< orphan*/ ) ; 

int nand_create_bbt(struct nand_chip *this)
{
	int ret;

	/* Is a flash based bad block table requested? */
	if (this->bbt_options & NAND_BBT_USE_FLASH) {
		/* Use the default pattern descriptors */
		if (!this->bbt_td) {
			if (this->bbt_options & NAND_BBT_NO_OOB) {
				this->bbt_td = &bbt_main_no_oob_descr;
				this->bbt_md = &bbt_mirror_no_oob_descr;
			} else {
				this->bbt_td = &bbt_main_descr;
				this->bbt_md = &bbt_mirror_descr;
			}
		}
	} else {
		this->bbt_td = NULL;
		this->bbt_md = NULL;
	}

	if (!this->badblock_pattern) {
		ret = nand_create_badblock_pattern(this);
		if (ret)
			return ret;
	}

	return nand_scan_bbt(this, this->badblock_pattern);
}