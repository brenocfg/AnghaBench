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
 int mtdtest_erase_eraseblock (struct mtd_info*,unsigned int) ; 

int mtdtest_erase_good_eraseblocks(struct mtd_info *mtd, unsigned char *bbt,
				unsigned int eb, int ebcnt)
{
	int err;
	unsigned int i;

	for (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		err = mtdtest_erase_eraseblock(mtd, eb + i);
		if (err)
			return err;
		cond_resched();
	}

	return 0;
}