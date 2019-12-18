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
struct hantro_dev {int dummy; } ;
struct hantro_ctx {struct hantro_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  G1_REG_CONFIG ; 
 int G1_REG_CONFIG_DEC_AXI_RD_ID (int) ; 
 int G1_REG_CONFIG_DEC_CLK_GATE_E ; 
 int G1_REG_CONFIG_DEC_INSWAP32_E ; 
 int G1_REG_CONFIG_DEC_MAX_BURST (int) ; 
 int G1_REG_CONFIG_DEC_OUTSWAP32_E ; 
 int G1_REG_CONFIG_DEC_OUT_ENDIAN ; 
 int G1_REG_CONFIG_DEC_STRENDIAN_E ; 
 int G1_REG_CONFIG_DEC_STRSWAP32_E ; 
 int G1_REG_CONFIG_DEC_TIMEOUT_E ; 
 int /*<<< orphan*/  G1_REG_INTERRUPT ; 
 int /*<<< orphan*/  G1_REG_INTERRUPT_DEC_E ; 
 int /*<<< orphan*/  hantro_finish_run (struct hantro_ctx*) ; 
 scalar_t__ hantro_h264_dec_prepare_run (struct hantro_ctx*) ; 
 int /*<<< orphan*/  set_buffers (struct hantro_ctx*) ; 
 int /*<<< orphan*/  set_params (struct hantro_ctx*) ; 
 int /*<<< orphan*/  set_ref (struct hantro_ctx*) ; 
 int /*<<< orphan*/  vdpu_write (struct hantro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdpu_write_relaxed (struct hantro_dev*,int,int /*<<< orphan*/ ) ; 

void hantro_g1_h264_dec_run(struct hantro_ctx *ctx)
{
	struct hantro_dev *vpu = ctx->dev;

	/* Prepare the H264 decoder context. */
	if (hantro_h264_dec_prepare_run(ctx))
		return;

	/* Configure hardware registers. */
	set_params(ctx);
	set_ref(ctx);
	set_buffers(ctx);

	hantro_finish_run(ctx);

	/* Start decoding! */
	vdpu_write_relaxed(vpu,
			   G1_REG_CONFIG_DEC_AXI_RD_ID(0xffu) |
			   G1_REG_CONFIG_DEC_TIMEOUT_E |
			   G1_REG_CONFIG_DEC_OUT_ENDIAN |
			   G1_REG_CONFIG_DEC_STRENDIAN_E |
			   G1_REG_CONFIG_DEC_MAX_BURST(16) |
			   G1_REG_CONFIG_DEC_OUTSWAP32_E |
			   G1_REG_CONFIG_DEC_INSWAP32_E |
			   G1_REG_CONFIG_DEC_STRSWAP32_E |
			   G1_REG_CONFIG_DEC_CLK_GATE_E,
			   G1_REG_CONFIG);
	vdpu_write(vpu, G1_REG_INTERRUPT_DEC_E, G1_REG_INTERRUPT);
}