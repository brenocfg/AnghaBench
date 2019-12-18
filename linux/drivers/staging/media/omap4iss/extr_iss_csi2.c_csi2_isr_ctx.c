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
typedef  int u32 ;
typedef  int u16 ;
struct iss_pipeline {int /*<<< orphan*/  frame_number; } ;
struct TYPE_2__ {int /*<<< orphan*/  entity; } ;
struct iss_csi2_device {scalar_t__ frame_skip; int output; int /*<<< orphan*/  regs1; int /*<<< orphan*/  iss; TYPE_1__ subdev; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; } ;
struct iss_csi2_ctx_cfg {unsigned int ctxnum; int frame; int /*<<< orphan*/  format_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_CTX_CTRL2 (unsigned int) ; 
 int CSI2_CTX_CTRL2_FRAME_SHIFT ; 
 int /*<<< orphan*/  CSI2_CTX_IRQSTATUS (unsigned int) ; 
 int CSI2_CTX_IRQ_FE ; 
 int CSI2_CTX_IRQ_FS ; 
 int CSI2_OUTPUT_MEMORY ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csi2_ctx_config (struct iss_csi2_device*,struct iss_csi2_ctx_cfg*) ; 
 int /*<<< orphan*/  csi2_ctx_enable (struct iss_csi2_device*,unsigned int,int) ; 
 int /*<<< orphan*/  csi2_ctx_map_format (struct iss_csi2_device*) ; 
 int /*<<< orphan*/  csi2_isr_buffer (struct iss_csi2_device*) ; 
 int iss_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ omap4iss_module_sync_is_stopping (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iss_pipeline* to_iss_pipeline (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void csi2_isr_ctx(struct iss_csi2_device *csi2,
			 struct iss_csi2_ctx_cfg *ctx)
{
	unsigned int n = ctx->ctxnum;
	u32 status;

	status = iss_reg_read(csi2->iss, csi2->regs1, CSI2_CTX_IRQSTATUS(n));
	iss_reg_write(csi2->iss, csi2->regs1, CSI2_CTX_IRQSTATUS(n), status);

	if (omap4iss_module_sync_is_stopping(&csi2->wait, &csi2->stopping))
		return;

	/* Propagate frame number */
	if (status & CSI2_CTX_IRQ_FS) {
		struct iss_pipeline *pipe =
				     to_iss_pipeline(&csi2->subdev.entity);
		u16 frame;
		u16 delta;

		frame = iss_reg_read(csi2->iss, csi2->regs1,
				     CSI2_CTX_CTRL2(ctx->ctxnum))
		      >> CSI2_CTX_CTRL2_FRAME_SHIFT;

		if (frame == 0) {
			/* A zero value means that the counter isn't implemented
			 * by the source. Increment the frame number in software
			 * in that case.
			 */
			atomic_inc(&pipe->frame_number);
		} else {
			/* Extend the 16 bit frame number to 32 bits by
			 * computing the delta between two consecutive CSI2
			 * frame numbers and adding it to the software frame
			 * number. The hardware counter starts at 1 and wraps
			 * from 0xffff to 1 without going through 0, so subtract
			 * 1 when the counter wraps.
			 */
			delta = frame - ctx->frame;
			if (frame < ctx->frame)
				delta--;
			ctx->frame = frame;

			atomic_add(delta, &pipe->frame_number);
		}
	}

	if (!(status & CSI2_CTX_IRQ_FE))
		return;

	/* Skip interrupts until we reach the frame skip count. The CSI2 will be
	 * automatically disabled, as the frame skip count has been programmed
	 * in the CSI2_CTx_CTRL1::COUNT field, so re-enable it.
	 *
	 * It would have been nice to rely on the FRAME_NUMBER interrupt instead
	 * but it turned out that the interrupt is only generated when the CSI2
	 * writes to memory (the CSI2_CTx_CTRL1::COUNT field is decreased
	 * correctly and reaches 0 when data is forwarded to the video port only
	 * but no interrupt arrives). Maybe a CSI2 hardware bug.
	 */
	if (csi2->frame_skip) {
		csi2->frame_skip--;
		if (csi2->frame_skip == 0) {
			ctx->format_id = csi2_ctx_map_format(csi2);
			csi2_ctx_config(csi2, ctx);
			csi2_ctx_enable(csi2, n, 1);
		}
		return;
	}

	if (csi2->output & CSI2_OUTPUT_MEMORY)
		csi2_isr_buffer(csi2);
}