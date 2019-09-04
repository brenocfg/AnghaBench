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
typedef  int /*<<< orphan*/  u64 ;
struct bfq_data {scalar_t__ bfq_wr_max_time; int /*<<< orphan*/  peak_rate; int /*<<< orphan*/  rate_dur_prod; } ;

/* Variables and functions */
 unsigned int clamp_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

__attribute__((used)) static unsigned int bfq_wr_duration(struct bfq_data *bfqd)
{
	u64 dur;

	if (bfqd->bfq_wr_max_time > 0)
		return bfqd->bfq_wr_max_time;

	dur = bfqd->rate_dur_prod;
	do_div(dur, bfqd->peak_rate);

	/*
	 * Limit duration between 3 and 25 seconds. The upper limit
	 * has been conservatively set after the following worst case:
	 * on a QEMU/KVM virtual machine
	 * - running in a slow PC
	 * - with a virtual disk stacked on a slow low-end 5400rpm HDD
	 * - serving a heavy I/O workload, such as the sequential reading
	 *   of several files
	 * mplayer took 23 seconds to start, if constantly weight-raised.
	 *
	 * As for higher values than that accomodating the above bad
	 * scenario, tests show that higher values would often yield
	 * the opposite of the desired result, i.e., would worsen
	 * responsiveness by allowing non-interactive applications to
	 * preserve weight raising for too long.
	 *
	 * On the other end, lower values than 3 seconds make it
	 * difficult for most interactive tasks to complete their jobs
	 * before weight-raising finishes.
	 */
	return clamp_val(dur, msecs_to_jiffies(3000), msecs_to_jiffies(25000));
}