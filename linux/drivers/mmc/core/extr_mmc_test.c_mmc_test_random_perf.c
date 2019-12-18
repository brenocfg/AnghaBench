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
 int mmc_test_rnd_perf (struct mmc_test_card*,int,int,unsigned long) ; 
 unsigned int rnd_next ; 

__attribute__((used)) static int mmc_test_random_perf(struct mmc_test_card *test, int write)
{
	struct mmc_test_area *t = &test->area;
	unsigned int next;
	unsigned long sz;
	int ret;

	for (sz = 512; sz < t->max_tfr; sz <<= 1) {
		/*
		 * When writing, try to get more consistent results by running
		 * the test twice with exactly the same I/O but outputting the
		 * results only for the 2nd run.
		 */
		if (write) {
			next = rnd_next;
			ret = mmc_test_rnd_perf(test, write, 0, sz);
			if (ret)
				return ret;
			rnd_next = next;
		}
		ret = mmc_test_rnd_perf(test, write, 1, sz);
		if (ret)
			return ret;
	}
	sz = t->max_tfr;
	if (write) {
		next = rnd_next;
		ret = mmc_test_rnd_perf(test, write, 0, sz);
		if (ret)
			return ret;
		rnd_next = next;
	}
	return mmc_test_rnd_perf(test, write, 1, sz);
}