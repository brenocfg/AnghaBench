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
struct timespec64 {int dummy; } ;
struct mmc_test_area {unsigned long max_sz; unsigned int dev_addr; } ;
struct mmc_test_card {int /*<<< orphan*/  card; struct mmc_test_area area; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_TRIM_ARG ; 
 int RESULT_UNSUP_CARD ; 
 int RESULT_UNSUP_HOST ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  mmc_can_erase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_can_trim (int /*<<< orphan*/ ) ; 
 int mmc_erase (int /*<<< orphan*/ ,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 
 int mmc_test_area_erase (struct mmc_test_card*) ; 
 int mmc_test_area_fill (struct mmc_test_card*) ; 
 int /*<<< orphan*/  mmc_test_print_avg_rate (struct mmc_test_card*,unsigned long,unsigned int,struct timespec64*,struct timespec64*) ; 

__attribute__((used)) static int mmc_test_profile_seq_trim_perf(struct mmc_test_card *test)
{
	struct mmc_test_area *t = &test->area;
	unsigned long sz;
	unsigned int dev_addr, i, cnt;
	struct timespec64 ts1, ts2;
	int ret;

	if (!mmc_can_trim(test->card))
		return RESULT_UNSUP_CARD;

	if (!mmc_can_erase(test->card))
		return RESULT_UNSUP_HOST;

	for (sz = 512; sz <= t->max_sz; sz <<= 1) {
		ret = mmc_test_area_erase(test);
		if (ret)
			return ret;
		ret = mmc_test_area_fill(test);
		if (ret)
			return ret;
		cnt = t->max_sz / sz;
		dev_addr = t->dev_addr;
		ktime_get_ts64(&ts1);
		for (i = 0; i < cnt; i++) {
			ret = mmc_erase(test->card, dev_addr, sz >> 9,
					MMC_TRIM_ARG);
			if (ret)
				return ret;
			dev_addr += (sz >> 9);
		}
		ktime_get_ts64(&ts2);
		mmc_test_print_avg_rate(test, sz, cnt, &ts1, &ts2);
	}
	return 0;
}