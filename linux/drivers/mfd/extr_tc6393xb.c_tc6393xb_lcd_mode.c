#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tc6393xb {int /*<<< orphan*/  lock; scalar_t__ scr; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct fb_videomode {int pixclock; } ;

/* Variables and functions */
 scalar_t__ SCR_PLL1CR ; 
 struct tc6393xb* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int tc6393xb_lcd_mode(struct platform_device *fb,
					const struct fb_videomode *mode) {
	struct tc6393xb *tc6393xb = dev_get_drvdata(fb->dev.parent);
	unsigned long flags;

	raw_spin_lock_irqsave(&tc6393xb->lock, flags);

	iowrite16(mode->pixclock, tc6393xb->scr + SCR_PLL1CR + 0);
	iowrite16(mode->pixclock >> 16, tc6393xb->scr + SCR_PLL1CR + 2);

	raw_spin_unlock_irqrestore(&tc6393xb->lock, flags);

	return 0;
}