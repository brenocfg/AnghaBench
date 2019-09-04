#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec64 {int tv_sec; } ;
struct mmc_test_card {TYPE_1__* card; } ;
struct TYPE_2__ {unsigned int pref_erase; } ;

/* Variables and functions */
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 int mmc_test_area_io (struct mmc_test_card*,unsigned long,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmc_test_capacity (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_test_print_avg_rate (struct mmc_test_card*,unsigned long,unsigned int,struct timespec64*,struct timespec64*) ; 
 unsigned int mmc_test_rnd_num (unsigned int) ; 
 struct timespec64 timespec64_sub (struct timespec64,struct timespec64) ; 

__attribute__((used)) static int mmc_test_rnd_perf(struct mmc_test_card *test, int write, int print,
			     unsigned long sz)
{
	unsigned int dev_addr, cnt, rnd_addr, range1, range2, last_ea = 0, ea;
	unsigned int ssz;
	struct timespec64 ts1, ts2, ts;
	int ret;

	ssz = sz >> 9;

	rnd_addr = mmc_test_capacity(test->card) / 4;
	range1 = rnd_addr / test->card->pref_erase;
	range2 = range1 / ssz;

	ktime_get_ts64(&ts1);
	for (cnt = 0; cnt < UINT_MAX; cnt++) {
		ktime_get_ts64(&ts2);
		ts = timespec64_sub(ts2, ts1);
		if (ts.tv_sec >= 10)
			break;
		ea = mmc_test_rnd_num(range1);
		if (ea == last_ea)
			ea -= 1;
		last_ea = ea;
		dev_addr = rnd_addr + test->card->pref_erase * ea +
			   ssz * mmc_test_rnd_num(range2);
		ret = mmc_test_area_io(test, sz, dev_addr, write, 0, 0);
		if (ret)
			return ret;
	}
	if (print)
		mmc_test_print_avg_rate(test, sz, cnt, &ts1, &ts2);
	return 0;
}