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
struct s5p_jpeg_ctx {struct s5p_jpeg* jpeg; } ;
struct s5p_jpeg {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
#define  V4L2_CID_JPEG_CHROMA_SUBSAMPLING 128 
 struct s5p_jpeg_ctx* ctrl_to_ctx (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  s5p_jpeg_to_user_subsampling (struct s5p_jpeg_ctx*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s5p_jpeg_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct s5p_jpeg_ctx *ctx = ctrl_to_ctx(ctrl);
	struct s5p_jpeg *jpeg = ctx->jpeg;
	unsigned long flags;

	switch (ctrl->id) {
	case V4L2_CID_JPEG_CHROMA_SUBSAMPLING:
		spin_lock_irqsave(&jpeg->slock, flags);
		ctrl->val = s5p_jpeg_to_user_subsampling(ctx);
		spin_unlock_irqrestore(&jpeg->slock, flags);
		break;
	}

	return 0;
}