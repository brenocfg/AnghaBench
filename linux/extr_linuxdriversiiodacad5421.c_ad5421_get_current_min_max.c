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
struct ad5421_state {int current_range; } ;

/* Variables and functions */
#define  AD5421_CURRENT_RANGE_3mA2_24mA 130 
#define  AD5421_CURRENT_RANGE_3mA8_21mA 129 
#define  AD5421_CURRENT_RANGE_4mA_20mA 128 

__attribute__((used)) static void ad5421_get_current_min_max(struct ad5421_state *st,
	unsigned int *min, unsigned int *max)
{
	/* The current range is configured using external pins, which are
	 * usually hard-wired and not run-time switchable. */
	switch (st->current_range) {
	case AD5421_CURRENT_RANGE_4mA_20mA:
		*min = 4000;
		*max = 20000;
		break;
	case AD5421_CURRENT_RANGE_3mA8_21mA:
		*min = 3800;
		*max = 21000;
		break;
	case AD5421_CURRENT_RANGE_3mA2_24mA:
		*min = 3200;
		*max = 24000;
		break;
	default:
		*min = 0;
		*max = 1;
		break;
	}
}