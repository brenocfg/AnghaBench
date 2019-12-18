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
struct TYPE_5__ {int field; unsigned int height; int width; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct tw68_format {int depth; } ;
struct tw68_dev {TYPE_1__* tvnorm; } ;
struct file {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
#define  V4L2_FIELD_BOTTOM 132 
#define  V4L2_FIELD_INTERLACED 131 
#define  V4L2_FIELD_SEQ_BT 130 
#define  V4L2_FIELD_SEQ_TB 129 
#define  V4L2_FIELD_TOP 128 
 int V4L2_STD_525_60 ; 
 struct tw68_format* format_by_fourcc (int /*<<< orphan*/ ) ; 
 struct tw68_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw68_try_fmt_vid_cap(struct file *file, void *priv,
						struct v4l2_format *f)
{
	struct tw68_dev *dev = video_drvdata(file);
	const struct tw68_format *fmt;
	enum v4l2_field field;
	unsigned int maxh;

	fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	if (NULL == fmt)
		return -EINVAL;

	field = f->fmt.pix.field;
	maxh  = (dev->tvnorm->id & V4L2_STD_525_60) ? 480 : 576;

	switch (field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
		break;
	case V4L2_FIELD_INTERLACED:
	case V4L2_FIELD_SEQ_BT:
	case V4L2_FIELD_SEQ_TB:
		maxh = maxh * 2;
		break;
	default:
		field = (f->fmt.pix.height > maxh / 2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
		break;
	}

	f->fmt.pix.field = field;
	if (f->fmt.pix.width  < 48)
		f->fmt.pix.width  = 48;
	if (f->fmt.pix.height < 32)
		f->fmt.pix.height = 32;
	if (f->fmt.pix.width > 720)
		f->fmt.pix.width = 720;
	if (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;
	f->fmt.pix.width &= ~0x03;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * (fmt->depth)) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	return 0;
}