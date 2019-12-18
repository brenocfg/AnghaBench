#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ offset; int /*<<< orphan*/  depth; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  type; } ;
struct xenfb_info {int resize_dpy; int /*<<< orphan*/  resize_lock; TYPE_3__ resize; } ;
struct TYPE_5__ {int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct TYPE_4__ {int /*<<< orphan*/  line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct xenfb_info* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  XENFB_TYPE_RESIZE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int xenfb_set_par(struct fb_info *info)
{
	struct xenfb_info *xenfb_info;
	unsigned long flags;

	xenfb_info = info->par;

	spin_lock_irqsave(&xenfb_info->resize_lock, flags);
	xenfb_info->resize.type = XENFB_TYPE_RESIZE;
	xenfb_info->resize.width = info->var.xres;
	xenfb_info->resize.height = info->var.yres;
	xenfb_info->resize.stride = info->fix.line_length;
	xenfb_info->resize.depth = info->var.bits_per_pixel;
	xenfb_info->resize.offset = 0;
	xenfb_info->resize_dpy = 1;
	spin_unlock_irqrestore(&xenfb_info->resize_lock, flags);
	return 0;
}