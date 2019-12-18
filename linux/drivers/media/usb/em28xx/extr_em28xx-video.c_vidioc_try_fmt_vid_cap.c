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
struct TYPE_5__ {unsigned int width; unsigned int height; unsigned int bytesperline; unsigned int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct file {int dummy; } ;
struct em28xx_v4l2 {scalar_t__ interlaced_fieldmode; scalar_t__ progressive; } ;
struct em28xx_fmt {unsigned int depth; int /*<<< orphan*/  fourcc; } ;
struct TYPE_4__ {scalar_t__ is_em2800; } ;
struct em28xx {TYPE_1__ board; struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_FIELD_TOP ; 
 int /*<<< orphan*/  em28xx_videodbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct em28xx_fmt* format ; 
 struct em28xx_fmt* format_by_fourcc (int /*<<< orphan*/ ) ; 
 unsigned int norm_maxh (struct em28xx*) ; 
 unsigned int norm_maxw (struct em28xx*) ; 
 int /*<<< orphan*/  scale_to_size (struct em28xx*,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  size_to_scale (struct em28xx*,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (unsigned int*,int,unsigned int,int,unsigned int*,int,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct em28xx* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_try_fmt_vid_cap(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct em28xx         *dev   = video_drvdata(file);
	struct em28xx_v4l2    *v4l2  = dev->v4l2;
	unsigned int          width  = f->fmt.pix.width;
	unsigned int          height = f->fmt.pix.height;
	unsigned int          maxw   = norm_maxw(dev);
	unsigned int          maxh   = norm_maxh(dev);
	unsigned int          hscale, vscale;
	struct em28xx_fmt     *fmt;

	fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	if (!fmt) {
		fmt = &format[0];
		em28xx_videodbg("Fourcc format (%08x) invalid. Using default (%08x).\n",
				f->fmt.pix.pixelformat, fmt->fourcc);
	}

	if (dev->board.is_em2800) {
		/* the em2800 can only scale down to 50% */
		height = height > (3 * maxh / 4) ? maxh : maxh / 2;
		width = width > (3 * maxw / 4) ? maxw : maxw / 2;
		/*
		 * MaxPacketSize for em2800 is too small to capture at full
		 * resolution use half of maxw as the scaler can only scale
		 * to 50%
		 */
		if (width == maxw && height == maxh)
			width /= 2;
	} else {
		/*
		 * width must even because of the YUYV format
		 * height must be even because of interlacing
		 */
		v4l_bound_align_image(&width, 48, maxw, 1, &height, 32, maxh,
				      1, 0);
	}
	/* Avoid division by zero at size_to_scale */
	if (width < 1)
		width = 1;
	if (height < 1)
		height = 1;

	size_to_scale(dev, width, height, &hscale, &vscale);
	scale_to_size(dev, hscale, vscale, &width, &height);

	f->fmt.pix.width = width;
	f->fmt.pix.height = height;
	f->fmt.pix.pixelformat = fmt->fourcc;
	f->fmt.pix.bytesperline = (width * fmt->depth + 7) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.bytesperline * height;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	if (v4l2->progressive)
		f->fmt.pix.field = V4L2_FIELD_NONE;
	else
		f->fmt.pix.field = v4l2->interlaced_fieldmode ?
			   V4L2_FIELD_INTERLACED : V4L2_FIELD_TOP;

	return 0;
}