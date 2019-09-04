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
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ top; scalar_t__ left; scalar_t__ width; scalar_t__ height; } ;
struct v4l2_crop {scalar_t__ type; TYPE_4__ c; } ;
struct fimc_frame {scalar_t__ o_width; scalar_t__ o_height; int /*<<< orphan*/  f_height; int /*<<< orphan*/  f_width; TYPE_2__* fmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  vfd; } ;
struct fimc_dev {TYPE_3__* variant; TYPE_1__ m2m; } ;
struct fimc_ctx {struct fimc_frame s_frame; struct fimc_frame d_frame; struct fimc_dev* fimc_dev; } ;
struct TYPE_7__ {int min_inp_pixsize; int min_out_pixsize; int min_vsize_align; int hor_offs_align; } ;
struct TYPE_6__ {int memplanes; scalar_t__* depth; int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  dbg (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ffs (int) ; 
 scalar_t__ fimc_fmt_is_rgb (int /*<<< orphan*/ ) ; 
 void* round_down (scalar_t__,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (scalar_t__*,int,scalar_t__,int,scalar_t__*,int,scalar_t__,int,int) ; 

__attribute__((used)) static int fimc_m2m_try_crop(struct fimc_ctx *ctx, struct v4l2_crop *cr)
{
	struct fimc_dev *fimc = ctx->fimc_dev;
	struct fimc_frame *f;
	u32 min_size, halign, depth = 0;
	int i;

	if (cr->c.top < 0 || cr->c.left < 0) {
		v4l2_err(&fimc->m2m.vfd,
			"doesn't support negative values for top & left\n");
		return -EINVAL;
	}
	if (cr->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		f = &ctx->d_frame;
	else if (cr->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		f = &ctx->s_frame;
	else
		return -EINVAL;

	min_size = (f == &ctx->s_frame) ?
		fimc->variant->min_inp_pixsize : fimc->variant->min_out_pixsize;

	/* Get pixel alignment constraints. */
	if (fimc->variant->min_vsize_align == 1)
		halign = fimc_fmt_is_rgb(f->fmt->color) ? 0 : 1;
	else
		halign = ffs(fimc->variant->min_vsize_align) - 1;

	for (i = 0; i < f->fmt->memplanes; i++)
		depth += f->fmt->depth[i];

	v4l_bound_align_image(&cr->c.width, min_size, f->o_width,
			      ffs(min_size) - 1,
			      &cr->c.height, min_size, f->o_height,
			      halign, 64/(ALIGN(depth, 8)));

	/* adjust left/top if cropping rectangle is out of bounds */
	if (cr->c.left + cr->c.width > f->o_width)
		cr->c.left = f->o_width - cr->c.width;
	if (cr->c.top + cr->c.height > f->o_height)
		cr->c.top = f->o_height - cr->c.height;

	cr->c.left = round_down(cr->c.left, min_size);
	cr->c.top  = round_down(cr->c.top, fimc->variant->hor_offs_align);

	dbg("l:%d, t:%d, w:%d, h:%d, f_w: %d, f_h: %d",
	    cr->c.left, cr->c.top, cr->c.width, cr->c.height,
	    f->f_width, f->f_height);

	return 0;
}