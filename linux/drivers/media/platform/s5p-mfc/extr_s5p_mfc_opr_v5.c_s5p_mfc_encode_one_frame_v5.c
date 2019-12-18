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
struct s5p_mfc_dev {int dummy; } ;
struct s5p_mfc_ctx {scalar_t__ state; int inst_no; TYPE_1__* src_fmt; struct s5p_mfc_dev* dev; } ;
struct TYPE_2__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 scalar_t__ MFCINST_FINISHING ; 
 int S5P_FIMV_CH_FRAME_START ; 
 int S5P_FIMV_CH_LAST_FRAME ; 
 int S5P_FIMV_CH_MASK ; 
 int S5P_FIMV_CH_SHIFT ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_MAP_FOR_CUR ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_INST_ID ; 
 scalar_t__ V4L2_PIX_FMT_NV12M ; 
 scalar_t__ V4L2_PIX_FMT_NV12MT ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_set_shared_buffer (struct s5p_mfc_ctx*) ; 

__attribute__((used)) static int s5p_mfc_encode_one_frame_v5(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	int cmd;
	/* memory structure cur. frame */
	if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12M)
		mfc_write(dev, 0, S5P_FIMV_ENC_MAP_FOR_CUR);
	else if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_NV12MT)
		mfc_write(dev, 3, S5P_FIMV_ENC_MAP_FOR_CUR);
	s5p_mfc_set_shared_buffer(ctx);

	if (ctx->state == MFCINST_FINISHING)
		cmd = S5P_FIMV_CH_LAST_FRAME;
	else
		cmd = S5P_FIMV_CH_FRAME_START;
	mfc_write(dev, ((cmd & S5P_FIMV_CH_MASK) << S5P_FIMV_CH_SHIFT)
				| (ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);

	return 0;
}