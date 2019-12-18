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
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  value; int /*<<< orphan*/  range; } ;
struct TYPE_9__ {scalar_t__ level; } ;
struct v4l2_ctrl_vp8_frame_header {int flags; int version; TYPE_5__ coder_state; TYPE_4__ lf_header; } ;
struct hantro_dev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; scalar_t__ cpu; } ;
struct TYPE_8__ {TYPE_2__ segment_map; } ;
struct TYPE_6__ {size_t height; size_t width; } ;
struct hantro_ctx {TYPE_3__ vp8_dec; TYPE_1__ dst_fmt; struct hantro_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  G1_REG_CONFIG ; 
 int G1_REG_CONFIG_DEC_CLK_GATE_E ; 
 int G1_REG_CONFIG_DEC_INSWAP32_E ; 
 int G1_REG_CONFIG_DEC_IN_ENDIAN ; 
 int G1_REG_CONFIG_DEC_MAX_BURST (int) ; 
 int G1_REG_CONFIG_DEC_OUTSWAP32_E ; 
 int G1_REG_CONFIG_DEC_OUT_ENDIAN ; 
 int G1_REG_CONFIG_DEC_STRENDIAN_E ; 
 int G1_REG_CONFIG_DEC_STRSWAP32_E ; 
 int G1_REG_CONFIG_DEC_TIMEOUT_E ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL0 ; 
 int G1_REG_DEC_CTRL0_DEC_MODE (int) ; 
 int G1_REG_DEC_CTRL0_FILTERING_DIS ; 
 int G1_REG_DEC_CTRL0_PIC_INTER_E ; 
 int G1_REG_DEC_CTRL0_SKIP_MODE ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL1 ; 
 int G1_REG_DEC_CTRL1_PIC_MB_HEIGHT_P (int) ; 
 int G1_REG_DEC_CTRL1_PIC_MB_H_EXT (int) ; 
 int G1_REG_DEC_CTRL1_PIC_MB_WIDTH (int) ; 
 int G1_REG_DEC_CTRL1_PIC_MB_W_EXT (int) ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL2 ; 
 int G1_REG_DEC_CTRL2_BOOLEAN_RANGE (int /*<<< orphan*/ ) ; 
 int G1_REG_DEC_CTRL2_BOOLEAN_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G1_REG_DEC_CTRL4 ; 
 int G1_REG_DEC_CTRL4_BILIN_MC_E ; 
 int G1_REG_DEC_CTRL4_VC1_HEIGHT_EXT ; 
 int /*<<< orphan*/  G1_REG_INTERRUPT ; 
 int /*<<< orphan*/  G1_REG_INTERRUPT_DEC_E ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_VP8_FRAME_HEADER ; 
 int V4L2_VP8_FRAME_HEADER_FLAG_MB_NO_SKIP_COEFF ; 
 scalar_t__ VP8_FRAME_IS_KEY_FRAME (struct v4l2_ctrl_vp8_frame_header const*) ; 
 int VP8_MB_HEIGHT (size_t) ; 
 int VP8_MB_WIDTH (size_t) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cfg_buffers (struct hantro_ctx*,struct v4l2_ctrl_vp8_frame_header const*) ; 
 int /*<<< orphan*/  cfg_lf (struct hantro_ctx*,struct v4l2_ctrl_vp8_frame_header const*) ; 
 int /*<<< orphan*/  cfg_parts (struct hantro_ctx*,struct v4l2_ctrl_vp8_frame_header const*) ; 
 int /*<<< orphan*/  cfg_qp (struct hantro_ctx*,struct v4l2_ctrl_vp8_frame_header const*) ; 
 int /*<<< orphan*/  cfg_ref (struct hantro_ctx*,struct v4l2_ctrl_vp8_frame_header const*) ; 
 int /*<<< orphan*/  cfg_tap (struct hantro_ctx*,struct v4l2_ctrl_vp8_frame_header const*) ; 
 int /*<<< orphan*/  hantro_finish_run (struct hantro_ctx*) ; 
 struct v4l2_ctrl_vp8_frame_header* hantro_get_ctrl (struct hantro_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hantro_prepare_run (struct hantro_ctx*) ; 
 int /*<<< orphan*/  hantro_vp8_prob_update (struct hantro_ctx*,struct v4l2_ctrl_vp8_frame_header const*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,int,int /*<<< orphan*/ ) ; 

void hantro_g1_vp8_dec_run(struct hantro_ctx *ctx)
{
	const struct v4l2_ctrl_vp8_frame_header *hdr;
	struct hantro_dev *vpu = ctx->dev;
	size_t height = ctx->dst_fmt.height;
	size_t width = ctx->dst_fmt.width;
	u32 mb_width, mb_height;
	u32 reg;

	hantro_prepare_run(ctx);

	hdr = hantro_get_ctrl(ctx, V4L2_CID_MPEG_VIDEO_VP8_FRAME_HEADER);
	if (WARN_ON(!hdr))
		return;

	/* Reset segment_map buffer in keyframe */
	if (VP8_FRAME_IS_KEY_FRAME(hdr) && ctx->vp8_dec.segment_map.cpu)
		memset(ctx->vp8_dec.segment_map.cpu, 0,
		       ctx->vp8_dec.segment_map.size);

	hantro_vp8_prob_update(ctx, hdr);

	reg = G1_REG_CONFIG_DEC_TIMEOUT_E |
	      G1_REG_CONFIG_DEC_STRENDIAN_E |
	      G1_REG_CONFIG_DEC_INSWAP32_E |
	      G1_REG_CONFIG_DEC_STRSWAP32_E |
	      G1_REG_CONFIG_DEC_OUTSWAP32_E |
	      G1_REG_CONFIG_DEC_CLK_GATE_E |
	      G1_REG_CONFIG_DEC_IN_ENDIAN |
	      G1_REG_CONFIG_DEC_OUT_ENDIAN |
	      G1_REG_CONFIG_DEC_MAX_BURST(16);
	vdpu_write_relaxed(vpu, reg, G1_REG_CONFIG);

	reg = G1_REG_DEC_CTRL0_DEC_MODE(10);
	if (!VP8_FRAME_IS_KEY_FRAME(hdr))
		reg |= G1_REG_DEC_CTRL0_PIC_INTER_E;
	if (!(hdr->flags & V4L2_VP8_FRAME_HEADER_FLAG_MB_NO_SKIP_COEFF))
		reg |= G1_REG_DEC_CTRL0_SKIP_MODE;
	if (hdr->lf_header.level == 0)
		reg |= G1_REG_DEC_CTRL0_FILTERING_DIS;
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL0);

	/* Frame dimensions */
	mb_width = VP8_MB_WIDTH(width);
	mb_height = VP8_MB_HEIGHT(height);
	reg = G1_REG_DEC_CTRL1_PIC_MB_WIDTH(mb_width) |
	      G1_REG_DEC_CTRL1_PIC_MB_HEIGHT_P(mb_height) |
	      G1_REG_DEC_CTRL1_PIC_MB_W_EXT(mb_width >> 9) |
	      G1_REG_DEC_CTRL1_PIC_MB_H_EXT(mb_height >> 8);
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL1);

	/* Boolean decoder */
	reg = G1_REG_DEC_CTRL2_BOOLEAN_RANGE(hdr->coder_state.range)
		| G1_REG_DEC_CTRL2_BOOLEAN_VALUE(hdr->coder_state.value);
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL2);

	reg = 0;
	if (hdr->version != 3)
		reg |= G1_REG_DEC_CTRL4_VC1_HEIGHT_EXT;
	if (hdr->version & 0x3)
		reg |= G1_REG_DEC_CTRL4_BILIN_MC_E;
	vdpu_write_relaxed(vpu, reg, G1_REG_DEC_CTRL4);

	cfg_lf(ctx, hdr);
	cfg_qp(ctx, hdr);
	cfg_parts(ctx, hdr);
	cfg_tap(ctx, hdr);
	cfg_ref(ctx, hdr);
	cfg_buffers(ctx, hdr);

	hantro_finish_run(ctx);

	vdpu_write(vpu, G1_REG_INTERRUPT_DEC_E, G1_REG_INTERRUPT);
}