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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct s5p_jpeg_ctx {TYPE_1__* jpeg; int /*<<< orphan*/  subsampling; int /*<<< orphan*/  restart_interval; int /*<<< orphan*/  compr_quality; } ;
struct TYPE_2__ {int /*<<< orphan*/  slock; } ;

/* Variables and functions */
#define  V4L2_CID_JPEG_CHROMA_SUBSAMPLING 130 
#define  V4L2_CID_JPEG_COMPRESSION_QUALITY 129 
#define  V4L2_CID_JPEG_RESTART_INTERVAL 128 
 struct s5p_jpeg_ctx* ctrl_to_ctx (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s5p_jpeg_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct s5p_jpeg_ctx *ctx = ctrl_to_ctx(ctrl);
	unsigned long flags;

	spin_lock_irqsave(&ctx->jpeg->slock, flags);

	switch (ctrl->id) {
	case V4L2_CID_JPEG_COMPRESSION_QUALITY:
		ctx->compr_quality = ctrl->val;
		break;
	case V4L2_CID_JPEG_RESTART_INTERVAL:
		ctx->restart_interval = ctrl->val;
		break;
	case V4L2_CID_JPEG_CHROMA_SUBSAMPLING:
		ctx->subsampling = ctrl->val;
		break;
	}

	spin_unlock_irqrestore(&ctx->jpeg->slock, flags);
	return 0;
}