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
typedef  int u32 ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct hantro_jpeg_ctx {int /*<<< orphan*/  quality; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  buffer; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct hantro_ctx {TYPE_2__ src_fmt; int /*<<< orphan*/  jpeg_quality; TYPE_1__ dst_fmt; struct hantro_dev* dev; } ;
typedef  int /*<<< orphan*/  jpeg_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  H1_REG_AXI_CTRL ; 
 int H1_REG_AXI_CTRL_BURST_LEN (int) ; 
 int H1_REG_AXI_CTRL_INPUT_SWAP16 ; 
 int H1_REG_AXI_CTRL_INPUT_SWAP32 ; 
 int H1_REG_AXI_CTRL_INPUT_SWAP8 ; 
 int H1_REG_AXI_CTRL_OUTPUT_SWAP16 ; 
 int H1_REG_AXI_CTRL_OUTPUT_SWAP32 ; 
 int H1_REG_AXI_CTRL_OUTPUT_SWAP8 ; 
 int /*<<< orphan*/  H1_REG_ENC_CTRL ; 
 int H1_REG_ENC_CTRL_ENC_MODE_JPEG ; 
 int H1_REG_ENC_CTRL_EN_BIT ; 
 int H1_REG_ENC_CTRL_HEIGHT (int /*<<< orphan*/ ) ; 
 int H1_REG_ENC_CTRL_WIDTH (int /*<<< orphan*/ ) ; 
 int H1_REG_ENC_PIC_INTRA ; 
 int /*<<< orphan*/  JPEG_MB_HEIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JPEG_MB_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hantro_finish_run (struct hantro_ctx*) ; 
 struct vb2_v4l2_buffer* hantro_get_dst_buf (struct hantro_ctx*) ; 
 struct vb2_v4l2_buffer* hantro_get_src_buf (struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_h1_jpeg_enc_set_buffers (struct hantro_dev*,struct hantro_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hantro_h1_jpeg_enc_set_qtable (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hantro_h1_set_src_img_ctrl (struct hantro_dev*,struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_jpeg_get_qtable (struct hantro_jpeg_ctx*,int) ; 
 int /*<<< orphan*/  hantro_jpeg_header_assemble (struct hantro_jpeg_ctx*) ; 
 int /*<<< orphan*/  hantro_prepare_run (struct hantro_ctx*) ; 
 int /*<<< orphan*/  memset (struct hantro_jpeg_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vepu_write (struct hantro_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vepu_write_relaxed (struct hantro_dev*,int,int /*<<< orphan*/ ) ; 

void hantro_h1_jpeg_enc_run(struct hantro_ctx *ctx)
{
	struct hantro_dev *vpu = ctx->dev;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	struct hantro_jpeg_ctx jpeg_ctx;
	u32 reg;

	src_buf = hantro_get_src_buf(ctx);
	dst_buf = hantro_get_dst_buf(ctx);

	hantro_prepare_run(ctx);

	memset(&jpeg_ctx, 0, sizeof(jpeg_ctx));
	jpeg_ctx.buffer = vb2_plane_vaddr(&dst_buf->vb2_buf, 0);
	jpeg_ctx.width = ctx->dst_fmt.width;
	jpeg_ctx.height = ctx->dst_fmt.height;
	jpeg_ctx.quality = ctx->jpeg_quality;
	hantro_jpeg_header_assemble(&jpeg_ctx);

	/* Switch to JPEG encoder mode before writing registers */
	vepu_write_relaxed(vpu, H1_REG_ENC_CTRL_ENC_MODE_JPEG,
			   H1_REG_ENC_CTRL);

	hantro_h1_set_src_img_ctrl(vpu, ctx);
	hantro_h1_jpeg_enc_set_buffers(vpu, ctx, &src_buf->vb2_buf);
	hantro_h1_jpeg_enc_set_qtable(vpu,
				      hantro_jpeg_get_qtable(&jpeg_ctx, 0),
				      hantro_jpeg_get_qtable(&jpeg_ctx, 1));

	reg = H1_REG_AXI_CTRL_OUTPUT_SWAP16
		| H1_REG_AXI_CTRL_INPUT_SWAP16
		| H1_REG_AXI_CTRL_BURST_LEN(16)
		| H1_REG_AXI_CTRL_OUTPUT_SWAP32
		| H1_REG_AXI_CTRL_INPUT_SWAP32
		| H1_REG_AXI_CTRL_OUTPUT_SWAP8
		| H1_REG_AXI_CTRL_INPUT_SWAP8;
	/* Make sure that all registers are written at this point. */
	vepu_write(vpu, reg, H1_REG_AXI_CTRL);

	reg = H1_REG_ENC_CTRL_WIDTH(JPEG_MB_WIDTH(ctx->src_fmt.width))
		| H1_REG_ENC_CTRL_HEIGHT(JPEG_MB_HEIGHT(ctx->src_fmt.height))
		| H1_REG_ENC_CTRL_ENC_MODE_JPEG
		| H1_REG_ENC_PIC_INTRA
		| H1_REG_ENC_CTRL_EN_BIT;

	hantro_finish_run(ctx);

	vepu_write(vpu, reg, H1_REG_ENC_CTRL);
}