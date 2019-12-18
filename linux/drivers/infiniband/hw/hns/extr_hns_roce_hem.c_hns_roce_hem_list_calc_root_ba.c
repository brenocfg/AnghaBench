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
struct hns_roce_buf_region {int hopnum; int count; } ;

/* Variables and functions */
 int hem_list_calc_ba_range (int,int,int) ; 

int hns_roce_hem_list_calc_root_ba(const struct hns_roce_buf_region *regions,
				   int region_cnt, int unit)
{
	struct hns_roce_buf_region *r;
	int total = 0;
	int step;
	int i;

	for (i = 0; i < region_cnt; i++) {
		r = (struct hns_roce_buf_region *)&regions[i];
		if (r->hopnum > 1) {
			step = hem_list_calc_ba_range(r->hopnum, 1, unit);
			if (step > 0)
				total += (r->count + step - 1) / step;
		} else {
			total += r->count;
		}
	}

	return total;
}