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
struct v4l2_plane_pix_format {int bytesperline; int sizeimage; } ;
struct v4l2_pix_format_mplane {int width; int height; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  num_planes; struct v4l2_plane_pix_format* plane_fmt; } ;
struct TYPE_2__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct flite_frame {int f_width; int f_height; struct fimc_fmt* fmt; } ;
struct fimc_lite {struct flite_frame out_frame; } ;
struct fimc_fmt {int* depth; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  fourcc; int /*<<< orphan*/  memplanes; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct fimc_lite* video_drvdata (struct file*) ; 

__attribute__((used)) static int fimc_lite_g_fmt_mplane(struct file *file, void *fh,
				  struct v4l2_format *f)
{
	struct fimc_lite *fimc = video_drvdata(file);
	struct v4l2_pix_format_mplane *pixm = &f->fmt.pix_mp;
	struct v4l2_plane_pix_format *plane_fmt = &pixm->plane_fmt[0];
	struct flite_frame *frame = &fimc->out_frame;
	const struct fimc_fmt *fmt = frame->fmt;

	plane_fmt->bytesperline = (frame->f_width * fmt->depth[0]) / 8;
	plane_fmt->sizeimage = plane_fmt->bytesperline * frame->f_height;

	pixm->num_planes = fmt->memplanes;
	pixm->pixelformat = fmt->fourcc;
	pixm->width = frame->f_width;
	pixm->height = frame->f_height;
	pixm->field = V4L2_FIELD_NONE;
	pixm->colorspace = fmt->colorspace;
	return 0;
}