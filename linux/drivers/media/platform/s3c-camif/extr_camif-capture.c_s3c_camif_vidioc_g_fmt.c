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
struct v4l2_pix_format {int bytesperline; int width; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  sizeimage; } ;
struct TYPE_2__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct file {int dummy; } ;
struct camif_frame {int f_width; int /*<<< orphan*/  f_height; } ;
struct camif_vp {int /*<<< orphan*/  payload; struct camif_fmt* out_fmt; struct camif_frame out_frame; } ;
struct camif_fmt {int ybpp; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct camif_vp* video_drvdata (struct file*) ; 

__attribute__((used)) static int s3c_camif_vidioc_g_fmt(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	struct camif_vp *vp = video_drvdata(file);
	struct v4l2_pix_format *pix = &f->fmt.pix;
	struct camif_frame *frame = &vp->out_frame;
	const struct camif_fmt *fmt = vp->out_fmt;

	pix->bytesperline = frame->f_width * fmt->ybpp;
	pix->sizeimage = vp->payload;

	pix->pixelformat = fmt->fourcc;
	pix->width = frame->f_width;
	pix->height = frame->f_height;
	pix->field = V4L2_FIELD_NONE;
	pix->colorspace = V4L2_COLORSPACE_JPEG;

	return 0;
}