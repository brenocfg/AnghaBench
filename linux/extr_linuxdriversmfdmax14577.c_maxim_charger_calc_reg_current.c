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
typedef  unsigned int u8 ;
struct maxim_charger_current {unsigned int max; unsigned int min; unsigned int high_start; unsigned int high_step; } ;

/* Variables and functions */
 unsigned int CHGCTRL4_MBCICHWRCH_SHIFT ; 
 int CHGCTRL4_MBCICHWRCL_SHIFT ; 
 int EINVAL ; 
 unsigned int min (unsigned int,unsigned int) ; 

int maxim_charger_calc_reg_current(const struct maxim_charger_current *limits,
		unsigned int min_ua, unsigned int max_ua, u8 *dst)
{
	unsigned int current_bits = 0xf;

	if (min_ua > max_ua)
		return -EINVAL;

	if (min_ua > limits->max || max_ua < limits->min)
		return -EINVAL;

	if (max_ua < limits->high_start) {
		/*
		 * Less than high_start, so set the minimal current
		 * (turn Low Bit off, 0 as high bits).
		 */
		*dst = 0x0;
		return 0;
	}

	/* max_ua is in range: <high_start, infinite>, cut it to limits.max */
	max_ua = min(limits->max, max_ua);
	max_ua -= limits->high_start;
	/*
	 * There is no risk of overflow 'max_ua' here because:
	 *  - max_ua >= limits.high_start
	 *  - BUILD_BUG checks that 'limits' are: max >= high_start + high_step
	 */
	current_bits = max_ua / limits->high_step;

	/* Turn Low Bit on (use range <limits.high_start, limits.max>) ... */
	*dst = 0x1 << CHGCTRL4_MBCICHWRCL_SHIFT;
	/* and set proper High Bits */
	*dst |= current_bits << CHGCTRL4_MBCICHWRCH_SHIFT;

	return 0;
}