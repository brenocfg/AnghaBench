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
typedef  unsigned long long u64 ;
struct TYPE_2__ {int /*<<< orphan*/  config; int /*<<< orphan*/  prev_count; } ;
struct perf_event {int /*<<< orphan*/  count; TYPE_1__ hw; } ;

/* Variables and functions */
 int ecctr (int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  local64_add (unsigned long long,int /*<<< orphan*/ *) ; 
 unsigned long long local64_cmpxchg (int /*<<< orphan*/ *,unsigned long long,unsigned long long) ; 
 unsigned long long local64_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hw_perf_event_update(struct perf_event *event)
{
	u64 prev, new, delta;
	int err;

	do {
		prev = local64_read(&event->hw.prev_count);
		err = ecctr(event->hw.config, &new);
		if (err)
			return;
	} while (local64_cmpxchg(&event->hw.prev_count, prev, new) != prev);

	delta = (prev <= new) ? new - prev
			      : (-1ULL - prev) + new + 1;	 /* overflow */
	local64_add(delta, &event->count);
}