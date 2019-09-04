#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct s5p_mfc_dev {TYPE_2__* variant; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  virt; } ;
struct s5p_mfc_ctx {int codec_mode; TYPE_3__ ctx; struct s5p_mfc_dev* dev; } ;
struct s5p_mfc_buf_size_v6 {int /*<<< orphan*/  other_enc_ctx; int /*<<< orphan*/  hevc_enc_ctx; int /*<<< orphan*/  h264_enc_ctx; int /*<<< orphan*/  other_dec_ctx; int /*<<< orphan*/  h264_dec_ctx; } ;
struct TYPE_5__ {TYPE_1__* buf_size; } ;
struct TYPE_4__ {struct s5p_mfc_buf_size_v6* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_L_CTX ; 
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
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*,...) ; 
 int s5p_mfc_alloc_priv_buf (struct s5p_mfc_dev*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int s5p_mfc_alloc_instance_buffer_v6(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_buf_size_v6 *buf_size = dev->variant->buf_size->priv;
	int ret;

	mfc_debug_enter();

	switch (ctx->codec_mode) {
	case S5P_MFC_CODEC_H264_DEC:
	case S5P_MFC_CODEC_H264_MVC_DEC:
	case S5P_MFC_CODEC_HEVC_DEC:
		ctx->ctx.size = buf_size->h264_dec_ctx;
		break;
	case S5P_MFC_CODEC_MPEG4_DEC:
	case S5P_MFC_CODEC_H263_DEC:
	case S5P_MFC_CODEC_VC1RCV_DEC:
	case S5P_MFC_CODEC_VC1_DEC:
	case S5P_MFC_CODEC_MPEG2_DEC:
	case S5P_MFC_CODEC_VP8_DEC:
	case S5P_MFC_CODEC_VP9_DEC:
		ctx->ctx.size = buf_size->other_dec_ctx;
		break;
	case S5P_MFC_CODEC_H264_ENC:
		ctx->ctx.size = buf_size->h264_enc_ctx;
		break;
	case S5P_MFC_CODEC_HEVC_ENC:
		ctx->ctx.size = buf_size->hevc_enc_ctx;
		break;
	case S5P_MFC_CODEC_MPEG4_ENC:
	case S5P_MFC_CODEC_H263_ENC:
	case S5P_MFC_CODEC_VP8_ENC:
		ctx->ctx.size = buf_size->other_enc_ctx;
		break;
	default:
		ctx->ctx.size = 0;
		mfc_err("Codec type(%d) should be checked!\n", ctx->codec_mode);
		break;
	}

	ret = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &ctx->ctx);
	if (ret) {
		mfc_err("Failed to allocate instance buffer\n");
		return ret;
	}

	memset(ctx->ctx.virt, 0, ctx->ctx.size);
	wmb();

	mfc_debug_leave();

	return 0;
}