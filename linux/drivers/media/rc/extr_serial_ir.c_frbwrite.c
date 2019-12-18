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
struct ir_raw_event {unsigned int duration; int pulse; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcdev; } ;

/* Variables and functions */
 unsigned int IR_MAX_DURATION ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 TYPE_1__ serial_ir ; 

__attribute__((used)) static void frbwrite(unsigned int l, bool is_pulse)
{
	/* simple noise filter */
	static unsigned int ptr, pulse, space;
	struct ir_raw_event ev = {};

	if (ptr > 0 && is_pulse) {
		pulse += l;
		if (pulse > 250000) {
			ev.duration = space;
			ev.pulse = false;
			ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
			ev.duration = pulse;
			ev.pulse = true;
			ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
			ptr = 0;
			pulse = 0;
		}
		return;
	}
	if (!is_pulse) {
		if (ptr == 0) {
			if (l > 20000000) {
				space = l;
				ptr++;
				return;
			}
		} else {
			if (l > 20000000) {
				space += pulse;
				if (space > IR_MAX_DURATION)
					space = IR_MAX_DURATION;
				space += l;
				if (space > IR_MAX_DURATION)
					space = IR_MAX_DURATION;
				pulse = 0;
				return;
			}

			ev.duration = space;
			ev.pulse = false;
			ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
			ev.duration = pulse;
			ev.pulse = true;
			ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
			ptr = 0;
			pulse = 0;
		}
	}

	ev.duration = l;
	ev.pulse = is_pulse;
	ir_raw_event_store_with_filter(serial_ir.rcdev, &ev);
}