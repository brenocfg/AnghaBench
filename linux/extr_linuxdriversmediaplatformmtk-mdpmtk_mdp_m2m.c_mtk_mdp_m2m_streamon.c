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
struct mtk_mdp_ctx {int /*<<< orphan*/  m2m_ctx; TYPE_2__* mdp_dev; int /*<<< orphan*/  vpu; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTK_MDP_DST_FMT ; 
 int /*<<< orphan*/  MTK_MDP_SRC_FMT ; 
 int /*<<< orphan*/  MTK_MDP_VPU_INIT ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct mtk_mdp_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  mtk_mdp_ctx_state_is_set (struct mtk_mdp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_mdp_ctx_state_lock_set (struct mtk_mdp_ctx*,int /*<<< orphan*/ ) ; 
 int mtk_mdp_vpu_init (int /*<<< orphan*/ *) ; 
 int v4l2_m2m_streamon (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtk_mdp_m2m_streamon(struct file *file, void *fh,
				enum v4l2_buf_type type)
{
	struct mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	int ret;

	/* The source and target color format need to be set */
	if (V4L2_TYPE_IS_OUTPUT(type)) {
		if (!mtk_mdp_ctx_state_is_set(ctx, MTK_MDP_SRC_FMT))
			return -EINVAL;
	} else if (!mtk_mdp_ctx_state_is_set(ctx, MTK_MDP_DST_FMT)) {
		return -EINVAL;
	}

	if (!mtk_mdp_ctx_state_is_set(ctx, MTK_MDP_VPU_INIT)) {
		ret = mtk_mdp_vpu_init(&ctx->vpu);
		if (ret < 0) {
			dev_err(&ctx->mdp_dev->pdev->dev,
				"vpu init failed %d\n",
				ret);
			return -EINVAL;
		}
		mtk_mdp_ctx_state_lock_set(ctx, MTK_MDP_VPU_INIT);
	}

	return v4l2_m2m_streamon(file, ctx->m2m_ctx, type);
}