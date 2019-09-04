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
struct regmap_range_node {unsigned int range_min; unsigned int window_len; unsigned int range_max; unsigned int window_start; unsigned int selector_reg; unsigned int selector_shift; int /*<<< orphan*/  selector_mask; } ;
struct regmap {void* work_buf; void* selector_work_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int _regmap_update_bits (struct regmap*,unsigned int,int /*<<< orphan*/ ,unsigned int,int*,int) ; 

__attribute__((used)) static int _regmap_select_page(struct regmap *map, unsigned int *reg,
			       struct regmap_range_node *range,
			       unsigned int val_num)
{
	void *orig_work_buf;
	unsigned int win_offset;
	unsigned int win_page;
	bool page_chg;
	int ret;

	win_offset = (*reg - range->range_min) % range->window_len;
	win_page = (*reg - range->range_min) / range->window_len;

	if (val_num > 1) {
		/* Bulk write shouldn't cross range boundary */
		if (*reg + val_num - 1 > range->range_max)
			return -EINVAL;

		/* ... or single page boundary */
		if (val_num > range->window_len - win_offset)
			return -EINVAL;
	}

	/* It is possible to have selector register inside data window.
	   In that case, selector register is located on every page and
	   it needs no page switching, when accessed alone. */
	if (val_num > 1 ||
	    range->window_start + win_offset != range->selector_reg) {
		/* Use separate work_buf during page switching */
		orig_work_buf = map->work_buf;
		map->work_buf = map->selector_work_buf;

		ret = _regmap_update_bits(map, range->selector_reg,
					  range->selector_mask,
					  win_page << range->selector_shift,
					  &page_chg, false);

		map->work_buf = orig_work_buf;

		if (ret != 0)
			return ret;
	}

	*reg = range->window_start + win_offset;

	return 0;
}