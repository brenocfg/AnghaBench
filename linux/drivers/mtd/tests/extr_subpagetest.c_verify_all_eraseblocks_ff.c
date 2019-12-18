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
 int verify_eraseblock_ff (unsigned int) ; 

__attribute__((used)) static int verify_all_eraseblocks_ff(void)
{
	int err;
	unsigned int i;

	pr_info("verifying all eraseblocks for 0xff\n");
	for (i = 0; i < ebcnt; ++i) {
		if (bbt[i])
			continue;
		err = verify_eraseblock_ff(i);
		if (err)
			return err;
		if (i % 256 == 0)
			pr_info("verified up to eraseblock %u\n", i);

		err = mtdtest_relax();
		if (err)
			return err;
	}
	pr_info("verified %u eraseblocks\n", i);
	return 0;
}