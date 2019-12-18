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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {TYPE_1__ r; int /*<<< orphan*/  target; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct mtk_mdp_frame {TYPE_2__ crop; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mtk_mdp_ctx {int /*<<< orphan*/  id; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 133 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 132 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct mtk_mdp_ctx* fh_to_ctx (void*) ; 
 struct mtk_mdp_frame* mtk_mdp_ctx_get_frame (struct mtk_mdp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_mdp_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mtk_mdp_is_target_compose (int /*<<< orphan*/ ) ; 
 scalar_t__ mtk_mdp_is_target_crop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_mdp_m2m_g_selection(struct file *file, void *fh,
				       struct v4l2_selection *s)
{
	struct mtk_mdp_frame *frame;
	struct mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	bool valid = false;

	if (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		if (mtk_mdp_is_target_compose(s->target))
			valid = true;
	} else if (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		if (mtk_mdp_is_target_crop(s->target))
			valid = true;
	}
	if (!valid) {
		mtk_mdp_dbg(1, "[%d] invalid type:%d,%u", ctx->id, s->type,
			    s->target);
		return -EINVAL;
	}

	frame = mtk_mdp_ctx_get_frame(ctx, s->type);

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = frame->width;
		s->r.height = frame->height;
		return 0;

	case V4L2_SEL_TGT_COMPOSE:
	case V4L2_SEL_TGT_CROP:
		s->r.left = frame->crop.left;
		s->r.top = frame->crop.top;
		s->r.width = frame->crop.width;
		s->r.height = frame->crop.height;
		return 0;
	}

	return -EINVAL;
}