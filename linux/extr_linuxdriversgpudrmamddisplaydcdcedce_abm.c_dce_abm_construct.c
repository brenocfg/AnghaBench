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
struct dce_abm_shift {int dummy; } ;
struct dce_abm_registers {int dummy; } ;
struct dce_abm_mask {int dummy; } ;
struct TYPE_2__ {scalar_t__ LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV; scalar_t__ BL_PWM_PERIOD_CNTL; scalar_t__ BL_PWM_CNTL2; scalar_t__ BL_PWM_CNTL; } ;
struct abm {TYPE_1__ stored_backlight_registers; int /*<<< orphan*/ * funcs; struct dc_context* ctx; } ;
struct dce_abm {struct dce_abm_mask const* abm_mask; struct dce_abm_shift const* abm_shift; struct dce_abm_registers const* regs; struct abm base; } ;
struct dc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dce_funcs ; 

__attribute__((used)) static void dce_abm_construct(
	struct dce_abm *abm_dce,
	struct dc_context *ctx,
	const struct dce_abm_registers *regs,
	const struct dce_abm_shift *abm_shift,
	const struct dce_abm_mask *abm_mask)
{
	struct abm *base = &abm_dce->base;

	base->ctx = ctx;
	base->funcs = &dce_funcs;
	base->stored_backlight_registers.BL_PWM_CNTL = 0;
	base->stored_backlight_registers.BL_PWM_CNTL2 = 0;
	base->stored_backlight_registers.BL_PWM_PERIOD_CNTL = 0;
	base->stored_backlight_registers.LVTMA_PWRSEQ_REF_DIV_BL_PWM_REF_DIV = 0;

	abm_dce->regs = regs;
	abm_dce->abm_shift = abm_shift;
	abm_dce->abm_mask = abm_mask;
}