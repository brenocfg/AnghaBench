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
struct s5p_mfc_dev {int dummy; } ;
struct s5p_mfc_ctx {scalar_t__ codec_mode; int loop_filter_mpeg4; int slice_interface; int display_delay_enable; int display_delay; int inst_no; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int S5P_FIMV_CH_MASK ; 
 int S5P_FIMV_CH_SEQ_HEADER ; 
 int S5P_FIMV_CH_SHIFT ; 
 int S5P_FIMV_DDELAY_ENA_SHIFT ; 
 int S5P_FIMV_DDELAY_VAL_MASK ; 
 int S5P_FIMV_DDELAY_VAL_SHIFT ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_LF_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_DPB_CONF_CTRL ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_INST_ID ; 
 int S5P_FIMV_SLICE_INT_MASK ; 
 int S5P_FIMV_SLICE_INT_SHIFT ; 
 scalar_t__ S5P_MFC_CODEC_MPEG4_DEC ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_set_shared_buffer (struct s5p_mfc_ctx*) ; 

__attribute__((used)) static int s5p_mfc_init_decode_v5(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;

	s5p_mfc_set_shared_buffer(ctx);
	/* Setup loop filter, for decoding this is only valid for MPEG4 */
	if (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_DEC)
		mfc_write(dev, ctx->loop_filter_mpeg4, S5P_FIMV_ENC_LF_CTRL);
	else
		mfc_write(dev, 0, S5P_FIMV_ENC_LF_CTRL);
	mfc_write(dev, ((ctx->slice_interface & S5P_FIMV_SLICE_INT_MASK) <<
		S5P_FIMV_SLICE_INT_SHIFT) | (ctx->display_delay_enable <<
		S5P_FIMV_DDELAY_ENA_SHIFT) | ((ctx->display_delay &
		S5P_FIMV_DDELAY_VAL_MASK) << S5P_FIMV_DDELAY_VAL_SHIFT),
		S5P_FIMV_SI_CH0_DPB_CONF_CTRL);
	mfc_write(dev,
	((S5P_FIMV_CH_SEQ_HEADER & S5P_FIMV_CH_MASK) << S5P_FIMV_CH_SHIFT)
				| (ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);
	return 0;
}