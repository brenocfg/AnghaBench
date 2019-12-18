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
struct jpu_ctx {TYPE_1__* jpu; int /*<<< orphan*/  compr_quality; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ V4L2_CID_JPEG_COMPRESSION_QUALITY ; 
 struct jpu_ctx* ctrl_to_ctx (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int jpu_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct jpu_ctx *ctx = ctrl_to_ctx(ctrl);
	unsigned long flags;

	spin_lock_irqsave(&ctx->jpu->lock, flags);
	if (ctrl->id == V4L2_CID_JPEG_COMPRESSION_QUALITY)
		ctx->compr_quality = ctrl->val;
	spin_unlock_irqrestore(&ctx->jpu->lock, flags);

	return 0;
}