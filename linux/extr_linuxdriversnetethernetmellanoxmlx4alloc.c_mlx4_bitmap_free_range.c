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
typedef  int u32 ;
struct mlx4_bitmap {int max; int reserved_top; int top; int mask; int avail; int /*<<< orphan*/  lock; int /*<<< orphan*/  table; int /*<<< orphan*/  last; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mlx4_bitmap_free_range(struct mlx4_bitmap *bitmap, u32 obj, int cnt,
			    int use_rr)
{
	obj &= bitmap->max + bitmap->reserved_top - 1;

	spin_lock(&bitmap->lock);
	if (!use_rr) {
		bitmap->last = min(bitmap->last, obj);
		bitmap->top = (bitmap->top + bitmap->max + bitmap->reserved_top)
				& bitmap->mask;
	}
	bitmap_clear(bitmap->table, obj, cnt);
	bitmap->avail += cnt;
	spin_unlock(&bitmap->lock);
}