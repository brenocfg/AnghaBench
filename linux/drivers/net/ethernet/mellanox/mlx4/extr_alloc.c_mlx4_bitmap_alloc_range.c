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
struct mlx4_bitmap {int last; int max; int top; int reserved_top; int mask; int avail; int /*<<< orphan*/  lock; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int find_aligned_range (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 scalar_t__ likely (int) ; 
 int mlx4_bitmap_alloc (struct mlx4_bitmap*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

u32 mlx4_bitmap_alloc_range(struct mlx4_bitmap *bitmap, int cnt,
			    int align, u32 skip_mask)
{
	u32 obj;

	if (likely(cnt == 1 && align == 1 && !skip_mask))
		return mlx4_bitmap_alloc(bitmap);

	spin_lock(&bitmap->lock);

	obj = find_aligned_range(bitmap->table, bitmap->last,
				 bitmap->max, cnt, align, skip_mask);
	if (obj >= bitmap->max) {
		bitmap->top = (bitmap->top + bitmap->max + bitmap->reserved_top)
				& bitmap->mask;
		obj = find_aligned_range(bitmap->table, 0, bitmap->max,
					 cnt, align, skip_mask);
	}

	if (obj < bitmap->max) {
		bitmap_set(bitmap->table, obj, cnt);
		if (obj == bitmap->last) {
			bitmap->last = (obj + cnt);
			if (bitmap->last >= bitmap->max)
				bitmap->last = 0;
		}
		obj |= bitmap->top;
	} else
		obj = -1;

	if (obj != -1)
		bitmap->avail -= cnt;

	spin_unlock(&bitmap->lock);

	return obj;
}