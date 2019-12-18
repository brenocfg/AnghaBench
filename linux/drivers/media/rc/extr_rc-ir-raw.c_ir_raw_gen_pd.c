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
struct ir_raw_timings_pd {unsigned int header_space; unsigned int* bit_space; unsigned int trailer_space; scalar_t__ trailer_pulse; scalar_t__ bit_pulse; scalar_t__ msb_first; scalar_t__ header_pulse; } ;
struct ir_raw_event {int dummy; } ;

/* Variables and functions */
 int ir_raw_gen_pulse_space (struct ir_raw_event**,unsigned int*,scalar_t__,unsigned int) ; 

int ir_raw_gen_pd(struct ir_raw_event **ev, unsigned int max,
		  const struct ir_raw_timings_pd *timings,
		  unsigned int n, u64 data)
{
	int i;
	int ret;
	unsigned int space;

	if (timings->header_pulse) {
		ret = ir_raw_gen_pulse_space(ev, &max, timings->header_pulse,
					     timings->header_space);
		if (ret)
			return ret;
	}

	if (timings->msb_first) {
		for (i = n - 1; i >= 0; --i) {
			space = timings->bit_space[(data >> i) & 1];
			ret = ir_raw_gen_pulse_space(ev, &max,
						     timings->bit_pulse,
						     space);
			if (ret)
				return ret;
		}
	} else {
		for (i = 0; i < n; ++i, data >>= 1) {
			space = timings->bit_space[data & 1];
			ret = ir_raw_gen_pulse_space(ev, &max,
						     timings->bit_pulse,
						     space);
			if (ret)
				return ret;
		}
	}

	ret = ir_raw_gen_pulse_space(ev, &max, timings->trailer_pulse,
				     timings->trailer_space);
	return ret;
}