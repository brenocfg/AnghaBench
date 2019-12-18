#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int field; unsigned int height; int width; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_8__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_4__ fmt; } ;
struct saa7134_format {int depth; scalar_t__ planar; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {int width; int height; } ;
struct saa7134_dev {TYPE_2__ crop_bounds; TYPE_1__ crop_current; } ;
struct file {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int V4L2_FIELD_ANY ; 
#define  V4L2_FIELD_BOTTOM 129 
 int V4L2_FIELD_INTERLACED ; 
#define  V4L2_FIELD_TOP 128 
 struct saa7134_format* format_by_fourcc (int /*<<< orphan*/ ) ; 
 unsigned int min (int,int /*<<< orphan*/ ) ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int saa7134_try_fmt_vid_cap(struct file *file, void *priv,
						struct v4l2_format *f)
{
	struct saa7134_dev *dev = video_drvdata(file);
	struct saa7134_format *fmt;
	enum v4l2_field field;
	unsigned int maxw, maxh;

	fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	if (NULL == fmt)
		return -EINVAL;

	field = f->fmt.pix.field;
	maxw  = min(dev->crop_current.width*4,  dev->crop_bounds.width);
	maxh  = min(dev->crop_current.height*4, dev->crop_bounds.height);

	if (V4L2_FIELD_ANY == field) {
		field = (f->fmt.pix.height > maxh/2)
			? V4L2_FIELD_INTERLACED
			: V4L2_FIELD_BOTTOM;
	}
	switch (field) {
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
		maxh = maxh / 2;
		break;
	default:
		field = V4L2_FIELD_INTERLACED;
		break;
	}

	f->fmt.pix.field = field;
	if (f->fmt.pix.width  < 48)
		f->fmt.pix.width  = 48;
	if (f->fmt.pix.height < 32)
		f->fmt.pix.height = 32;
	if (f->fmt.pix.width > maxw)
		f->fmt.pix.width = maxw;
	if (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;
	f->fmt.pix.width &= ~0x03;
	if (fmt->planar)
		f->fmt.pix.bytesperline = f->fmt.pix.width;
	else
		f->fmt.pix.bytesperline =
			(f->fmt.pix.width * fmt->depth) / 8;
	f->fmt.pix.sizeimage =
		(f->fmt.pix.height * f->fmt.pix.width * fmt->depth) / 8;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;

	return 0;
}