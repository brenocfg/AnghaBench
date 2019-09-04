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
typedef  int u64 ;
struct hw_perf_event {int /*<<< orphan*/  config; int /*<<< orphan*/  prev_count; int /*<<< orphan*/  event_base; } ;
struct perf_event {int /*<<< orphan*/  count; struct hw_perf_event hw; } ;
typedef  int s64 ;

/* Variables and functions */
 int RAPL_CNTR_WIDTH ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  local64_add (int,int /*<<< orphan*/ *) ; 
 int local64_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int local64_read (int /*<<< orphan*/ *) ; 
 int rapl_scale (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 rapl_event_update(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	u64 prev_raw_count, new_raw_count;
	s64 delta, sdelta;
	int shift = RAPL_CNTR_WIDTH;

again:
	prev_raw_count = local64_read(&hwc->prev_count);
	rdmsrl(event->hw.event_base, new_raw_count);

	if (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			    new_raw_count) != prev_raw_count) {
		cpu_relax();
		goto again;
	}

	/*
	 * Now we have the new raw value and have updated the prev
	 * timestamp already. We can now calculate the elapsed delta
	 * (event-)time and add that to the generic event.
	 *
	 * Careful, not all hw sign-extends above the physical width
	 * of the count.
	 */
	delta = (new_raw_count << shift) - (prev_raw_count << shift);
	delta >>= shift;

	sdelta = rapl_scale(delta, event->hw.config);

	local64_add(sdelta, &event->count);

	return new_raw_count;
}