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
typedef  int u32 ;
struct tw5864_input {int reg_emu; int reg_interlacing; int reg_dsp; int reg_dsp_qp; int reg_dsp_ref_mvp_lambda; int reg_dsp_i4x4_weight; scalar_t__ frame_gop_seqno; int tail_nb_bits; int nr; int /*<<< orphan*/  h264_idr_pic_id; struct tw5864_dev* root; } ;
struct tw5864_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int TW5864_CIF_MAP_MD ; 
 int /*<<< orphan*/  TW5864_DSP ; 
 int /*<<< orphan*/  TW5864_DSP_CODEC ; 
 int /*<<< orphan*/  TW5864_DSP_ENC_ORG_PTR_REG ; 
 int TW5864_DSP_ENC_ORG_PTR_SHIFT ; 
 int /*<<< orphan*/  TW5864_DSP_ENC_REC ; 
 int /*<<< orphan*/  TW5864_DSP_I4x4_WEIGHT ; 
 int /*<<< orphan*/  TW5864_DSP_INTRA_MODE ; 
 int /*<<< orphan*/  TW5864_DSP_INTRA_MODE_16x16 ; 
 int /*<<< orphan*/  TW5864_DSP_INTRA_MODE_MASK ; 
 int /*<<< orphan*/  TW5864_DSP_INTRA_MODE_SHIFT ; 
 int /*<<< orphan*/  TW5864_DSP_QP ; 
 int /*<<< orphan*/  TW5864_DSP_REF_FRM ; 
 int /*<<< orphan*/  TW5864_DSP_REF_MVP_LAMBDA ; 
 int /*<<< orphan*/  TW5864_EMU ; 
 int /*<<< orphan*/  TW5864_ENC_BUF_PTR_REC1 ; 
 int TW5864_HD1_MAP_MD ; 
 int /*<<< orphan*/  TW5864_INTERLACING ; 
 int TW5864_INTRA_EN ; 
 int TW5864_ME_EN ; 
 int /*<<< orphan*/  TW5864_MOTION_SEARCH_ETC ; 
 int /*<<< orphan*/  TW5864_SLICE ; 
 int TW5864_START_NSLICE ; 
 int /*<<< orphan*/  TW5864_VLC ; 
 int TW5864_VLC_BIT_ALIGN_SHIFT ; 
 int TW5864_VLC_PCI_SEL ; 
 int /*<<< orphan*/  tw5864_prepare_frame_headers (struct tw5864_input*) ; 
 int tw_mask_shift_readl (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tw_mask_shift_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_setl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw_writel (int /*<<< orphan*/ ,int) ; 

void tw5864_request_encoded_frame(struct tw5864_input *input)
{
	struct tw5864_dev *dev = input->root;
	u32 enc_buf_id_new;

	tw_setl(TW5864_DSP_CODEC, TW5864_CIF_MAP_MD | TW5864_HD1_MAP_MD);
	tw_writel(TW5864_EMU, input->reg_emu);
	tw_writel(TW5864_INTERLACING, input->reg_interlacing);
	tw_writel(TW5864_DSP, input->reg_dsp);

	tw_writel(TW5864_DSP_QP, input->reg_dsp_qp);
	tw_writel(TW5864_DSP_REF_MVP_LAMBDA, input->reg_dsp_ref_mvp_lambda);
	tw_writel(TW5864_DSP_I4x4_WEIGHT, input->reg_dsp_i4x4_weight);
	tw_mask_shift_writel(TW5864_DSP_INTRA_MODE, TW5864_DSP_INTRA_MODE_MASK,
			     TW5864_DSP_INTRA_MODE_SHIFT,
			     TW5864_DSP_INTRA_MODE_16x16);

	if (input->frame_gop_seqno == 0) {
		/* Produce I-frame */
		tw_writel(TW5864_MOTION_SEARCH_ETC, TW5864_INTRA_EN);
		input->h264_idr_pic_id++;
		input->h264_idr_pic_id &= TW5864_DSP_REF_FRM;
	} else {
		/* Produce P-frame */
		tw_writel(TW5864_MOTION_SEARCH_ETC, TW5864_INTRA_EN |
			  TW5864_ME_EN | BIT(5) /* SRCH_OPT default */);
	}
	tw5864_prepare_frame_headers(input);
	tw_writel(TW5864_VLC,
		  TW5864_VLC_PCI_SEL |
		  ((input->tail_nb_bits + 24) << TW5864_VLC_BIT_ALIGN_SHIFT) |
		  input->reg_dsp_qp);

	enc_buf_id_new = tw_mask_shift_readl(TW5864_ENC_BUF_PTR_REC1, 0x3,
					     2 * input->nr);
	tw_writel(TW5864_DSP_ENC_ORG_PTR_REG,
		  enc_buf_id_new << TW5864_DSP_ENC_ORG_PTR_SHIFT);
	tw_writel(TW5864_DSP_ENC_REC,
		  enc_buf_id_new << 12 | ((enc_buf_id_new + 3) & 3));

	tw_writel(TW5864_SLICE, TW5864_START_NSLICE);
	tw_writel(TW5864_SLICE, 0);
}