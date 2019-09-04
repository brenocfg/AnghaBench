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
struct v4l2_ctrl {scalar_t__ id; int /*<<< orphan*/  val; } ;
struct s5p_jpeg_ctx {TYPE_1__* jpeg; } ;
struct TYPE_2__ {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 scalar_t__ V4L2_CID_JPEG_CHROMA_SUBSAMPLING ; 
 struct s5p_jpeg_ctx* ctrl_to_ctx (struct v4l2_ctrl*) ; 
 int s5p_jpeg_adjust_subs_ctrl (struct s5p_jpeg_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s5p_jpeg_try_ctrl(struct v4l2_ctrl *ctrl)
{
	struct s5p_jpeg_ctx *ctx = ctrl_to_ctx(ctrl);
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&ctx->jpeg->slock, flags);

	if (ctrl->id == V4L2_CID_JPEG_CHROMA_SUBSAMPLING)
		ret = s5p_jpeg_adjust_subs_ctrl(ctx, &ctrl->val);

	spin_unlock_irqrestore(&ctx->jpeg->slock, flags);
	return ret;
}