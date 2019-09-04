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
struct TYPE_5__ {int width; int height; int bytesperline; int sizeimage; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; } ;
struct TYPE_6__ {TYPE_2__ pix; } ;
struct v4l2_format {TYPE_3__ fmt; } ;
struct stk1160 {int width; int height; TYPE_1__* fmt; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 struct stk1160* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_fmt_vid_cap(struct file *file, void *priv,
					struct v4l2_format *f)
{
	struct stk1160 *dev = video_drvdata(file);

	f->fmt.pix.width = dev->width;
	f->fmt.pix.height = dev->height;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.pixelformat = dev->fmt->fourcc;
	f->fmt.pix.bytesperline = dev->width * 2;
	f->fmt.pix.sizeimage = dev->height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	return 0;
}