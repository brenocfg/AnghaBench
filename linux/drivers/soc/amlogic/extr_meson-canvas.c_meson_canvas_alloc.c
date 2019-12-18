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
typedef  int u8 ;
struct meson_canvas {int* used; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENODEV ; 
 int NUM_CANVAS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int meson_canvas_alloc(struct meson_canvas *canvas, u8 *canvas_index)
{
	int i;
	unsigned long flags;

	spin_lock_irqsave(&canvas->lock, flags);
	for (i = 0; i < NUM_CANVAS; ++i) {
		if (!canvas->used[i]) {
			canvas->used[i] = 1;
			spin_unlock_irqrestore(&canvas->lock, flags);
			*canvas_index = i;
			return 0;
		}
	}
	spin_unlock_irqrestore(&canvas->lock, flags);

	dev_err(canvas->dev, "No more canvas available\n");
	return -ENODEV;
}