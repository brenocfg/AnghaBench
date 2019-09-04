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
struct ir_raw_timings_manchester {scalar_t__ trailer_space; scalar_t__ clock; scalar_t__ invert; scalar_t__ leader_space; scalar_t__ leader_pulse; } ;
struct ir_raw_event {int /*<<< orphan*/  duration; int /*<<< orphan*/  pulse; } ;

/* Variables and functions */
 int BIT_ULL (unsigned int) ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  init_ir_raw_event_duration (struct ir_raw_event*,int,scalar_t__) ; 

int ir_raw_gen_manchester(struct ir_raw_event **ev, unsigned int max,
			  const struct ir_raw_timings_manchester *timings,
			  unsigned int n, u64 data)
{
	bool need_pulse;
	u64 i;
	int ret = -ENOBUFS;

	i = BIT_ULL(n - 1);

	if (timings->leader_pulse) {
		if (!max--)
			return ret;
		init_ir_raw_event_duration((*ev), 1, timings->leader_pulse);
		if (timings->leader_space) {
			if (!max--)
				return ret;
			init_ir_raw_event_duration(++(*ev), 0,
						   timings->leader_space);
		}
	} else {
		/* continue existing signal */
		--(*ev);
	}
	/* from here on *ev will point to the last event rather than the next */

	while (n && i > 0) {
		need_pulse = !(data & i);
		if (timings->invert)
			need_pulse = !need_pulse;
		if (need_pulse == !!(*ev)->pulse) {
			(*ev)->duration += timings->clock;
		} else {
			if (!max--)
				goto nobufs;
			init_ir_raw_event_duration(++(*ev), need_pulse,
						   timings->clock);
		}

		if (!max--)
			goto nobufs;
		init_ir_raw_event_duration(++(*ev), !need_pulse,
					   timings->clock);
		i >>= 1;
	}

	if (timings->trailer_space) {
		if (!(*ev)->pulse)
			(*ev)->duration += timings->trailer_space;
		else if (!max--)
			goto nobufs;
		else
			init_ir_raw_event_duration(++(*ev), 0,
						   timings->trailer_space);
	}

	ret = 0;
nobufs:
	/* point to the next event rather than last event before returning */
	++(*ev);
	return ret;
}