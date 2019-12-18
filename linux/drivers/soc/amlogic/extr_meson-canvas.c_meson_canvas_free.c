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
typedef  size_t u8 ;
struct meson_canvas {int /*<<< orphan*/  lock; scalar_t__* used; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int meson_canvas_free(struct meson_canvas *canvas, u8 canvas_index)
{
	unsigned long flags;

	spin_lock_irqsave(&canvas->lock, flags);
	if (!canvas->used[canvas_index]) {
		dev_err(canvas->dev,
			"Trying to free unused canvas %u\n", canvas_index);
		spin_unlock_irqrestore(&canvas->lock, flags);
		return -EINVAL;
	}
	canvas->used[canvas_index] = 0;
	spin_unlock_irqrestore(&canvas->lock, flags);

	return 0;
}