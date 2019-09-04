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
typedef  scalar_t__ u64 ;
struct cfq_queue {int dispatched; scalar_t__ slice_end; } ;
struct cfq_data {int cfq_slice_idle; } ;

/* Variables and functions */
 scalar_t__ cfq_cfqq_slice_new (struct cfq_queue*) ; 
 scalar_t__ ktime_get_ns () ; 

__attribute__((used)) static inline bool cfq_slice_used_soon(struct cfq_data *cfqd,
	struct cfq_queue *cfqq)
{
	u64 now = ktime_get_ns();

	/* the queue hasn't finished any request, can't estimate */
	if (cfq_cfqq_slice_new(cfqq))
		return true;
	if (now + cfqd->cfq_slice_idle * cfqq->dispatched > cfqq->slice_end)
		return true;

	return false;
}