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
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {scalar_t__ pad; int target; scalar_t__ which; struct v4l2_rect r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct fimc_frame {int dummy; } ;
struct TYPE_2__ {struct fimc_ctx* ctx; } ;
struct fimc_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  slock; int /*<<< orphan*/  state; TYPE_1__ vid_cap; } ;
struct fimc_ctx {int /*<<< orphan*/  state; struct fimc_frame d_frame; struct fimc_frame s_frame; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIMC_COMPOSE ; 
 scalar_t__ FIMC_SD_PAD_SOURCE ; 
 int /*<<< orphan*/  ST_CAPT_APPLY_CFG ; 
#define  V4L2_SEL_TGT_COMPOSE 129 
#define  V4L2_SEL_TGT_CROP 128 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  dbg (char*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_capture_try_selection (struct fimc_ctx*,struct v4l2_rect*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_frame_crop (struct fimc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fimc_dev* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 struct v4l2_rect* v4l2_subdev_get_try_compose (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,scalar_t__) ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,scalar_t__) ; 

__attribute__((used)) static int fimc_subdev_set_selection(struct v4l2_subdev *sd,
				     struct v4l2_subdev_pad_config *cfg,
				     struct v4l2_subdev_selection *sel)
{
	struct fimc_dev *fimc = v4l2_get_subdevdata(sd);
	struct fimc_ctx *ctx = fimc->vid_cap.ctx;
	struct fimc_frame *f = &ctx->s_frame;
	struct v4l2_rect *r = &sel->r;
	struct v4l2_rect *try_sel;
	unsigned long flags;

	if (sel->pad == FIMC_SD_PAD_SOURCE)
		return -EINVAL;

	mutex_lock(&fimc->lock);
	fimc_capture_try_selection(ctx, r, V4L2_SEL_TGT_CROP);

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		try_sel = v4l2_subdev_get_try_crop(sd, cfg, sel->pad);
		break;
	case V4L2_SEL_TGT_COMPOSE:
		try_sel = v4l2_subdev_get_try_compose(sd, cfg, sel->pad);
		f = &ctx->d_frame;
		break;
	default:
		mutex_unlock(&fimc->lock);
		return -EINVAL;
	}

	if (sel->which == V4L2_SUBDEV_FORMAT_TRY) {
		*try_sel = sel->r;
	} else {
		spin_lock_irqsave(&fimc->slock, flags);
		set_frame_crop(f, r->left, r->top, r->width, r->height);
		set_bit(ST_CAPT_APPLY_CFG, &fimc->state);
		if (sel->target == V4L2_SEL_TGT_COMPOSE)
			ctx->state |= FIMC_COMPOSE;
		spin_unlock_irqrestore(&fimc->slock, flags);
	}

	dbg("target %#x: (%d,%d)/%dx%d", sel->target, r->left, r->top,
	    r->width, r->height);

	mutex_unlock(&fimc->lock);
	return 0;
}