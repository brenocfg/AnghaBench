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
struct v4l2_ctrl_mpeg2_quantization {int dummy; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  cpu; } ;
struct TYPE_4__ {TYPE_1__ qtable; } ;
struct hantro_ctx {TYPE_2__ mpeg2_dec; } ;

/* Variables and functions */
 int /*<<< orphan*/  G1_REG_QTABLE_BASE ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION ; 
 struct v4l2_ctrl_mpeg2_quantization* hantro_get_ctrl (struct hantro_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hantro_mpeg2_dec_copy_qtable (int /*<<< orphan*/ ,struct v4l2_ctrl_mpeg2_quantization*) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hantro_g1_mpeg2_dec_set_quantization(struct hantro_dev *vpu,
				     struct hantro_ctx *ctx)
{
	struct v4l2_ctrl_mpeg2_quantization *quantization;

	quantization = hantro_get_ctrl(ctx,
				       V4L2_CID_MPEG_VIDEO_MPEG2_QUANTIZATION);
	hantro_mpeg2_dec_copy_qtable(ctx->mpeg2_dec.qtable.cpu,
				     quantization);
	vdpu_write_relaxed(vpu, ctx->mpeg2_dec.qtable.dma,
			   G1_REG_QTABLE_BASE);
}