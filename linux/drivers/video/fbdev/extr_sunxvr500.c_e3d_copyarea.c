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
struct fb_info {int /*<<< orphan*/  screen_base; struct e3d_info* par; } ;
struct fb_copyarea {int dummy; } ;
struct e3d_info {int /*<<< orphan*/  lock; scalar_t__ fb8_buf_diff; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfb_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void e3d_copyarea(struct fb_info *info, const struct fb_copyarea *area)
{
	struct e3d_info *ep = info->par;
	unsigned long flags;

	spin_lock_irqsave(&ep->lock, flags);
	cfb_copyarea(info, area);
	info->screen_base += ep->fb8_buf_diff;
	cfb_copyarea(info, area);
	info->screen_base -= ep->fb8_buf_diff;
	spin_unlock_irqrestore(&ep->lock, flags);
}