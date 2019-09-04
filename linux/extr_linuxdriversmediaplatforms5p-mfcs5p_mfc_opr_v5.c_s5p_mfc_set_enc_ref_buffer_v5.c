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
struct TYPE_4__ {size_t dma; size_t size; } ;
struct TYPE_3__ {size_t dma; size_t size; } ;
struct s5p_mfc_ctx {unsigned int img_width; unsigned int img_height; int codec_mode; TYPE_2__ bank2; TYPE_1__ bank1; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  OFFSETA (size_t) ; 
 int /*<<< orphan*/  OFFSETB (size_t) ; 
 size_t S5P_FIMV_ENC_ACDCCOEF_SIZE ; 
 size_t S5P_FIMV_ENC_COLFLG_SIZE ; 
 size_t S5P_FIMV_ENC_INTRAMD_SIZE ; 
 size_t S5P_FIMV_ENC_INTRAPRED_SIZE ; 
 size_t S5P_FIMV_ENC_NBORINFO_SIZE ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_REF0_CHROMA_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_REF0_LUMA_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_ENC_REF2_LUMA_ADR ; 
 size_t S5P_FIMV_ENC_UPMV_SIZE ; 
 int /*<<< orphan*/  S5P_FIMV_H263_ACDC_COEF_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_H263_UP_MV_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_H264_COZERO_FLAG_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_H264_NBOR_INFO_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_H264_UP_INTRA_MD_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_H264_UP_INTRA_PRED_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_H264_UP_MV_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_MPEG4_ACDC_COEF_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_MPEG4_COZERO_FLAG_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_MPEG4_UP_MV_ADR ; 
 int /*<<< orphan*/  S5P_FIMV_NV12MT_HALIGN ; 
 int /*<<< orphan*/  S5P_FIMV_NV12MT_SALIGN ; 
 int /*<<< orphan*/  S5P_FIMV_NV12MT_VALIGN ; 
#define  S5P_MFC_CODEC_H263_ENC 130 
#define  S5P_MFC_CODEC_H264_ENC 129 
#define  S5P_MFC_CODEC_MPEG4_ENC 128 
 int /*<<< orphan*/  mfc_debug (int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  mfc_err (char*,int) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_enc_ref_buffer_v5(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	size_t buf_addr1, buf_addr2;
	size_t buf_size1, buf_size2;
	unsigned int enc_ref_y_size, enc_ref_c_size;
	unsigned int guard_width, guard_height;
	int i;

	buf_addr1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;
	buf_addr2 = ctx->bank2.dma;
	buf_size2 = ctx->bank2.size;
	enc_ref_y_size = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
		* ALIGN(ctx->img_height, S5P_FIMV_NV12MT_VALIGN);
	enc_ref_y_size = ALIGN(enc_ref_y_size, S5P_FIMV_NV12MT_SALIGN);
	if (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC) {
		enc_ref_c_size = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN)
			* ALIGN((ctx->img_height >> 1), S5P_FIMV_NV12MT_VALIGN);
		enc_ref_c_size = ALIGN(enc_ref_c_size, S5P_FIMV_NV12MT_SALIGN);
	} else {
		guard_width = ALIGN(ctx->img_width + 16,
						S5P_FIMV_NV12MT_HALIGN);
		guard_height = ALIGN((ctx->img_height >> 1) + 4,
						S5P_FIMV_NV12MT_VALIGN);
		enc_ref_c_size = ALIGN(guard_width * guard_height,
				       S5P_FIMV_NV12MT_SALIGN);
	}
	mfc_debug(2, "buf_size1: %zu, buf_size2: %zu\n", buf_size1, buf_size2);
	switch (ctx->codec_mode) {
	case S5P_MFC_CODEC_H264_ENC:
		for (i = 0; i < 2; i++) {
			mfc_write(dev, OFFSETA(buf_addr1),
				S5P_FIMV_ENC_REF0_LUMA_ADR + (4 * i));
			buf_addr1 += enc_ref_y_size;
			buf_size1 -= enc_ref_y_size;

			mfc_write(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF2_LUMA_ADR + (4 * i));
			buf_addr2 += enc_ref_y_size;
			buf_size2 -= enc_ref_y_size;
		}
		for (i = 0; i < 4; i++) {
			mfc_write(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF0_CHROMA_ADR + (4 * i));
			buf_addr2 += enc_ref_c_size;
			buf_size2 -= enc_ref_c_size;
		}
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_H264_UP_MV_ADR);
		buf_addr1 += S5P_FIMV_ENC_UPMV_SIZE;
		buf_size1 -= S5P_FIMV_ENC_UPMV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1),
					S5P_FIMV_H264_COZERO_FLAG_ADR);
		buf_addr1 += S5P_FIMV_ENC_COLFLG_SIZE;
		buf_size1 -= S5P_FIMV_ENC_COLFLG_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1),
					S5P_FIMV_H264_UP_INTRA_MD_ADR);
		buf_addr1 += S5P_FIMV_ENC_INTRAMD_SIZE;
		buf_size1 -= S5P_FIMV_ENC_INTRAMD_SIZE;
		mfc_write(dev, OFFSETB(buf_addr2),
					S5P_FIMV_H264_UP_INTRA_PRED_ADR);
		buf_addr2 += S5P_FIMV_ENC_INTRAPRED_SIZE;
		buf_size2 -= S5P_FIMV_ENC_INTRAPRED_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1),
					S5P_FIMV_H264_NBOR_INFO_ADR);
		buf_addr1 += S5P_FIMV_ENC_NBORINFO_SIZE;
		buf_size1 -= S5P_FIMV_ENC_NBORINFO_SIZE;
		mfc_debug(2, "buf_size1: %zu, buf_size2: %zu\n",
			buf_size1, buf_size2);
		break;
	case S5P_MFC_CODEC_MPEG4_ENC:
		for (i = 0; i < 2; i++) {
			mfc_write(dev, OFFSETA(buf_addr1),
				S5P_FIMV_ENC_REF0_LUMA_ADR + (4 * i));
			buf_addr1 += enc_ref_y_size;
			buf_size1 -= enc_ref_y_size;
			mfc_write(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF2_LUMA_ADR + (4 * i));
			buf_addr2 += enc_ref_y_size;
			buf_size2 -= enc_ref_y_size;
		}
		for (i = 0; i < 4; i++) {
			mfc_write(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF0_CHROMA_ADR + (4 * i));
			buf_addr2 += enc_ref_c_size;
			buf_size2 -= enc_ref_c_size;
		}
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_UP_MV_ADR);
		buf_addr1 += S5P_FIMV_ENC_UPMV_SIZE;
		buf_size1 -= S5P_FIMV_ENC_UPMV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1),
						S5P_FIMV_MPEG4_COZERO_FLAG_ADR);
		buf_addr1 += S5P_FIMV_ENC_COLFLG_SIZE;
		buf_size1 -= S5P_FIMV_ENC_COLFLG_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1),
						S5P_FIMV_MPEG4_ACDC_COEF_ADR);
		buf_addr1 += S5P_FIMV_ENC_ACDCCOEF_SIZE;
		buf_size1 -= S5P_FIMV_ENC_ACDCCOEF_SIZE;
		mfc_debug(2, "buf_size1: %zu, buf_size2: %zu\n",
			buf_size1, buf_size2);
		break;
	case S5P_MFC_CODEC_H263_ENC:
		for (i = 0; i < 2; i++) {
			mfc_write(dev, OFFSETA(buf_addr1),
				S5P_FIMV_ENC_REF0_LUMA_ADR + (4 * i));
			buf_addr1 += enc_ref_y_size;
			buf_size1 -= enc_ref_y_size;
			mfc_write(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF2_LUMA_ADR + (4 * i));
			buf_addr2 += enc_ref_y_size;
			buf_size2 -= enc_ref_y_size;
		}
		for (i = 0; i < 4; i++) {
			mfc_write(dev, OFFSETB(buf_addr2),
				S5P_FIMV_ENC_REF0_CHROMA_ADR + (4 * i));
			buf_addr2 += enc_ref_c_size;
			buf_size2 -= enc_ref_c_size;
		}
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_UP_MV_ADR);
		buf_addr1 += S5P_FIMV_ENC_UPMV_SIZE;
		buf_size1 -= S5P_FIMV_ENC_UPMV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_ACDC_COEF_ADR);
		buf_addr1 += S5P_FIMV_ENC_ACDCCOEF_SIZE;
		buf_size1 -= S5P_FIMV_ENC_ACDCCOEF_SIZE;
		mfc_debug(2, "buf_size1: %zu, buf_size2: %zu\n",
			buf_size1, buf_size2);
		break;
	default:
		mfc_err("Unknown codec set for encoding: %d\n",
			ctx->codec_mode);
		return -EINVAL;
	}
	return 0;
}