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
struct v4l2_pix_format_mplane {int num_planes; TYPE_3__* plane_fmt; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct fimc_frame {int /*<<< orphan*/ * payload; int /*<<< orphan*/ * bytesperline; TYPE_2__* fmt; int /*<<< orphan*/  o_height; int /*<<< orphan*/  o_width; } ;
struct TYPE_6__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;
struct TYPE_5__ {int memplanes; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 

void __fimc_get_format(struct fimc_frame *frame, struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pixm = &f->fmt.pix_mp;
	int i;

	pixm->width = frame->o_width;
	pixm->height = frame->o_height;
	pixm->field = V4L2_FIELD_NONE;
	pixm->pixelformat = frame->fmt->fourcc;
	pixm->colorspace = V4L2_COLORSPACE_JPEG;
	pixm->num_planes = frame->fmt->memplanes;

	for (i = 0; i < pixm->num_planes; ++i) {
		pixm->plane_fmt[i].bytesperline = frame->bytesperline[i];
		pixm->plane_fmt[i].sizeimage = frame->payload[i];
	}
}