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
struct v4l2_rect {int width; int height; } ;
struct vivid_dev {unsigned int clipcount_cap; int /*<<< orphan*/ * clips_cap; int /*<<< orphan*/ * bitmap_cap; int /*<<< orphan*/  overlay_cap_field; int /*<<< orphan*/  overlay_cap_left; int /*<<< orphan*/  overlay_cap_top; scalar_t__ multiplanar; struct v4l2_rect compose_cap; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_window {unsigned int clipcount; int /*<<< orphan*/ * clips; int /*<<< orphan*/ * bitmap; int /*<<< orphan*/  field; TYPE_2__ w; } ;
struct TYPE_3__ {struct v4l2_window win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOTTY ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vidioc_g_fmt_vid_overlay(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct vivid_dev *dev = video_drvdata(file);
	const struct v4l2_rect *compose = &dev->compose_cap;
	struct v4l2_window *win = &f->fmt.win;
	unsigned clipcount = win->clipcount;

	if (dev->multiplanar)
		return -ENOTTY;

	win->w.top = dev->overlay_cap_top;
	win->w.left = dev->overlay_cap_left;
	win->w.width = compose->width;
	win->w.height = compose->height;
	win->field = dev->overlay_cap_field;
	win->clipcount = dev->clipcount_cap;
	if (clipcount > dev->clipcount_cap)
		clipcount = dev->clipcount_cap;
	if (dev->bitmap_cap == NULL)
		win->bitmap = NULL;
	else if (win->bitmap) {
		if (copy_to_user(win->bitmap, dev->bitmap_cap,
		    ((compose->width + 7) / 8) * compose->height))
			return -EFAULT;
	}
	if (clipcount && win->clips) {
		if (copy_to_user(win->clips, dev->clips_cap,
				 clipcount * sizeof(dev->clips_cap[0])))
			return -EFAULT;
	}
	return 0;
}