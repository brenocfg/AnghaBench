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
struct TYPE_3__ {int field; unsigned int width; unsigned int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;
struct cx25821_fmt {int depth; } ;
struct cx25821_dev {int tvnorm; } ;
struct cx25821_channel {struct cx25821_dev* dev; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int V4L2_FIELD_BOTTOM ; 
 int V4L2_FIELD_INTERLACED ; 
 int V4L2_FIELD_TOP ; 
 int V4L2_STD_625_50 ; 
 struct cx25821_fmt* cx25821_format_by_fourcc (int /*<<< orphan*/ ) ; 
 struct cx25821_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int cx25821_vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				   struct v4l2_format *f)
{
	struct cx25821_channel *chan = video_drvdata(file);
	struct cx25821_dev *dev = chan->dev;
	const struct cx25821_fmt *fmt;
	enum v4l2_field field = f->fmt.pix.field;
	unsigned int maxh;
	unsigned w;

	fmt = cx25821_format_by_fourcc(f->fmt.pix.pixelformat);
	if (NULL == fmt)
		return -EINVAL;
	maxh = (dev->tvnorm & V4L2_STD_625_50) ? 576 : 480;

	w = f->fmt.pix.width;
	if (field != V4L2_FIELD_BOTTOM)
		field = V4L2_FIELD_TOP;
	if (w < 352) {
		w = 176;
		f->fmt.pix.height = maxh / 4;
	} else if (w < 720) {
		w = 352;
		f->fmt.pix.height = maxh / 2;
	} else {
		w = 720;
		f->fmt.pix.height = maxh;
		field = V4L2_FIELD_INTERLACED;
	}
	f->fmt.pix.field = field;
	f->fmt.pix.width = w;
	f->fmt.pix.bytesperline = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	return 0;
}