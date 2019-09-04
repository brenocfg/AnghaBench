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
struct mmc_test_area {unsigned long max_tfr; } ;
struct mmc_test_card {struct mmc_test_area area; } ;

/* Variables and functions */
 int __mmc_test_cmds_during_tfr (struct mmc_test_card*,unsigned long,int,int,int) ; 

__attribute__((used)) static int mmc_test_cmds_during_tfr(struct mmc_test_card *test, int use_sbc,
				    int write, int use_areq)
{
	struct mmc_test_area *t = &test->area;
	unsigned long sz;
	int ret;

	for (sz = 512; sz <= t->max_tfr; sz += 512) {
		ret = __mmc_test_cmds_during_tfr(test, sz, use_sbc, write,
						 use_areq);
		if (ret)
			return ret;
	}
	return 0;
}