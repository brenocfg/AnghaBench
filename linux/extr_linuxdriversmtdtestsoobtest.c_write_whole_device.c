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

/* Variables and functions */
 scalar_t__* bbt ; 
 unsigned int ebcnt ; 
 int mtdtest_relax () ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int write_eraseblock (unsigned int) ; 

__attribute__((used)) static int write_whole_device(void)
{
	int err;
	unsigned int i;

	pr_info("writing OOBs of whole device\n");
	for (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		err = write_eraseblock(i);
		if (err)
			return err;
		if (i % 256 == 0)
			pr_info("written up to eraseblock %u\n", i);

		err = mtdtest_relax();
		if (err)
			return err;
	}
	pr_info("written %u eraseblocks\n", i);
	return 0;
}