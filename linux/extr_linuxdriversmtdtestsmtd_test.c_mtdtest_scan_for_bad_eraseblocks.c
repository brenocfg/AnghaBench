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

/* Variables and functions */
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ is_block_bad (struct mtd_info*,unsigned int) ; 
 int /*<<< orphan*/  mtd_can_have_bb (struct mtd_info*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

int mtdtest_scan_for_bad_eraseblocks(struct mtd_info *mtd, unsigned char *bbt,
					unsigned int eb, int ebcnt)
{
	int i, bad = 0;

	if (!mtd_can_have_bb(mtd))
		return 0;

	pr_info("scanning for bad eraseblocks\n");
	for (i = 0; i < ebcnt; ++i) {
		bbt[i] = is_block_bad(mtd, eb + i) ? 1 : 0;
		if (bbt[i])
			bad += 1;
		cond_resched();
	}
	pr_info("scanned %d eraseblocks, %d are bad\n", i, bad);

	return 0;
}