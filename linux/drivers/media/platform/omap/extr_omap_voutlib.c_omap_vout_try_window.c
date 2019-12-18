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
struct v4l2_rect {scalar_t__ left; scalar_t__ width; scalar_t__ top; int height; } ;
struct v4l2_window {int /*<<< orphan*/ * bitmap; scalar_t__ clipcount; int /*<<< orphan*/ * clips; int /*<<< orphan*/  field; struct v4l2_rect w; } ;
struct TYPE_2__ {scalar_t__ width; int height; } ;
struct v4l2_framebuffer {TYPE_1__ fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 

int omap_vout_try_window(struct v4l2_framebuffer *fbuf,
			struct v4l2_window *new_win)
{
	struct v4l2_rect try_win;

	/* make a working copy of the new_win rectangle */
	try_win = new_win->w;

	/* adjust the preview window so it fits on the display by clipping any
	 * offscreen areas
	 */
	if (try_win.left < 0) {
		try_win.width += try_win.left;
		try_win.left = 0;
	}
	if (try_win.top < 0) {
		try_win.height += try_win.top;
		try_win.top = 0;
	}
	try_win.width = (try_win.width < fbuf->fmt.width) ?
		try_win.width : fbuf->fmt.width;
	try_win.height = (try_win.height < fbuf->fmt.height) ?
		try_win.height : fbuf->fmt.height;
	if (try_win.left + try_win.width > fbuf->fmt.width)
		try_win.width = fbuf->fmt.width - try_win.left;
	if (try_win.top + try_win.height > fbuf->fmt.height)
		try_win.height = fbuf->fmt.height - try_win.top;
	try_win.width &= ~1;
	try_win.height &= ~1;

	if (try_win.width <= 0 || try_win.height <= 0)
		return -EINVAL;

	/* We now have a valid preview window, so go with it */
	new_win->w = try_win;
	new_win->field = V4L2_FIELD_NONE;
	new_win->clips = NULL;
	new_win->clipcount = 0;
	new_win->bitmap = NULL;

	return 0;
}