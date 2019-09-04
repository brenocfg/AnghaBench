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
struct msi_bitmap {int irq_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int get_count_order (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int msi_bitmap_alloc_hwirqs(struct msi_bitmap *bmp, int num)
{
	unsigned long flags;
	int offset, order = get_count_order(num);

	spin_lock_irqsave(&bmp->lock, flags);

	offset = bitmap_find_next_zero_area(bmp->bitmap, bmp->irq_count, 0,
					    num, (1 << order) - 1);
	if (offset > bmp->irq_count)
		goto err;

	bitmap_set(bmp->bitmap, offset, num);
	spin_unlock_irqrestore(&bmp->lock, flags);

	pr_debug("msi_bitmap: allocated 0x%x at offset 0x%x\n", num, offset);

	return offset;
err:
	spin_unlock_irqrestore(&bmp->lock, flags);
	return -ENOMEM;
}