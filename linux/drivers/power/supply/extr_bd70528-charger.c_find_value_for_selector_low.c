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
struct linear_range {unsigned int low_sel; unsigned int vals; unsigned int min; unsigned int step; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int find_value_for_selector_low(const struct linear_range *r,
				       int selectors, unsigned int sel,
				       unsigned int *val)
{
	int i;

	for (i = 0; i < selectors; i++) {
		if (r[i].low_sel <= sel && r[i].low_sel + r[i].vals >= sel) {
			*val = r[i].min + (sel - r[i].low_sel) * r[i].step;
			return 0;
		}
	}
	return -EINVAL;
}