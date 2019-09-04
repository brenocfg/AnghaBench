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
struct viu_fmt {int depth; } ;
struct TYPE_3__ {int height; int width; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_4__ {TYPE_1__ pix; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 struct viu_fmt* format_by_fourcc (int /*<<< orphan*/ ) ; 
 unsigned int norm_maxh () ; 
 unsigned int norm_maxw () ; 

__attribute__((used)) static int vidioc_try_fmt_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct viu_fmt *fmt;
	unsigned int maxw, maxh;

	fmt = format_by_fourcc(f->fmt.pix.pixelformat);
	if (!fmt) {
		dprintk(1, "Fourcc format (0x%08x) invalid.",
			f->fmt.pix.pixelformat);
		return -EINVAL;
	}

	maxw  = norm_maxw();
	maxh  = norm_maxh();

	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	if (f->fmt.pix.height < 32)
		f->fmt.pix.height = 32;
	if (f->fmt.pix.height > maxh)
		f->fmt.pix.height = maxh;
	if (f->fmt.pix.width < 48)
		f->fmt.pix.width = 48;
	if (f->fmt.pix.width > maxw)
		f->fmt.pix.width = maxw;
	f->fmt.pix.width &= ~0x03;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	return 0;
}