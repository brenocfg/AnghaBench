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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct timespec64 {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct mmc_test_card {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 unsigned int mmc_test_rate (int,struct timespec64*) ; 
 int /*<<< orphan*/  mmc_test_save_transfer_result (struct mmc_test_card*,int,unsigned int,struct timespec64,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned int,unsigned int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 struct timespec64 timespec64_sub (struct timespec64,struct timespec64) ; 

__attribute__((used)) static void mmc_test_print_rate(struct mmc_test_card *test, uint64_t bytes,
				struct timespec64 *ts1, struct timespec64 *ts2)
{
	unsigned int rate, iops, sectors = bytes >> 9;
	struct timespec64 ts;

	ts = timespec64_sub(*ts2, *ts1);

	rate = mmc_test_rate(bytes, &ts);
	iops = mmc_test_rate(100, &ts); /* I/O ops per sec x 100 */

	pr_info("%s: Transfer of %u sectors (%u%s KiB) took %llu.%09u "
			 "seconds (%u kB/s, %u KiB/s, %u.%02u IOPS)\n",
			 mmc_hostname(test->card->host), sectors, sectors >> 1,
			 (sectors & 1 ? ".5" : ""), (u64)ts.tv_sec,
			 (u32)ts.tv_nsec, rate / 1000, rate / 1024,
			 iops / 100, iops % 100);

	mmc_test_save_transfer_result(test, 1, sectors, ts, rate, iops);
}