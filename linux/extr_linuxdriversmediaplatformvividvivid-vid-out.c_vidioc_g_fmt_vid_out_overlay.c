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
struct vivid_dev {unsigned int clipcount_out; int /*<<< orphan*/ * clips_out; struct v4l2_rect compose_out; int /*<<< orphan*/ * bitmap_out; int /*<<< orphan*/  global_alpha_out; int /*<<< orphan*/  chromakey_out; int /*<<< orphan*/  overlay_out_left; int /*<<< orphan*/  overlay_out_top; int /*<<< orphan*/  has_fb; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_window {unsigned int clipcount; int /*<<< orphan*/ * clips; int /*<<< orphan*/ * bitmap; int /*<<< orphan*/  global_alpha; int /*<<< orphan*/  chromakey; int /*<<< orphan*/  field; TYPE_2__ w; } ;
struct TYPE_3__ {struct v4l2_window win; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_ANY ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vidioc_g_fmt_vid_out_overlay(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct vivid_dev *dev = video_drvdata(file);
	const struct v4l2_rect *compose = &dev->compose_out;
	struct v4l2_window *win = &f->fmt.win;
	unsigned clipcount = win->clipcount;

	if (!dev->has_fb)
		return -EINVAL;
	win->w.top = dev->overlay_out_top;
	win->w.left = dev->overlay_out_left;
	win->w.width = compose->width;
	win->w.height = compose->height;
	win->clipcount = dev->clipcount_out;
	win->field = V4L2_FIELD_ANY;
	win->chromakey = dev->chromakey_out;
	win->global_alpha = dev->global_alpha_out;
	if (clipcount > dev->clipcount_out)
		clipcount = dev->clipcount_out;
	if (dev->bitmap_out == NULL)
		win->bitmap = NULL;
	else if (win->bitmap) {
		if (copy_to_user(win->bitmap, dev->bitmap_out,
		    ((dev->compose_out.width + 7) / 8) * dev->compose_out.height))
			return -EFAULT;
	}
	if (clipcount && win->clips) {
		if (copy_to_user(win->clips, dev->clips_out,
				 clipcount * sizeof(dev->clips_out[0])))
			return -EFAULT;
	}
	return 0;
}