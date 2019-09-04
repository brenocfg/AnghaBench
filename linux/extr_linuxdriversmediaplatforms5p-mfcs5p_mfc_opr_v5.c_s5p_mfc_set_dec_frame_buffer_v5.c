#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct s5p_mfc_dev {int dummy; } ;
struct TYPE_7__ {size_t dma; int size; } ;
struct TYPE_6__ {size_t dma; int size; } ;
struct s5p_mfc_ctx {unsigned int total_dpb_count; int codec_mode; unsigned int luma_size; unsigned int chroma_size; unsigned int mv_size; unsigned int inst_no; TYPE_5__* dst_bufs; TYPE_2__ bank2; TYPE_1__ bank1; struct s5p_mfc_dev* dev; } ;
struct TYPE_8__ {size_t luma; size_t chroma; } ;
struct TYPE_9__ {TYPE_3__ raw; } ;
struct TYPE_10__ {TYPE_4__ cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_CHROMA_DPB_SIZE ; 
 int /*<<< orphan*/  ALLOC_LUMA_DPB_SIZE ; 
 int /*<<< orphan*/  ALLOC_MV_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int OFFSETA (size_t) ; 
 unsigned int OFFSETB (size_t) ; 
 unsigned int S5P_FIMV_CH_INIT_BUFS ; 
 unsigned int S5P_FIMV_CH_MASK ; 
 unsigned int S5P_FIMV_CH_SHIFT ; 
 scalar_t__ S5P_FIMV_DEC_CHROMA_ADR ; 
 scalar_t__ S5P_FIMV_DEC_LUMA_ADR ; 
 size_t S5P_FIMV_DEC_NB_DCAC_SIZE ; 
 size_t S5P_FIMV_DEC_NB_IP_SIZE ; 
 size_t S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE ; 
 size_t S5P_FIMV_DEC_STX_PARSER_SIZE ; 
 size_t S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE ; 
 size_t S5P_FIMV_DEC_UPNB_MV_SIZE ; 
 size_t S5P_FIMV_DEC_VC1_BITPLANE_SIZE ; 
 size_t S5P_FIMV_DEC_VERT_NB_MV_SIZE ; 
 unsigned int S5P_FIMV_DPB_COUNT_MASK ; 
 scalar_t__ S5P_FIMV_H263_NB_DCAC_ADR ; 
 scalar_t__ S5P_FIMV_H263_OT_LINE_ADR ; 
 scalar_t__ S5P_FIMV_H263_SA_MV_ADR ; 
 scalar_t__ S5P_FIMV_H263_UP_NB_MV_ADR ; 
 scalar_t__ S5P_FIMV_H264_MV_ADR ; 
 scalar_t__ S5P_FIMV_H264_NB_IP_ADR ; 
 scalar_t__ S5P_FIMV_H264_VERT_NB_MV_ADR ; 
 scalar_t__ S5P_FIMV_MPEG4_NB_DCAC_ADR ; 
 scalar_t__ S5P_FIMV_MPEG4_OT_LINE_ADR ; 
 scalar_t__ S5P_FIMV_MPEG4_SA_MV_ADR ; 
 scalar_t__ S5P_FIMV_MPEG4_SP_ADR ; 
 scalar_t__ S5P_FIMV_MPEG4_UP_NB_MV_ADR ; 
 scalar_t__ S5P_FIMV_SI_CH0_DPB_CONF_CTRL ; 
 scalar_t__ S5P_FIMV_SI_CH0_INST_ID ; 
 scalar_t__ S5P_FIMV_VC1_BITPLANE1_ADR ; 
 scalar_t__ S5P_FIMV_VC1_BITPLANE2_ADR ; 
 scalar_t__ S5P_FIMV_VC1_BITPLANE3_ADR ; 
 scalar_t__ S5P_FIMV_VC1_NB_DCAC_ADR ; 
 scalar_t__ S5P_FIMV_VC1_OT_LINE_ADR ; 
 scalar_t__ S5P_FIMV_VC1_SA_MV_ADR ; 
 scalar_t__ S5P_FIMV_VC1_UP_NB_MV_ADR ; 
#define  S5P_MFC_CODEC_H263_DEC 133 
#define  S5P_MFC_CODEC_H264_DEC 132 
#define  S5P_MFC_CODEC_MPEG2_DEC 131 
#define  S5P_MFC_CODEC_MPEG4_DEC 130 
#define  S5P_MFC_CODEC_VC1RCV_DEC 129 
#define  S5P_MFC_CODEC_VC1_DEC 128 
 int /*<<< orphan*/  mfc_debug (int,char*,...) ; 
 int /*<<< orphan*/  mfc_err (char*,int) ; 
 unsigned int mfc_read (struct s5p_mfc_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mfc_write (struct s5p_mfc_dev*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  s5p_mfc_set_shared_buffer (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_write_info_v5 (struct s5p_mfc_ctx*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5p_mfc_set_dec_frame_buffer_v5(struct s5p_mfc_ctx *ctx)
{
	unsigned int frame_size_lu, i;
	unsigned int frame_size_ch, frame_size_mv;
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned int dpb;
	size_t buf_addr1, buf_addr2;
	int buf_size1, buf_size2;

	buf_addr1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;
	buf_addr2 = ctx->bank2.dma;
	buf_size2 = ctx->bank2.size;
	dpb = mfc_read(dev, S5P_FIMV_SI_CH0_DPB_CONF_CTRL) &
						~S5P_FIMV_DPB_COUNT_MASK;
	mfc_write(dev, ctx->total_dpb_count | dpb,
						S5P_FIMV_SI_CH0_DPB_CONF_CTRL);
	s5p_mfc_set_shared_buffer(ctx);
	switch (ctx->codec_mode) {
	case S5P_MFC_CODEC_H264_DEC:
		mfc_write(dev, OFFSETA(buf_addr1),
						S5P_FIMV_H264_VERT_NB_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_VERT_NB_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_VERT_NB_MV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_H264_NB_IP_ADR);
		buf_addr1 += S5P_FIMV_DEC_NB_IP_SIZE;
		buf_size1 -= S5P_FIMV_DEC_NB_IP_SIZE;
		break;
	case S5P_MFC_CODEC_MPEG4_DEC:
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_NB_DCAC_ADR);
		buf_addr1 += S5P_FIMV_DEC_NB_DCAC_SIZE;
		buf_size1 -= S5P_FIMV_DEC_NB_DCAC_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_UP_NB_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_UPNB_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_UPNB_MV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_SA_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_SP_ADR);
		buf_addr1 += S5P_FIMV_DEC_STX_PARSER_SIZE;
		buf_size1 -= S5P_FIMV_DEC_STX_PARSER_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_MPEG4_OT_LINE_ADR);
		buf_addr1 += S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		buf_size1 -= S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		break;
	case S5P_MFC_CODEC_H263_DEC:
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_OT_LINE_ADR);
		buf_addr1 += S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		buf_size1 -= S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_UP_NB_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_UPNB_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_UPNB_MV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_SA_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_H263_NB_DCAC_ADR);
		buf_addr1 += S5P_FIMV_DEC_NB_DCAC_SIZE;
		buf_size1 -= S5P_FIMV_DEC_NB_DCAC_SIZE;
		break;
	case S5P_MFC_CODEC_VC1_DEC:
	case S5P_MFC_CODEC_VC1RCV_DEC:
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_NB_DCAC_ADR);
		buf_addr1 += S5P_FIMV_DEC_NB_DCAC_SIZE;
		buf_size1 -= S5P_FIMV_DEC_NB_DCAC_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_OT_LINE_ADR);
		buf_addr1 += S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		buf_size1 -= S5P_FIMV_DEC_OVERLAP_TRANSFORM_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_UP_NB_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_UPNB_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_UPNB_MV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_SA_MV_ADR);
		buf_addr1 += S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		buf_size1 -= S5P_FIMV_DEC_SUB_ANCHOR_MV_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_BITPLANE3_ADR);
		buf_addr1 += S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		buf_size1 -= S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_BITPLANE2_ADR);
		buf_addr1 += S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		buf_size1 -= S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		mfc_write(dev, OFFSETA(buf_addr1), S5P_FIMV_VC1_BITPLANE1_ADR);
		buf_addr1 += S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		buf_size1 -= S5P_FIMV_DEC_VC1_BITPLANE_SIZE;
		break;
	case S5P_MFC_CODEC_MPEG2_DEC:
		break;
	default:
		mfc_err("Unknown codec for decoding (%x)\n",
			ctx->codec_mode);
		return -EINVAL;
	}
	frame_size_lu = ctx->luma_size;
	frame_size_ch = ctx->chroma_size;
	frame_size_mv = ctx->mv_size;
	mfc_debug(2, "Frm size: %d ch: %d mv: %d\n", frame_size_lu, frame_size_ch,
								frame_size_mv);
	for (i = 0; i < ctx->total_dpb_count; i++) {
		/* Bank2 */
		mfc_debug(2, "Luma %d: %zx\n", i,
					ctx->dst_bufs[i].cookie.raw.luma);
		mfc_write(dev, OFFSETB(ctx->dst_bufs[i].cookie.raw.luma),
						S5P_FIMV_DEC_LUMA_ADR + i * 4);
		mfc_debug(2, "\tChroma %d: %zx\n", i,
					ctx->dst_bufs[i].cookie.raw.chroma);
		mfc_write(dev, OFFSETA(ctx->dst_bufs[i].cookie.raw.chroma),
					       S5P_FIMV_DEC_CHROMA_ADR + i * 4);
		if (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC) {
			mfc_debug(2, "\tBuf2: %zx, size: %d\n",
							buf_addr2, buf_size2);
			mfc_write(dev, OFFSETB(buf_addr2),
						S5P_FIMV_H264_MV_ADR + i * 4);
			buf_addr2 += frame_size_mv;
			buf_size2 -= frame_size_mv;
		}
	}
	mfc_debug(2, "Buf1: %zu, buf_size1: %d\n", buf_addr1, buf_size1);
	mfc_debug(2, "Buf 1/2 size after: %d/%d (frames %d)\n",
			buf_size1,  buf_size2, ctx->total_dpb_count);
	if (buf_size1 < 0 || buf_size2 < 0) {
		mfc_debug(2, "Not enough memory has been allocated\n");
		return -ENOMEM;
	}
	s5p_mfc_write_info_v5(ctx, frame_size_lu, ALLOC_LUMA_DPB_SIZE);
	s5p_mfc_write_info_v5(ctx, frame_size_ch, ALLOC_CHROMA_DPB_SIZE);
	if (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC)
		s5p_mfc_write_info_v5(ctx, frame_size_mv, ALLOC_MV_SIZE);
	mfc_write(dev, ((S5P_FIMV_CH_INIT_BUFS & S5P_FIMV_CH_MASK)
					<< S5P_FIMV_CH_SHIFT) | (ctx->inst_no),
						S5P_FIMV_SI_CH0_INST_ID);
	return 0;
}