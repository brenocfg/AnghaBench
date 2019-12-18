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
struct streamzap_ir {int idle; scalar_t__ sum; int /*<<< orphan*/  signal_last; int /*<<< orphan*/  signal_start; } ;
struct ir_raw_event {int pulse; int duration; } ;

/* Variables and functions */
 void* IR_MAX_DURATION ; 
 int SZ_RESOLUTION ; 
 int USEC_PER_SEC ; 
 void* US_TO_NS (int) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sz_push (struct streamzap_ir*,struct ir_raw_event) ; 

__attribute__((used)) static void sz_push_full_pulse(struct streamzap_ir *sz,
			       unsigned char value)
{
	struct ir_raw_event rawir = {};

	if (sz->idle) {
		int delta;

		sz->signal_last = sz->signal_start;
		sz->signal_start = ktime_get_real();

		delta = ktime_us_delta(sz->signal_start, sz->signal_last);
		rawir.pulse = false;
		if (delta > (15 * USEC_PER_SEC)) {
			/* really long time */
			rawir.duration = IR_MAX_DURATION;
		} else {
			rawir.duration = delta;
			rawir.duration -= sz->sum;
			rawir.duration = US_TO_NS(rawir.duration);
			rawir.duration = (rawir.duration > IR_MAX_DURATION) ?
					 IR_MAX_DURATION : rawir.duration;
		}
		sz_push(sz, rawir);

		sz->idle = false;
		sz->sum = 0;
	}

	rawir.pulse = true;
	rawir.duration = ((int) value) * SZ_RESOLUTION;
	rawir.duration += SZ_RESOLUTION / 2;
	sz->sum += rawir.duration;
	rawir.duration = US_TO_NS(rawir.duration);
	rawir.duration = (rawir.duration > IR_MAX_DURATION) ?
			 IR_MAX_DURATION : rawir.duration;
	sz_push(sz, rawir);
}