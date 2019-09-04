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
struct ir_raw_timings_pl {unsigned int header_pulse; unsigned int bit_space; unsigned int* bit_pulse; unsigned int trailer_space; scalar_t__ msb_first; } ;
struct ir_raw_event {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  init_ir_raw_event_duration (int /*<<< orphan*/ ,int,unsigned int) ; 

int ir_raw_gen_pl(struct ir_raw_event **ev, unsigned int max,
		  const struct ir_raw_timings_pl *timings,
		  unsigned int n, u64 data)
{
	int i;
	int ret = -ENOBUFS;
	unsigned int pulse;

	if (!max--)
		return ret;

	init_ir_raw_event_duration((*ev)++, 1, timings->header_pulse);

	if (timings->msb_first) {
		for (i = n - 1; i >= 0; --i) {
			if (!max--)
				return ret;
			init_ir_raw_event_duration((*ev)++, 0,
						   timings->bit_space);
			if (!max--)
				return ret;
			pulse = timings->bit_pulse[(data >> i) & 1];
			init_ir_raw_event_duration((*ev)++, 1, pulse);
		}
	} else {
		for (i = 0; i < n; ++i, data >>= 1) {
			if (!max--)
				return ret;
			init_ir_raw_event_duration((*ev)++, 0,
						   timings->bit_space);
			if (!max--)
				return ret;
			pulse = timings->bit_pulse[data & 1];
			init_ir_raw_event_duration((*ev)++, 1, pulse);
		}
	}

	if (!max--)
		return ret;

	init_ir_raw_event_duration((*ev)++, 0, timings->trailer_space);

	return 0;
}