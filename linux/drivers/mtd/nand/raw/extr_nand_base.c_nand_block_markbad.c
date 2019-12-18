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
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtd_to_nand (struct mtd_info*) ; 
 int nand_block_isbad (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int nand_block_markbad_lowlevel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nand_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	int ret;

	ret = nand_block_isbad(mtd, ofs);
	if (ret) {
		/* If it was bad already, return success and do nothing */
		if (ret > 0)
			return 0;
		return ret;
	}

	return nand_block_markbad_lowlevel(mtd_to_nand(mtd), ofs);
}