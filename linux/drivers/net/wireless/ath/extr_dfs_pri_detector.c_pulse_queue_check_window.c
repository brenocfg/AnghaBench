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
struct pulse_elem {scalar_t__ ts; } ;
struct pri_detector {int count; scalar_t__ last_ts; scalar_t__ window_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  pulse_queue_dequeue (struct pri_detector*) ; 
 struct pulse_elem* pulse_queue_get_tail (struct pri_detector*) ; 

__attribute__((used)) static void pulse_queue_check_window(struct pri_detector *pde)
{
	u64 min_valid_ts;
	struct pulse_elem *p;

	/* there is no delta time with less than 2 pulses */
	if (pde->count < 2)
		return;

	if (pde->last_ts <= pde->window_size)
		return;

	min_valid_ts = pde->last_ts - pde->window_size;
	while ((p = pulse_queue_get_tail(pde)) != NULL) {
		if (p->ts >= min_valid_ts)
			return;
		pulse_queue_dequeue(pde);
	}
}