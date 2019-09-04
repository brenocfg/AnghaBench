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
typedef  size_t uint8_t ;
struct timing_generator {TYPE_5__* funcs; } ;
struct irq_source_info {int /*<<< orphan*/  ext_id; int /*<<< orphan*/  src_id; } ;
struct irq_service {struct dc_context* ctx; } ;
struct dc_context {struct dc* dc; } ;
struct dc {TYPE_4__* current_state; } ;
typedef  enum dc_irq_source { ____Placeholder_dc_irq_source } dc_irq_source ;
struct TYPE_10__ {int /*<<< orphan*/  (* arm_vert_intr ) (struct timing_generator*,int) ;} ;
struct TYPE_8__ {TYPE_2__* pipe_ctx; } ;
struct TYPE_9__ {TYPE_3__ res_ctx; } ;
struct TYPE_6__ {struct timing_generator* tg; } ;
struct TYPE_7__ {TYPE_1__ stream_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_ERROR (char*) ; 
 int IRQ_TYPE_VBLANK ; 
 int /*<<< orphan*/  dal_irq_service_set_generic (struct irq_service*,struct irq_source_info const*,int) ; 
 int dc_interrupt_to_irq_source (struct dc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,int) ; 

bool dce110_vblank_set(struct irq_service *irq_service,
		       const struct irq_source_info *info,
		       bool enable)
{
	struct dc_context *dc_ctx = irq_service->ctx;
	struct dc *core_dc = irq_service->ctx->dc;
	enum dc_irq_source dal_irq_src =
			dc_interrupt_to_irq_source(irq_service->ctx->dc,
						   info->src_id,
						   info->ext_id);
	uint8_t pipe_offset = dal_irq_src - IRQ_TYPE_VBLANK;

	struct timing_generator *tg =
			core_dc->current_state->res_ctx.pipe_ctx[pipe_offset].stream_res.tg;

	if (enable) {
		if (!tg || !tg->funcs->arm_vert_intr(tg, 2)) {
			DC_ERROR("Failed to get VBLANK!\n");
			return false;
		}
	}

	dal_irq_service_set_generic(irq_service, info, enable);
	return true;
}