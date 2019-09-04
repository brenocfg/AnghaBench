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
struct hns_roce_bitmap {unsigned long max; unsigned long last; int top; int reserved_top; int mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 unsigned long bitmap_find_next_zero_area (int /*<<< orphan*/ ,unsigned long,unsigned long,int,int) ; 
 int hns_roce_bitmap_alloc (struct hns_roce_bitmap*,unsigned long*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int hns_roce_bitmap_alloc_range(struct hns_roce_bitmap *bitmap, int cnt,
				int align, unsigned long *obj)
{
	int ret = 0;
	int i;

	if (likely(cnt == 1 && align == 1))
		return hns_roce_bitmap_alloc(bitmap, obj);

	spin_lock(&bitmap->lock);

	*obj = bitmap_find_next_zero_area(bitmap->table, bitmap->max,
					  bitmap->last, cnt, align - 1);
	if (*obj >= bitmap->max) {
		bitmap->top = (bitmap->top + bitmap->max + bitmap->reserved_top)
			       & bitmap->mask;
		*obj = bitmap_find_next_zero_area(bitmap->table, bitmap->max, 0,
						  cnt, align - 1);
	}

	if (*obj < bitmap->max) {
		for (i = 0; i < cnt; i++)
			set_bit(*obj + i, bitmap->table);

		if (*obj == bitmap->last) {
			bitmap->last = (*obj + cnt);
			if (bitmap->last >= bitmap->max)
				bitmap->last = 0;
		}
		*obj |= bitmap->top;
	} else {
		ret = -1;
	}

	spin_unlock(&bitmap->lock);

	return ret;
}