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
typedef  int uint32_t ;
struct dce112_compressor {int /*<<< orphan*/  offsets; } ;
struct TYPE_3__ {scalar_t__ DUMMY_BACKEND; scalar_t__ LPT_SUPPORT; scalar_t__ FBC_SUPPORT; } ;
struct TYPE_4__ {TYPE_1__ bits; } ;
struct compressor {int is_enabled; int attached_inst; int /*<<< orphan*/  ctx; TYPE_2__ options; } ;
struct compr_addr_and_pitch_params {int source_view_width; int source_view_height; int inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBC_CNTL ; 
 int /*<<< orphan*/  FBC_GRPH_COMP_EN ; 
 int /*<<< orphan*/  FBC_SRC_SEL ; 
 struct dce112_compressor* TO_DCE112_COMPRESSOR (struct compressor*) ; 
 int /*<<< orphan*/  dce112_compressor_enable_lpt (struct compressor*) ; 
 int /*<<< orphan*/  dce112_compressor_is_fbc_enabled_in_hw (struct compressor*,int /*<<< orphan*/ *) ; 
 int dce11_one_lpt_channel_max_resolution ; 
 int dm_read_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dm_write_reg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  is_source_bigger_than_epanel_size (struct dce112_compressor*,int,int) ; 
 int mmFBC_CNTL ; 
 int /*<<< orphan*/ * reg_offsets ; 
 int /*<<< orphan*/  set_reg_field_value (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_fbc_state_changed (struct dce112_compressor*,int) ; 

void dce112_compressor_enable_fbc(
	struct compressor *compressor,
	uint32_t paths_num,
	struct compr_addr_and_pitch_params *params)
{
	struct dce112_compressor *cp110 = TO_DCE112_COMPRESSOR(compressor);

	if (compressor->options.bits.FBC_SUPPORT &&
		(compressor->options.bits.DUMMY_BACKEND == 0) &&
		(!dce112_compressor_is_fbc_enabled_in_hw(compressor, NULL)) &&
		(!is_source_bigger_than_epanel_size(
			cp110,
			params->source_view_width,
			params->source_view_height))) {

		uint32_t addr;
		uint32_t value;

		/* Before enabling FBC first need to enable LPT if applicable
		 * LPT state should always be changed (enable/disable) while FBC
		 * is disabled */
		if (compressor->options.bits.LPT_SUPPORT && (paths_num < 2) &&
			(params->source_view_width *
				params->source_view_height <=
				dce11_one_lpt_channel_max_resolution)) {
			dce112_compressor_enable_lpt(compressor);
		}

		addr = mmFBC_CNTL;
		value = dm_read_reg(compressor->ctx, addr);
		set_reg_field_value(value, 1, FBC_CNTL, FBC_GRPH_COMP_EN);
		set_reg_field_value(
			value,
			params->inst,
			FBC_CNTL, FBC_SRC_SEL);
		dm_write_reg(compressor->ctx, addr, value);

		/* Keep track of enum controller_id FBC is attached to */
		compressor->is_enabled = true;
		compressor->attached_inst = params->inst;
		cp110->offsets = reg_offsets[params->inst];

		/*Toggle it as there is bug in HW */
		set_reg_field_value(value, 0, FBC_CNTL, FBC_GRPH_COMP_EN);
		dm_write_reg(compressor->ctx, addr, value);
		set_reg_field_value(value, 1, FBC_CNTL, FBC_GRPH_COMP_EN);
		dm_write_reg(compressor->ctx, addr, value);

		wait_for_fbc_state_changed(cp110, true);
	}
}