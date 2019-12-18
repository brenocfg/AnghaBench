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
struct ntc_data {int n_comp; TYPE_1__* comp; } ;
struct TYPE_2__ {unsigned int ohm; } ;

/* Variables and functions */

__attribute__((used)) static void lookup_comp(struct ntc_data *data, unsigned int ohm,
			int *i_low, int *i_high)
{
	int start, end, mid;

	/*
	 * Handle special cases: Resistance is higher than or equal to
	 * resistance in first table entry, or resistance is lower or equal
	 * to resistance in last table entry.
	 * In these cases, return i_low == i_high, either pointing to the
	 * beginning or to the end of the table depending on the condition.
	 */
	if (ohm >= data->comp[0].ohm) {
		*i_low = 0;
		*i_high = 0;
		return;
	}
	if (ohm <= data->comp[data->n_comp - 1].ohm) {
		*i_low = data->n_comp - 1;
		*i_high = data->n_comp - 1;
		return;
	}

	/* Do a binary search on compensation table */
	start = 0;
	end = data->n_comp;
	while (start < end) {
		mid = start + (end - start) / 2;
		/*
		 * start <= mid < end
		 * data->comp[start].ohm > ohm >= data->comp[end].ohm
		 *
		 * We could check for "ohm == data->comp[mid].ohm" here, but
		 * that is a quite unlikely condition, and we would have to
		 * check again after updating start. Check it at the end instead
		 * for simplicity.
		 */
		if (ohm >= data->comp[mid].ohm) {
			end = mid;
		} else {
			start = mid + 1;
			/*
			 * ohm >= data->comp[start].ohm might be true here,
			 * since we set start to mid + 1. In that case, we are
			 * done. We could keep going, but the condition is quite
			 * likely to occur, so it is worth checking for it.
			 */
			if (ohm >= data->comp[start].ohm)
				end = start;
		}
		/*
		 * start <= end
		 * data->comp[start].ohm >= ohm >= data->comp[end].ohm
		 */
	}
	/*
	 * start == end
	 * ohm >= data->comp[end].ohm
	 */
	*i_low = end;
	if (ohm == data->comp[end].ohm)
		*i_high = end;
	else
		*i_high = end - 1;
}