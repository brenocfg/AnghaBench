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
struct cfq_queue {scalar_t__ slice_end; } ;

/* Variables and functions */
 scalar_t__ cfq_cfqq_slice_new (struct cfq_queue*) ; 
 scalar_t__ ktime_get_ns () ; 

__attribute__((used)) static inline bool cfq_slice_used(struct cfq_queue *cfqq)
{
	if (cfq_cfqq_slice_new(cfqq))
		return false;
	if (ktime_get_ns() < cfqq->slice_end)
		return false;

	return true;
}