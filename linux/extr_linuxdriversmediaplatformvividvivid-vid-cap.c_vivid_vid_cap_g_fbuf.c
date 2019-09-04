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
struct TYPE_2__ {scalar_t__ priv; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; } ;
struct v4l2_framebuffer {int capability; TYPE_1__ fmt; int /*<<< orphan*/  flags; } ;
struct vivid_dev {struct v4l2_framebuffer fb_cap; scalar_t__ multiplanar; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int V4L2_FBUF_CAP_BITMAP_CLIPPING ; 
 int V4L2_FBUF_CAP_LIST_CLIPPING ; 
 int /*<<< orphan*/  V4L2_FBUF_FLAG_PRIMARY ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vivid_vid_cap_g_fbuf(struct file *file, void *fh,
				struct v4l2_framebuffer *a)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (dev->multiplanar)
		return -ENOTTY;

	*a = dev->fb_cap;
	a->capability = V4L2_FBUF_CAP_BITMAP_CLIPPING |
			V4L2_FBUF_CAP_LIST_CLIPPING;
	a->flags = V4L2_FBUF_FLAG_PRIMARY;
	a->fmt.field = V4L2_FIELD_NONE;
	a->fmt.colorspace = V4L2_COLORSPACE_SRGB;
	a->fmt.priv = 0;
	return 0;
}