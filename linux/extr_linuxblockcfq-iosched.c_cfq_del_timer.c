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
struct cfq_queue {int /*<<< orphan*/  cfqg; } ;
struct cfq_data {int /*<<< orphan*/  idle_slice_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfqg_stats_update_idle_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cfq_del_timer(struct cfq_data *cfqd, struct cfq_queue *cfqq)
{
	hrtimer_try_to_cancel(&cfqd->idle_slice_timer);
	cfqg_stats_update_idle_time(cfqq->cfqg);
}