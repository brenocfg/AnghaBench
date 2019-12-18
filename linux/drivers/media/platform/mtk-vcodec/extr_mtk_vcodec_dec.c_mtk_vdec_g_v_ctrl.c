#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct mtk_vcodec_ctx {int /*<<< orphan*/  dpb_size; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTK_STATE_HEADER ; 
#define  V4L2_CID_MIN_BUFFERS_FOR_CAPTURE 128 
 struct mtk_vcodec_ctx* ctrl_to_ctx (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  mtk_v4l2_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mtk_vdec_g_v_ctrl(struct v4l2_ctrl *ctrl)
{
	struct mtk_vcodec_ctx *ctx = ctrl_to_ctx(ctrl);
	int ret = 0;

	switch (ctrl->id) {
	case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		if (ctx->state >= MTK_STATE_HEADER) {
			ctrl->val = ctx->dpb_size;
		} else {
			mtk_v4l2_debug(0, "Seqinfo not ready");
			ctrl->val = 0;
		}
		break;
	default:
		ret = -EINVAL;
	}
	return ret;
}