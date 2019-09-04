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
typedef  void* uint8_t ;
typedef  scalar_t__ uint32_t ;
struct select_crtc_source_parameters_v2_3 {void* dst_bpc; int /*<<< orphan*/  encode_mode; void* encoder_id; void* crtc_id; } ;
struct bp_crtc_source_select {int signal; scalar_t__ sink_signal; scalar_t__ display_output_bit_depth; int /*<<< orphan*/  enable_dp_audio; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  controller_id; } ;
struct bios_parser {TYPE_1__* cmd_helper; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_2__ {int /*<<< orphan*/  (* encoder_mode_bp_to_atom ) (int,int /*<<< orphan*/ ) ;scalar_t__ (* engine_bp_to_atom ) (int /*<<< orphan*/ ,scalar_t__*) ;scalar_t__ (* controller_id_to_atom ) (int /*<<< orphan*/ ,void**) ;} ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,struct select_crtc_source_parameters_v2_3) ; 
 int SIGNAL_TYPE_DISPLAY_PORT ; 
 int SIGNAL_TYPE_EDP ; 
 scalar_t__ SIGNAL_TYPE_LVDS ; 
 int /*<<< orphan*/  memset (struct select_crtc_source_parameters_v2_3*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  selectcrtc_source ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result select_crtc_source_v3(
	struct bios_parser *bp,
	struct bp_crtc_source_select *bp_params)
{
	bool result = BP_RESULT_FAILURE;
	struct select_crtc_source_parameters_v2_3 params;
	uint8_t atom_controller_id;
	uint32_t atom_engine_id;
	enum signal_type s = bp_params->signal;

	memset(&params, 0, sizeof(params));

	if (bp->cmd_helper->controller_id_to_atom(bp_params->controller_id,
			&atom_controller_id))
		params.crtc_id = atom_controller_id;
	else
		return result;

	if (bp->cmd_helper->engine_bp_to_atom(bp_params->engine_id,
			&atom_engine_id))
		params.encoder_id = (uint8_t)atom_engine_id;
	else
		return result;

	if (s == SIGNAL_TYPE_EDP ||
		(s == SIGNAL_TYPE_DISPLAY_PORT && bp_params->sink_signal ==
							SIGNAL_TYPE_LVDS))
		s = SIGNAL_TYPE_LVDS;

	params.encode_mode =
			bp->cmd_helper->encoder_mode_bp_to_atom(
					s, bp_params->enable_dp_audio);
	/* Needed for VBIOS Random Spatial Dithering feature */
	params.dst_bpc = (uint8_t)(bp_params->display_output_bit_depth);

	if (EXEC_BIOS_CMD_TABLE(selectcrtc_source, params))
		result = BP_RESULT_OK;

	return result;
}