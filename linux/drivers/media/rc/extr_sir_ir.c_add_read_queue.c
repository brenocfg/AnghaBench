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
struct ir_raw_event {int pulse; int /*<<< orphan*/  duration; } ;

/* Variables and functions */
 int TIME_CONST ; 
 int /*<<< orphan*/  US_TO_NS (unsigned long) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned long) ; 
 int /*<<< orphan*/  rcdev ; 

__attribute__((used)) static void add_read_queue(int flag, unsigned long val)
{
	struct ir_raw_event ev = {};

	pr_debug("add flag %d with val %lu\n", flag, val);

	/*
	 * statistically, pulses are ~TIME_CONST/2 too long. we could
	 * maybe make this more exact, but this is good enough
	 */
	if (flag) {
		/* pulse */
		if (val > TIME_CONST / 2)
			val -= TIME_CONST / 2;
		else /* should not ever happen */
			val = 1;
		ev.pulse = true;
	} else {
		val += TIME_CONST / 2;
	}
	ev.duration = US_TO_NS(val);

	ir_raw_event_store_with_filter(rcdev, &ev);
}