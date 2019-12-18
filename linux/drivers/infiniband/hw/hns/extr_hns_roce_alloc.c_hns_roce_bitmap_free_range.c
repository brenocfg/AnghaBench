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
struct hns_roce_bitmap {int max; int reserved_top; int top; int mask; int /*<<< orphan*/  lock; int /*<<< orphan*/  last; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void hns_roce_bitmap_free_range(struct hns_roce_bitmap *bitmap,
				unsigned long obj, int cnt,
				int rr)
{
	int i;

	obj &= bitmap->max + bitmap->reserved_top - 1;

	spin_lock(&bitmap->lock);
	for (i = 0; i < cnt; i++)
		clear_bit(obj + i, bitmap->table);

	if (!rr)
		bitmap->last = min(bitmap->last, obj);
	bitmap->top = (bitmap->top + bitmap->max + bitmap->reserved_top)
		       & bitmap->mask;
	spin_unlock(&bitmap->lock);
}