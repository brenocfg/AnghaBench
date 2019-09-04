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
struct v4l2_pix_format_mplane {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* plane_fmt; } ;
struct fimc_frame {struct fimc_fmt* fmt; scalar_t__ offs_v; scalar_t__ offs_h; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  o_height; int /*<<< orphan*/  o_width; int /*<<< orphan*/  f_height; int /*<<< orphan*/  f_width; int /*<<< orphan*/ * payload; int /*<<< orphan*/ * bytesperline; } ;
struct fimc_fmt {int memplanes; } ;
struct TYPE_2__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;

/* Variables and functions */

__attribute__((used)) static void __set_frame_format(struct fimc_frame *frame, struct fimc_fmt *fmt,
			       struct v4l2_pix_format_mplane *pixm)
{
	int i;

	for (i = 0; i < fmt->memplanes; i++) {
		frame->bytesperline[i] = pixm->plane_fmt[i].bytesperline;
		frame->payload[i] = pixm->plane_fmt[i].sizeimage;
	}

	frame->f_width = pixm->width;
	frame->f_height	= pixm->height;
	frame->o_width = pixm->width;
	frame->o_height = pixm->height;
	frame->width = pixm->width;
	frame->height = pixm->height;
	frame->offs_h = 0;
	frame->offs_v = 0;
	frame->fmt = fmt;
}