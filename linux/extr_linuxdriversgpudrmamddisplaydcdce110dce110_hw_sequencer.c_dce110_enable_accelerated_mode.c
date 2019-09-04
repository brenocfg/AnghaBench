#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dc_state {int dummy; } ;
struct dc_link {TYPE_4__* link_enc; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* edp_power_control ) (struct dc_link*,int) ;int /*<<< orphan*/  (* edp_backlight_control ) (struct dc_link*,int) ;} ;
struct dc {int apply_edp_fast_boot_optimization; TYPE_3__* ctx; TYPE_2__ hwss; } ;
struct TYPE_8__ {TYPE_1__* funcs; } ;
struct TYPE_7__ {scalar_t__ dce_version; int /*<<< orphan*/  dc_bios; } ;
struct TYPE_5__ {int (* is_dig_enabled ) (TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ DCE_VERSION_8_0 ; 
 scalar_t__ DCE_VERSION_8_1 ; 
 scalar_t__ DCE_VERSION_8_3 ; 
 int /*<<< orphan*/  bios_set_scratch_acc_mode_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_vga_and_power_gate_all_controllers (struct dc*) ; 
 struct dc_link* get_link_for_edp (struct dc*) ; 
 struct dc_link* get_link_for_edp_not_in_use (struct dc*,struct dc_state*) ; 
 int /*<<< orphan*/  power_down_all_hw_blocks (struct dc*) ; 
 int stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (struct dc_link*,int) ; 
 int /*<<< orphan*/  stub3 (struct dc_link*,int) ; 

void dce110_enable_accelerated_mode(struct dc *dc, struct dc_state *context)
{
	struct dc_link *edp_link_to_turnoff = NULL;
	struct dc_link *edp_link = get_link_for_edp(dc);
	bool can_eDP_fast_boot_optimize = false;

	if (edp_link) {
		/* this seems to cause blank screens on DCE8 */
		if ((dc->ctx->dce_version == DCE_VERSION_8_0) ||
		    (dc->ctx->dce_version == DCE_VERSION_8_1) ||
		    (dc->ctx->dce_version == DCE_VERSION_8_3))
			can_eDP_fast_boot_optimize = false;
		else
			can_eDP_fast_boot_optimize =
				edp_link->link_enc->funcs->is_dig_enabled(edp_link->link_enc);
	}

	if (can_eDP_fast_boot_optimize) {
		edp_link_to_turnoff = get_link_for_edp_not_in_use(dc, context);

		/* if OS doesn't light up eDP and eDP link is available, we want to disable
		 * If resume from S4/S5, should optimization.
		 */
		if (!edp_link_to_turnoff)
			dc->apply_edp_fast_boot_optimization = true;
	}

	if (!dc->apply_edp_fast_boot_optimization) {
		if (edp_link_to_turnoff) {
			/*turn off backlight before DP_blank and encoder powered down*/
			dc->hwss.edp_backlight_control(edp_link_to_turnoff, false);
		}
		/*resume from S3, no vbios posting, no need to power down again*/
		power_down_all_hw_blocks(dc);
		disable_vga_and_power_gate_all_controllers(dc);
		if (edp_link_to_turnoff)
			dc->hwss.edp_power_control(edp_link_to_turnoff, false);
	}
	bios_set_scratch_acc_mode_change(dc->ctx->dc_bios);
}