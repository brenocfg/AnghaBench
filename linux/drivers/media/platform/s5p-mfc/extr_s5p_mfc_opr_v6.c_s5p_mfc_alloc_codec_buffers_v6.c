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
struct s5p_mfc_dev {int dummy; } ;
struct TYPE_4__ {int size; int dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; } ;
struct s5p_mfc_ctx {scalar_t__ type; int mv_size; unsigned int tmv_buffer_size; int codec_mode; int luma_dpb_size; unsigned int chroma_dpb_size; unsigned int me_buffer_size; unsigned int scratch_buf_size; int mv_count; int pb_count; TYPE_2__ bank1; TYPE_1__ bank2; int /*<<< orphan*/  img_height; int /*<<< orphan*/  img_width; int /*<<< orphan*/  total_dpb_count; int /*<<< orphan*/  chroma_size; int /*<<< orphan*/  luma_size; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int) ; 
 int /*<<< orphan*/  BANK_L_CTX ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DEC_VP9_STATIC_BUFFER_SIZE ; 
 int EINVAL ; 
 unsigned int ENC_V100_H264_ME_SIZE (unsigned int,unsigned int) ; 
 unsigned int ENC_V100_HEVC_ME_SIZE (unsigned int,unsigned int) ; 
 unsigned int ENC_V100_MPEG4_ME_SIZE (unsigned int,unsigned int) ; 
 unsigned int ENC_V100_VP8_ME_SIZE (unsigned int,unsigned int) ; 
 scalar_t__ IS_MFCV10 (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  IS_MFCV7_PLUS (struct s5p_mfc_dev*) ; 
 scalar_t__ IS_MFCV8_PLUS (struct s5p_mfc_dev*) ; 
 unsigned int MB_HEIGHT (int /*<<< orphan*/ ) ; 
 unsigned int MB_WIDTH (int /*<<< orphan*/ ) ; 
 scalar_t__ MFCINST_DECODER ; 
 scalar_t__ MFCINST_ENCODER ; 
 int MFC_BANK1_ALIGN_ORDER ; 
 int S5P_FIMV_CHROMA_DPB_BUFFER_ALIGN_V6 ; 
 unsigned int S5P_FIMV_CHROMA_MB_TO_PIXEL_V6 ; 
 int S5P_FIMV_CODEC_HEVC_ENC ; 
 int S5P_FIMV_LUMA_DPB_BUFFER_ALIGN_V6 ; 
 unsigned int S5P_FIMV_LUMA_MB_TO_PIXEL_V6 ; 
 int S5P_FIMV_ME_BUFFER_ALIGN_V6 ; 
 unsigned int S5P_FIMV_ME_BUFFER_SIZE_V6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_ME_BUFFER_SIZE_V8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_NUM_TMV_BUFFERS_V6 ; 
 int S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6 ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_H263_DEC_V6 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_H264_DEC_V6 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_H264_DEC_V8 (unsigned int,unsigned int) ; 
 int S5P_FIMV_SCRATCH_BUF_SIZE_H264_ENC_V6 (unsigned int,unsigned int) ; 
 int S5P_FIMV_SCRATCH_BUF_SIZE_H264_ENC_V8 (unsigned int,unsigned int) ; 
 int S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_DEC_V6 (unsigned int,unsigned int) ; 
 int S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_DEC_V7 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_ENC_V6 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_VC1_DEC_V6 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_VP8_DEC_V6 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_VP8_DEC_V8 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_VP8_ENC_V7 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_SCRATCH_BUF_SIZE_VP8_ENC_V8 (unsigned int,unsigned int) ; 
 int S5P_FIMV_TMV_BUFFER_ALIGN_V6 ; 
 unsigned int S5P_FIMV_TMV_BUFFER_SIZE_V6 (unsigned int,unsigned int) ; 
 unsigned int S5P_FIMV_TMV_BUFFER_SIZE_V8 (unsigned int,unsigned int) ; 
#define  S5P_MFC_CODEC_H263_DEC 142 
#define  S5P_MFC_CODEC_H263_ENC 141 
#define  S5P_MFC_CODEC_H264_DEC 140 
#define  S5P_MFC_CODEC_H264_ENC 139 
#define  S5P_MFC_CODEC_H264_MVC_DEC 138 
#define  S5P_MFC_CODEC_HEVC_DEC 137 
#define  S5P_MFC_CODEC_HEVC_ENC 136 
#define  S5P_MFC_CODEC_MPEG2_DEC 135 
#define  S5P_MFC_CODEC_MPEG4_DEC 134 
#define  S5P_MFC_CODEC_MPEG4_ENC 133 
#define  S5P_MFC_CODEC_VC1RCV_DEC 132 
#define  S5P_MFC_CODEC_VC1_DEC 131 
#define  S5P_MFC_CODEC_VP8_DEC 130 
#define  S5P_MFC_CODEC_VP8_ENC 129 
#define  S5P_MFC_CODEC_VP9_DEC 128 
 unsigned int S5P_MFC_LCU_HEIGHT (int /*<<< orphan*/ ) ; 
 unsigned int S5P_MFC_LCU_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,...) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int s5p_mfc_alloc_generic_buf (struct s5p_mfc_dev*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int s5p_mfc_alloc_codec_buffers_v6(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned int mb_width, mb_height;
	unsigned int lcu_width = 0, lcu_height = 0;
	int ret;

	mb_width = MB_WIDTH(ctx->img_width);
	mb_height = MB_HEIGHT(ctx->img_height);

	if (ctx->type == MFCINST_DECODER) {
		mfc_debug(2, "Luma size:%d Chroma size:%d MV size:%d\n",
			  ctx->luma_size, ctx->chroma_size, ctx->mv_size);
		mfc_debug(2, "Totals bufs: %d\n", ctx->total_dpb_count);
	} else if (ctx->type == MFCINST_ENCODER) {
		if (IS_MFCV10(dev)) {
			ctx->tmv_buffer_size = 0;
		} else if (IS_MFCV8_PLUS(dev))
			ctx->tmv_buffer_size = S5P_FIMV_NUM_TMV_BUFFERS_V6 *
			ALIGN(S5P_FIMV_TMV_BUFFER_SIZE_V8(mb_width, mb_height),
			S5P_FIMV_TMV_BUFFER_ALIGN_V6);
		else
			ctx->tmv_buffer_size = S5P_FIMV_NUM_TMV_BUFFERS_V6 *
			ALIGN(S5P_FIMV_TMV_BUFFER_SIZE_V6(mb_width, mb_height),
			S5P_FIMV_TMV_BUFFER_ALIGN_V6);
		if (IS_MFCV10(dev)) {
			lcu_width = S5P_MFC_LCU_WIDTH(ctx->img_width);
			lcu_height = S5P_MFC_LCU_HEIGHT(ctx->img_height);
			if (ctx->codec_mode != S5P_FIMV_CODEC_HEVC_ENC) {
				ctx->luma_dpb_size =
					ALIGN((mb_width * 16), 64)
					* ALIGN((mb_height * 16), 32)
						+ 64;
				ctx->chroma_dpb_size =
					ALIGN((mb_width * 16), 64)
							* (mb_height * 8)
							+ 64;
			} else {
				ctx->luma_dpb_size =
					ALIGN((lcu_width * 32), 64)
					* ALIGN((lcu_height * 32), 32)
						+ 64;
				ctx->chroma_dpb_size =
					ALIGN((lcu_width * 32), 64)
							* (lcu_height * 16)
							+ 64;
			}
		} else {
			ctx->luma_dpb_size = ALIGN((mb_width * mb_height) *
					S5P_FIMV_LUMA_MB_TO_PIXEL_V6,
					S5P_FIMV_LUMA_DPB_BUFFER_ALIGN_V6);
			ctx->chroma_dpb_size = ALIGN((mb_width * mb_height) *
					S5P_FIMV_CHROMA_MB_TO_PIXEL_V6,
					S5P_FIMV_CHROMA_DPB_BUFFER_ALIGN_V6);
		}
		if (IS_MFCV8_PLUS(dev))
			ctx->me_buffer_size = ALIGN(S5P_FIMV_ME_BUFFER_SIZE_V8(
						ctx->img_width, ctx->img_height,
						mb_width, mb_height),
						S5P_FIMV_ME_BUFFER_ALIGN_V6);
		else
			ctx->me_buffer_size = ALIGN(S5P_FIMV_ME_BUFFER_SIZE_V6(
						ctx->img_width, ctx->img_height,
						mb_width, mb_height),
						S5P_FIMV_ME_BUFFER_ALIGN_V6);

		mfc_debug(2, "recon luma size: %zu chroma size: %zu\n",
			  ctx->luma_dpb_size, ctx->chroma_dpb_size);
	} else {
		return -EINVAL;
	}

	/* Codecs have different memory requirements */
	switch (ctx->codec_mode) {
	case S5P_MFC_CODEC_H264_DEC:
	case S5P_MFC_CODEC_H264_MVC_DEC:
		if (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		else if (IS_MFCV8_PLUS(dev))
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H264_DEC_V8(
					mb_width,
					mb_height);
		else
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H264_DEC_V6(
					mb_width,
					mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size =
			ctx->scratch_buf_size +
			(ctx->mv_count * ctx->mv_size);
		break;
	case S5P_MFC_CODEC_MPEG4_DEC:
		if (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		else if (IS_MFCV7_PLUS(dev)) {
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_DEC_V7(
						mb_width,
						mb_height);
		} else {
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_DEC_V6(
						mb_width,
						mb_height);
		}

		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size = ctx->scratch_buf_size;
		break;
	case S5P_MFC_CODEC_VC1RCV_DEC:
	case S5P_MFC_CODEC_VC1_DEC:
		if (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		else
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VC1_DEC_V6(
						mb_width,
						mb_height);

		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size = ctx->scratch_buf_size;
		break;
	case S5P_MFC_CODEC_MPEG2_DEC:
		ctx->bank1.size = 0;
		ctx->bank2.size = 0;
		break;
	case S5P_MFC_CODEC_H263_DEC:
		if (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		else
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H263_DEC_V6(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size = ctx->scratch_buf_size;
		break;
	case S5P_MFC_CODEC_VP8_DEC:
		if (IS_MFCV10(dev))
			mfc_debug(2, "Use min scratch buffer size\n");
		else if (IS_MFCV8_PLUS(dev))
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VP8_DEC_V8(
						mb_width,
						mb_height);
		else
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VP8_DEC_V6(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size = ctx->scratch_buf_size;
		break;
	case S5P_MFC_CODEC_HEVC_DEC:
		mfc_debug(2, "Use min scratch buffer size\n");
		ctx->bank1.size =
			ctx->scratch_buf_size +
			(ctx->mv_count * ctx->mv_size);
		break;
	case S5P_MFC_CODEC_VP9_DEC:
		mfc_debug(2, "Use min scratch buffer size\n");
		ctx->bank1.size =
			ctx->scratch_buf_size +
			DEC_VP9_STATIC_BUFFER_SIZE;
		break;
	case S5P_MFC_CODEC_H264_ENC:
		if (IS_MFCV10(dev)) {
			mfc_debug(2, "Use min scratch buffer size\n");
			ctx->me_buffer_size =
			ALIGN(ENC_V100_H264_ME_SIZE(mb_width, mb_height), 16);
		} else if (IS_MFCV8_PLUS(dev))
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H264_ENC_V8(
					mb_width,
					mb_height);
		else
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_H264_ENC_V6(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size =
			ctx->scratch_buf_size + ctx->tmv_buffer_size +
			(ctx->pb_count * (ctx->luma_dpb_size +
			ctx->chroma_dpb_size + ctx->me_buffer_size));
		ctx->bank2.size = 0;
		break;
	case S5P_MFC_CODEC_MPEG4_ENC:
	case S5P_MFC_CODEC_H263_ENC:
		if (IS_MFCV10(dev)) {
			mfc_debug(2, "Use min scratch buffer size\n");
			ctx->me_buffer_size =
				ALIGN(ENC_V100_MPEG4_ME_SIZE(mb_width,
							mb_height), 16);
		} else
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_MPEG4_ENC_V6(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size =
			ctx->scratch_buf_size + ctx->tmv_buffer_size +
			(ctx->pb_count * (ctx->luma_dpb_size +
			ctx->chroma_dpb_size + ctx->me_buffer_size));
		ctx->bank2.size = 0;
		break;
	case S5P_MFC_CODEC_VP8_ENC:
		if (IS_MFCV10(dev)) {
			mfc_debug(2, "Use min scratch buffer size\n");
			ctx->me_buffer_size =
				ALIGN(ENC_V100_VP8_ME_SIZE(mb_width, mb_height),
						16);
		} else if (IS_MFCV8_PLUS(dev))
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VP8_ENC_V8(
					mb_width,
					mb_height);
		else
			ctx->scratch_buf_size =
				S5P_FIMV_SCRATCH_BUF_SIZE_VP8_ENC_V7(
						mb_width,
						mb_height);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size,
				S5P_FIMV_SCRATCH_BUFFER_ALIGN_V6);
		ctx->bank1.size =
			ctx->scratch_buf_size + ctx->tmv_buffer_size +
			(ctx->pb_count * (ctx->luma_dpb_size +
			ctx->chroma_dpb_size + ctx->me_buffer_size));
		ctx->bank2.size = 0;
		break;
	case S5P_MFC_CODEC_HEVC_ENC:
		mfc_debug(2, "Use min scratch buffer size\n");
		ctx->me_buffer_size =
			ALIGN(ENC_V100_HEVC_ME_SIZE(lcu_width, lcu_height), 16);
		ctx->scratch_buf_size = ALIGN(ctx->scratch_buf_size, 256);
		ctx->bank1.size =
			ctx->scratch_buf_size + ctx->tmv_buffer_size +
			(ctx->pb_count * (ctx->luma_dpb_size +
			ctx->chroma_dpb_size + ctx->me_buffer_size));
		ctx->bank2.size = 0;
		break;
	default:
		break;
	}

	/* Allocate only if memory from bank 1 is necessary */
	if (ctx->bank1.size > 0) {
		ret = s5p_mfc_alloc_generic_buf(dev, BANK_L_CTX, &ctx->bank1);
		if (ret) {
			mfc_err("Failed to allocate Bank1 memory\n");
			return ret;
		}
		BUG_ON(ctx->bank1.dma & ((1 << MFC_BANK1_ALIGN_ORDER) - 1));
	}
	return 0;
}