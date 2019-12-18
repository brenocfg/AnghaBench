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
struct TYPE_2__ {int height; int width; } ;
struct v4l2_window {TYPE_1__ w; int /*<<< orphan*/  chromakey; int /*<<< orphan*/  field; } ;
struct v4l2_rect {int height; int width; } ;
struct v4l2_framebuffer {int dummy; } ;

/* Variables and functions */
 scalar_t__ omap_vout_dss_omap24xx () ; 
 scalar_t__ omap_vout_dss_omap34xx () ; 
 int omap_vout_try_window (struct v4l2_framebuffer*,struct v4l2_window*) ; 

int omap_vout_new_window(struct v4l2_rect *crop,
		struct v4l2_window *win, struct v4l2_framebuffer *fbuf,
		struct v4l2_window *new_win)
{
	int err;

	err = omap_vout_try_window(fbuf, new_win);
	if (err)
		return err;

	/* update our preview window */
	win->w = new_win->w;
	win->field = new_win->field;
	win->chromakey = new_win->chromakey;

	/* Adjust the cropping window to allow for resizing limitation */
	if (omap_vout_dss_omap24xx()) {
		/* For 24xx limit is 8x to 1/2x scaling. */
		if ((crop->height/win->w.height) >= 2)
			crop->height = win->w.height * 2;

		if ((crop->width/win->w.width) >= 2)
			crop->width = win->w.width * 2;

		if (crop->width > 768) {
			/* The OMAP2420 vertical resizing line buffer is 768
			 * pixels wide. If the cropped image is wider than
			 * 768 pixels then it cannot be vertically resized.
			 */
			if (crop->height != win->w.height)
				crop->width = 768;
		}
	} else if (omap_vout_dss_omap34xx()) {
		/* For 34xx limit is 8x to 1/4x scaling. */
		if ((crop->height/win->w.height) >= 4)
			crop->height = win->w.height * 4;

		if ((crop->width/win->w.width) >= 4)
			crop->width = win->w.width * 4;
	}
	return 0;
}