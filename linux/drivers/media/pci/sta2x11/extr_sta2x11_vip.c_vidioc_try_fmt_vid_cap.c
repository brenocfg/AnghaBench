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
struct TYPE_3__ {scalar_t__ pixelformat; int field; int height; int width; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct sta2x11_vip {int std; int /*<<< orphan*/  v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
#define  V4L2_FIELD_ANY 131 
#define  V4L2_FIELD_BOTTOM 130 
#define  V4L2_FIELD_INTERLACED 129 
#define  V4L2_FIELD_TOP 128 
 scalar_t__ V4L2_PIX_FMT_UYVY ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 
 struct sta2x11_vip* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct sta2x11_vip *vip = video_drvdata(file);
	int interlace_lim;

	if (V4L2_PIX_FMT_UYVY != f->fmt.pix.pixelformat) {
		v4l2_warn(&vip->v4l2_dev, "Invalid format, only UYVY supported\n");
		return -EINVAL;
	}

	if (V4L2_STD_525_60 & vip->std)
		interlace_lim = 240;
	else
		interlace_lim = 288;

	switch (f->fmt.pix.field) {
	default:
	case V4L2_FIELD_ANY:
		if (interlace_lim < f->fmt.pix.height)
			f->fmt.pix.field = V4L2_FIELD_INTERLACED;
		else
			f->fmt.pix.field = V4L2_FIELD_BOTTOM;
		break;
	case V4L2_FIELD_TOP:
	case V4L2_FIELD_BOTTOM:
		if (interlace_lim < f->fmt.pix.height)
			f->fmt.pix.height = interlace_lim;
		break;
	case V4L2_FIELD_INTERLACED:
		break;
	}

	/* It is the only supported format */
	f->fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	f->fmt.pix.height &= ~1;
	if (2 * interlace_lim < f->fmt.pix.height)
		f->fmt.pix.height = 2 * interlace_lim;
	if (200 > f->fmt.pix.height)
		f->fmt.pix.height = 200;
	f->fmt.pix.width = 720;
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.width * 2 * f->fmt.pix.height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	return 0;
}