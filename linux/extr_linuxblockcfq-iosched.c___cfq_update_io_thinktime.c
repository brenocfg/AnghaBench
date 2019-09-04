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
typedef  unsigned long u64 ;
struct cfq_ttime {unsigned long last_end_request; int ttime_samples; int ttime_total; int /*<<< orphan*/  ttime_mean; } ;

/* Variables and functions */
 int /*<<< orphan*/  div64_ul (int /*<<< orphan*/ ,int) ; 
 int div_u64 (int,int) ; 
 unsigned long ktime_get_ns () ; 
 unsigned long min (unsigned long,unsigned long) ; 

__attribute__((used)) static void
__cfq_update_io_thinktime(struct cfq_ttime *ttime, u64 slice_idle)
{
	u64 elapsed = ktime_get_ns() - ttime->last_end_request;
	elapsed = min(elapsed, 2UL * slice_idle);

	ttime->ttime_samples = (7*ttime->ttime_samples + 256) / 8;
	ttime->ttime_total = div_u64(7*ttime->ttime_total + 256*elapsed,  8);
	ttime->ttime_mean = div64_ul(ttime->ttime_total + 128,
				     ttime->ttime_samples);
}