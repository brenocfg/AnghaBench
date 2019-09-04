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
struct max9485_rate {unsigned long out; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct max9485_rate* max9485_rates ; 

__attribute__((used)) static long max9485_clkout_round_rate(struct clk_hw *hw, unsigned long rate,
				      unsigned long *parent_rate)
{
	const struct max9485_rate *curr, *prev = NULL;

	for (curr = max9485_rates; curr->out != 0; curr++) {
		/* Exact matches */
		if (curr->out == rate)
			return rate;

		/*
		 * Find the first entry that has a frequency higher than the
		 * requested one.
		 */
		if (curr->out > rate) {
			unsigned int mid;

			/*
			 * If this is the first entry, clamp the value to the
			 * lowest possible frequency.
			 */
			if (!prev)
				return curr->out;

			/*
			 * Otherwise, determine whether the previous entry or
			 * current one is closer.
			 */
			mid = prev->out + ((curr->out - prev->out) / 2);

			return (mid > rate) ? prev->out : curr->out;
		}

		prev = curr;
	}

	/* If the last entry was still too high, clamp the value */
	return prev->out;
}