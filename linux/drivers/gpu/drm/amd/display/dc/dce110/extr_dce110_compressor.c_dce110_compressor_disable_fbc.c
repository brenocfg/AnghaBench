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
typedef  scalar_t__ uint32_t ;
struct dce110_compressor {int dummy; } ;
struct TYPE_3__ {scalar_t__ FBC_SUPPORT; } ;
struct TYPE_4__ {TYPE_1__ bits; } ;
struct compressor {int is_enabled; scalar_t__ attached_inst; int /*<<< orphan*/  ctx; TYPE_2__ options; } ;

/* Variables and functions */
 scalar_t__ CONTROLLER_ID_D0 ; 
 scalar_t__ CONTROLLER_ID_D3 ; 
 scalar_t__ CONTROLLER_ID_UNDEFINED ; 
 int /*<<< orphan*/  FBC_CNTL ; 
 int /*<<< orphan*/  FBC_GRPH_COMP_EN ; 
 struct dce110_compressor* TO_DCE110_COMPRESSOR (struct compressor*) ; 
 scalar_t__ dce110_compressor_is_fbc_enabled_in_hw (struct compressor*,scalar_t__*) ; 
 scalar_t__ dm_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmFBC_CNTL ; 
 int /*<<< orphan*/  reset_lb_on_vblank (struct compressor*,scalar_t__) ; 
 int /*<<< orphan*/  set_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_fbc_state_changed (struct dce110_compressor*,int) ; 

void dce110_compressor_disable_fbc(struct compressor *compressor)
{
	struct dce110_compressor *cp110 = TO_DCE110_COMPRESSOR(compressor);
	uint32_t crtc_inst = 0;

	if (compressor->options.bits.FBC_SUPPORT) {
		if (dce110_compressor_is_fbc_enabled_in_hw(compressor, &crtc_inst)) {
			uint32_t reg_data;
			/* Turn off compression */
			reg_data = dm_read_reg(compressor->ctx, mmFBC_CNTL);
			set_reg_field_value(reg_data, 0, FBC_CNTL, FBC_GRPH_COMP_EN);
			dm_write_reg(compressor->ctx, mmFBC_CNTL, reg_data);

			/* Reset enum controller_id to undefined */
			compressor->attached_inst = 0;
			compressor->is_enabled = false;

			wait_for_fbc_state_changed(cp110, false);
		}

		/* Sync line buffer which fbc was attached to dce100/110 only */
		if (crtc_inst > CONTROLLER_ID_UNDEFINED && crtc_inst < CONTROLLER_ID_D3)
			reset_lb_on_vblank(compressor,
					crtc_inst - CONTROLLER_ID_D0);
	}
}