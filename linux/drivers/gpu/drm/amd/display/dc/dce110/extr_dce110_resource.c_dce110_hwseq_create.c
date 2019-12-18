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
struct TYPE_3__ {int blnd_crtc_trigger; } ;
struct dce_hwseq {TYPE_1__ wa; int /*<<< orphan*/ * masks; int /*<<< orphan*/ * shifts; int /*<<< orphan*/ * regs; struct dc_context* ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_internal_rev; } ;
struct dc_context {TYPE_2__ asic_id; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_IS_STONEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hwseq_cz_reg ; 
 int /*<<< orphan*/  hwseq_mask ; 
 int /*<<< orphan*/  hwseq_shift ; 
 int /*<<< orphan*/  hwseq_stoney_reg ; 
 struct dce_hwseq* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dce_hwseq *dce110_hwseq_create(
	struct dc_context *ctx)
{
	struct dce_hwseq *hws = kzalloc(sizeof(struct dce_hwseq), GFP_KERNEL);

	if (hws) {
		hws->ctx = ctx;
		hws->regs = ASIC_REV_IS_STONEY(ctx->asic_id.hw_internal_rev) ?
				&hwseq_stoney_reg : &hwseq_cz_reg;
		hws->shifts = &hwseq_shift;
		hws->masks = &hwseq_mask;
		hws->wa.blnd_crtc_trigger = true;
	}
	return hws;
}