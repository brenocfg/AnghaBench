#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int width; int height; int left; int top; } ;
struct v4l2_window {TYPE_2__ w; } ;
struct v4l2_rect {int width; int height; } ;
struct v4l2_pix_format {int dummy; } ;
struct TYPE_3__ {int width; int height; } ;
struct v4l2_framebuffer {TYPE_1__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_vout_default_crop (struct v4l2_pix_format*,struct v4l2_framebuffer*,struct v4l2_rect*) ; 

void omap_vout_new_format(struct v4l2_pix_format *pix,
		struct v4l2_framebuffer *fbuf, struct v4l2_rect *crop,
		struct v4l2_window *win)
{
	/* crop defines the preview source window in the image capture
	 * buffer
	 */
	omap_vout_default_crop(pix, fbuf, crop);

	/* win defines the preview target window on the display */
	win->w.width = crop->width;
	win->w.height = crop->height;
	win->w.left = ((fbuf->fmt.width - win->w.width) >> 1) & ~1;
	win->w.top = ((fbuf->fmt.height - win->w.height) >> 1) & ~1;
}