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
struct linear_range {unsigned int min; unsigned int step; unsigned int vals; unsigned int low_sel; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int find_selector_for_value_low(const struct linear_range *r,
				       int selectors, unsigned int val,
				       unsigned int *sel, bool *found)
{
	int i;
	int ret = -EINVAL;

	*found = false;
	for (i = 0; i < selectors; i++) {
		if (r[i].min <= val) {
			if (r[i].min + r[i].step * r[i].vals >= val) {
				*found = true;
				*sel = r[i].low_sel + (val - r[i].min) /
				       r[i].step;
				ret = 0;
				break;
			}
			/*
			 * If the range max is smaller than requested
			 * we can set the max supported value from range
			 */
			*sel = r[i].low_sel + r[i].vals;
			ret = 0;
		}
	}
	return ret;
}