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
struct s5p_mfc_ctx {int dec_dst_flag; int inst_no; int /*<<< orphan*/  dpb_flush_flag; struct s5p_mfc_dev* dev; } ;
typedef  enum s5p_mfc_decode_arg { ____Placeholder_s5p_mfc_decode_arg } s5p_mfc_decode_arg ;

/* Variables and functions */
#define  MFC_DEC_FRAME 130 
#define  MFC_DEC_LAST_FRAME 129 
#define  MFC_DEC_RES_CHANGE 128 
 int S5P_FIMV_CH_FRAME_START ; 
 int S5P_FIMV_CH_FRAME_START_REALLOC ; 
 int S5P_FIMV_CH_LAST_FRAME ; 
 int S5P_FIMV_CH_MASK ; 
 int S5P_FIMV_CH_SHIFT ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_INST_ID ; 
 int /*<<< orphan*/  S5P_FIMV_SI_CH0_RELEASE_BUF ; 
 int /*<<< orphan*/  mfc_debug (int,char*) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_set_flush (struct s5p_mfc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_set_shared_buffer (struct s5p_mfc_ctx*) ; 

__attribute__((used)) static int s5p_mfc_decode_one_frame_v5(struct s5p_mfc_ctx *ctx,
					enum s5p_mfc_decode_arg last_frame)
{
	struct s5p_mfc_dev *dev = ctx->dev;

	mfc_write(dev, ctx->dec_dst_flag, S5P_FIMV_SI_CH0_RELEASE_BUF);
	s5p_mfc_set_shared_buffer(ctx);
	s5p_mfc_set_flush(ctx, ctx->dpb_flush_flag);
	/* Issue different commands to instance basing on whether it
	 * is the last frame or not. */
	switch (last_frame) {
	case MFC_DEC_FRAME:
		mfc_write(dev, ((S5P_FIMV_CH_FRAME_START & S5P_FIMV_CH_MASK) <<
		S5P_FIMV_CH_SHIFT) | (ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);
		break;
	case MFC_DEC_LAST_FRAME:
		mfc_write(dev, ((S5P_FIMV_CH_LAST_FRAME & S5P_FIMV_CH_MASK) <<
		S5P_FIMV_CH_SHIFT) | (ctx->inst_no), S5P_FIMV_SI_CH0_INST_ID);
		break;
	case MFC_DEC_RES_CHANGE:
		mfc_write(dev, ((S5P_FIMV_CH_FRAME_START_REALLOC &
		S5P_FIMV_CH_MASK) << S5P_FIMV_CH_SHIFT) | (ctx->inst_no),
		S5P_FIMV_SI_CH0_INST_ID);
		break;
	}
	mfc_debug(2, "Decoding a usual frame\n");
	return 0;
}