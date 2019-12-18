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
struct mmc_test_card {struct mmc_test_area area; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 int mmc_test_area_erase (struct mmc_test_card*) ; 
 int mmc_test_area_io (struct mmc_test_card*,unsigned long,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_test_print_avg_rate (struct mmc_test_card*,unsigned long,unsigned int,struct timespec64*,struct timespec64*) ; 

__attribute__((used)) static int mmc_test_seq_write_perf(struct mmc_test_card *test, unsigned long sz)
{
	struct mmc_test_area *t = &test->area;
	unsigned int dev_addr, i, cnt;
	struct timespec64 ts1, ts2;
	int ret;

	ret = mmc_test_area_erase(test);
	if (ret)
		return ret;
	cnt = t->max_sz / sz;
	dev_addr = t->dev_addr;
	ktime_get_ts64(&ts1);
	for (i = 0; i < cnt; i++) {
		ret = mmc_test_area_io(test, sz, dev_addr, 1, 0, 0);
		if (ret)
			return ret;
		dev_addr += (sz >> 9);
	}
	ktime_get_ts64(&ts2);
	mmc_test_print_avg_rate(test, sz, cnt, &ts1, &ts2);
	return 0;
}