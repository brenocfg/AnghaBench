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
struct vdec_vp9_inst {struct mtk_vcodec_ctx* ctx; } ;
struct mtk_vcodec_ctx {int irq_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_INST_IRQ_RECEIVED ; 
 int MTK_VDEC_IRQ_STATUS_DEC_SUCCESS ; 
 int /*<<< orphan*/  WAIT_INTR_TIMEOUT_MS ; 
 int /*<<< orphan*/  mtk_vcodec_wait_for_done_ctx (struct mtk_vcodec_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vp9_wait_dec_end(struct vdec_vp9_inst *inst)
{
	struct mtk_vcodec_ctx *ctx = inst->ctx;

	mtk_vcodec_wait_for_done_ctx(inst->ctx,
			MTK_INST_IRQ_RECEIVED,
			WAIT_INTR_TIMEOUT_MS);

	if (ctx->irq_status & MTK_VDEC_IRQ_STATUS_DEC_SUCCESS)
		return true;
	else
		return false;
}