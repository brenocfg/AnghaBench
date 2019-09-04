#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct v4l2_rect {scalar_t__ top; scalar_t__ left; scalar_t__ width; scalar_t__ height; } ;
struct mtk_mdp_variant {TYPE_3__* pix_min; TYPE_2__* pix_align; } ;
struct mtk_mdp_frame {scalar_t__ width; scalar_t__ height; } ;
struct mtk_mdp_dev {TYPE_1__* pdev; struct mtk_mdp_variant* variant; } ;
struct TYPE_10__ {TYPE_4__* rotate; } ;
struct mtk_mdp_ctx {int /*<<< orphan*/  id; TYPE_5__ ctrls; struct mtk_mdp_dev* mdp_dev; } ;
struct TYPE_9__ {int val; } ;
struct TYPE_8__ {scalar_t__ target_rot_en_w; scalar_t__ target_rot_en_h; scalar_t__ target_rot_dis_w; scalar_t__ target_rot_dis_h; } ;
struct TYPE_7__ {scalar_t__ target_w; scalar_t__ target_h; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtk_mdp_bound_align_image (scalar_t__*,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mtk_mdp_check_crop_change (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 struct mtk_mdp_frame* mtk_mdp_ctx_get_frame (struct mtk_mdp_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  mtk_mdp_dbg (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static int mtk_mdp_try_crop(struct mtk_mdp_ctx *ctx, u32 type,
			    struct v4l2_rect *r)
{
	struct mtk_mdp_frame *frame;
	struct mtk_mdp_dev *mdp = ctx->mdp_dev;
	struct mtk_mdp_variant *variant = mdp->variant;
	u32 align_w, align_h, new_w, new_h;
	u32 min_w, min_h, max_w, max_h;

	if (r->top < 0 || r->left < 0) {
		dev_err(&ctx->mdp_dev->pdev->dev,
			"doesn't support negative values for top & left\n");
		return -EINVAL;
	}

	mtk_mdp_dbg(2, "[%d] type:%d, set wxh:%dx%d", ctx->id, type,
		    r->width, r->height);

	frame = mtk_mdp_ctx_get_frame(ctx, type);
	max_w = frame->width;
	max_h = frame->height;
	new_w = r->width;
	new_h = r->height;

	if (V4L2_TYPE_IS_OUTPUT(type)) {
		align_w = 1;
		align_h = 1;
		min_w = 64;
		min_h = 32;
	} else {
		align_w = variant->pix_align->target_w;
		align_h = variant->pix_align->target_h;
		if (ctx->ctrls.rotate->val == 90 ||
		    ctx->ctrls.rotate->val == 270) {
			max_w = frame->height;
			max_h = frame->width;
			min_w = variant->pix_min->target_rot_en_w;
			min_h = variant->pix_min->target_rot_en_h;
			new_w = r->height;
			new_h = r->width;
		} else {
			min_w = variant->pix_min->target_rot_dis_w;
			min_h = variant->pix_min->target_rot_dis_h;
		}
	}

	mtk_mdp_dbg(2, "[%d] align:%dx%d, min:%dx%d, new:%dx%d", ctx->id,
		    align_w, align_h, min_w, min_h, new_w, new_h);

	mtk_mdp_bound_align_image(&new_w, min_w, max_w, align_w,
				  &new_h, min_h, max_h, align_h);

	if (!V4L2_TYPE_IS_OUTPUT(type) &&
		(ctx->ctrls.rotate->val == 90 ||
		ctx->ctrls.rotate->val == 270))
		mtk_mdp_check_crop_change(new_h, new_w,
					  &r->width, &r->height);
	else
		mtk_mdp_check_crop_change(new_w, new_h,
					  &r->width, &r->height);

	/* adjust left/top if cropping rectangle is out of bounds */
	/* Need to add code to algin left value with 2's multiple */
	if (r->left + new_w > max_w)
		r->left = max_w - new_w;
	if (r->top + new_h > max_h)
		r->top = max_h - new_h;

	if (r->left & 1)
		r->left -= 1;

	mtk_mdp_dbg(2, "[%d] crop l,t,w,h:%d,%d,%d,%d, max:%dx%d", ctx->id,
		    r->left, r->top, r->width,
		    r->height, max_w, max_h);
	return 0;
}