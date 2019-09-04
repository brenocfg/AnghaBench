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
struct TYPE_7__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; } ;
struct TYPE_8__ {TYPE_3__ pix; } ;
struct v4l2_format {TYPE_4__ fmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  field; } ;
struct tm6000_fh {int width; int height; TYPE_2__* fmt; TYPE_1__ vb_vidq; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int depth; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 

__attribute__((used)) static int vidioc_g_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct tm6000_fh  *fh = priv;

	f->fmt.pix.width        = fh->width;
	f->fmt.pix.height       = fh->height;
	f->fmt.pix.field        = fh->vb_vidq.field;
	f->fmt.pix.pixelformat  = fh->fmt->fourcc;
	f->fmt.pix.colorspace   = V4L2_COLORSPACE_SMPTE170M;
	f->fmt.pix.bytesperline =
		(f->fmt.pix.width * fh->fmt->depth) >> 3;
	f->fmt.pix.sizeimage =
		f->fmt.pix.height * f->fmt.pix.bytesperline;

	return 0;
}