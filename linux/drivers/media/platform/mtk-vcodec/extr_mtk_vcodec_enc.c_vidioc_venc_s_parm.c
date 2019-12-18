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
struct TYPE_6__ {int /*<<< orphan*/  numerator; int /*<<< orphan*/  denominator; } ;
struct TYPE_7__ {int /*<<< orphan*/  capability; TYPE_2__ timeperframe; } ;
struct TYPE_8__ {TYPE_3__ output; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_4__ parm; } ;
struct TYPE_5__ {int /*<<< orphan*/  framerate_denom; int /*<<< orphan*/  framerate_num; } ;
struct mtk_vcodec_ctx {int /*<<< orphan*/  param_change; TYPE_1__ enc_params; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MTK_ENCODE_PARAM_FRAMERATE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 struct mtk_vcodec_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int vidioc_venc_s_parm(struct file *file, void *priv,
			      struct v4l2_streamparm *a)
{
	struct mtk_vcodec_ctx *ctx = fh_to_ctx(priv);

	if (a->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		return -EINVAL;

	ctx->enc_params.framerate_num =
			a->parm.output.timeperframe.denominator;
	ctx->enc_params.framerate_denom =
			a->parm.output.timeperframe.numerator;
	ctx->param_change |= MTK_ENCODE_PARAM_FRAMERATE;

	a->parm.output.capability = V4L2_CAP_TIMEPERFRAME;

	return 0;
}