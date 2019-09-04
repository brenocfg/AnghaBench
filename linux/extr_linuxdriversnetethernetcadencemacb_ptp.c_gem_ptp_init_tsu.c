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
struct macb {int /*<<< orphan*/  tsu_incr; int /*<<< orphan*/  ptp_clock_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA ; 
 int /*<<< orphan*/  gem_tsu_incr_set (struct macb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gem_tsu_set_time (int /*<<< orphan*/ *,struct timespec64*) ; 
 int /*<<< orphan*/  gem_writel (struct macb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 struct timespec64 ns_to_timespec64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gem_ptp_init_tsu(struct macb *bp)
{
	struct timespec64 ts;

	/* 1. get current system time */
	ts = ns_to_timespec64(ktime_to_ns(ktime_get_real()));

	/* 2. set ptp timer */
	gem_tsu_set_time(&bp->ptp_clock_info, &ts);

	/* 3. set PTP timer increment value to BASE_INCREMENT */
	gem_tsu_incr_set(bp, &bp->tsu_incr);

	gem_writel(bp, TA, 0);
}