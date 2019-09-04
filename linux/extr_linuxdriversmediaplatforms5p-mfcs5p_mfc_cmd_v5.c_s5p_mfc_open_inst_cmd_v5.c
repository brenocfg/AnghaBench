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
struct s5p_mfc_dev {int /*<<< orphan*/  curr_ctx; } ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ ofs; } ;
struct s5p_mfc_ctx {int codec_mode; int /*<<< orphan*/  state; TYPE_1__ ctx; int /*<<< orphan*/  num; struct s5p_mfc_dev* dev; } ;
struct s5p_mfc_cmd_args {scalar_t__* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFCINST_ERROR ; 
 scalar_t__ S5P_FIMV_CODEC_H263_DEC ; 
 scalar_t__ S5P_FIMV_CODEC_H263_ENC ; 
 scalar_t__ S5P_FIMV_CODEC_H264_DEC ; 
 scalar_t__ S5P_FIMV_CODEC_H264_ENC ; 
 scalar_t__ S5P_FIMV_CODEC_MPEG2_DEC ; 
 scalar_t__ S5P_FIMV_CODEC_MPEG4_DEC ; 
 scalar_t__ S5P_FIMV_CODEC_MPEG4_ENC ; 
 scalar_t__ S5P_FIMV_CODEC_NONE ; 
 scalar_t__ S5P_FIMV_CODEC_VC1RCV_DEC ; 
 scalar_t__ S5P_FIMV_CODEC_VC1_DEC ; 
 int /*<<< orphan*/  S5P_FIMV_H2R_CMD_OPEN_INSTANCE ; 
#define  S5P_MFC_CODEC_H263_DEC 136 
#define  S5P_MFC_CODEC_H263_ENC 135 
#define  S5P_MFC_CODEC_H264_DEC 134 
#define  S5P_MFC_CODEC_H264_ENC 133 
#define  S5P_MFC_CODEC_MPEG2_DEC 132 
#define  S5P_MFC_CODEC_MPEG4_DEC 131 
#define  S5P_MFC_CODEC_MPEG4_ENC 130 
#define  S5P_MFC_CODEC_VC1RCV_DEC 129 
#define  S5P_MFC_CODEC_VC1_DEC 128 
 int /*<<< orphan*/  memset (struct s5p_mfc_cmd_args*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,int) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int s5p_mfc_cmd_host2risc_v5 (struct s5p_mfc_dev*,int /*<<< orphan*/ ,struct s5p_mfc_cmd_args*) ; 

__attribute__((used)) static int s5p_mfc_open_inst_cmd_v5(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_cmd_args h2r_args;
	int ret;

	/* Preparing decoding - getting instance number */
	mfc_debug(2, "Getting instance number (codec: %d)\n", ctx->codec_mode);
	dev->curr_ctx = ctx->num;
	memset(&h2r_args, 0, sizeof(struct s5p_mfc_cmd_args));
	switch (ctx->codec_mode) {
	case S5P_MFC_CODEC_H264_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_H264_DEC;
		break;
	case S5P_MFC_CODEC_VC1_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_VC1_DEC;
		break;
	case S5P_MFC_CODEC_MPEG4_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_MPEG4_DEC;
		break;
	case S5P_MFC_CODEC_MPEG2_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_MPEG2_DEC;
		break;
	case S5P_MFC_CODEC_H263_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_H263_DEC;
		break;
	case S5P_MFC_CODEC_VC1RCV_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_VC1RCV_DEC;
		break;
	case S5P_MFC_CODEC_H264_ENC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_H264_ENC;
		break;
	case S5P_MFC_CODEC_MPEG4_ENC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_MPEG4_ENC;
		break;
	case S5P_MFC_CODEC_H263_ENC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_H263_ENC;
		break;
	default:
		h2r_args.arg[0] = S5P_FIMV_CODEC_NONE;
	}
	h2r_args.arg[1] = 0; /* no crc & no pixelcache */
	h2r_args.arg[2] = ctx->ctx.ofs;
	h2r_args.arg[3] = ctx->ctx.size;
	ret = s5p_mfc_cmd_host2risc_v5(dev, S5P_FIMV_H2R_CMD_OPEN_INSTANCE,
								&h2r_args);
	if (ret) {
		mfc_err("Failed to create a new instance\n");
		ctx->state = MFCINST_ERROR;
	}
	return ret;
}