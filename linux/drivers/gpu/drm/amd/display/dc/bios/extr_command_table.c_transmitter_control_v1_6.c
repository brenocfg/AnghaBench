#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct command_table_helper {int /*<<< orphan*/  (* dig_encoder_sel_to_atom ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hpd_sel_to_atom ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* signal_type_to_atom_dig_mode ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* phy_id_to_atom ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ id; } ;
struct bp_transmitter_control {scalar_t__ action; int pixel_clock; int /*<<< orphan*/  color_depth; int /*<<< orphan*/  signal; TYPE_1__ connector_obj_id; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  hpd_sel; scalar_t__ lanes_number; scalar_t__ lane_settings; int /*<<< orphan*/  transmitter; } ;
struct bios_parser {struct command_table_helper* cmd_helper; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_6__ {int ulSymClock; void* ucConnObjId; int /*<<< orphan*/  ucDigEncoderSel; int /*<<< orphan*/  ucHPDSel; void* ucLaneNum; int /*<<< orphan*/  ucDigMode; void* ucDPLaneSet; void* ucAction; int /*<<< orphan*/  ucPhyId; } ;
typedef  TYPE_2__ DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_6 ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
#define  COLOR_DEPTH_101010 131 
#define  COLOR_DEPTH_121212 130 
#define  COLOR_DEPTH_161616 129 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_2__) ; 
#define  SIGNAL_TYPE_HDMI_TYPE_A 128 
 scalar_t__ TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS ; 
 int /*<<< orphan*/  UNIPHYTransmitterControl ; 
 void* cpu_to_le16 (int) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result transmitter_control_v1_6(
	struct bios_parser *bp,
	struct bp_transmitter_control *cntl)
{
	enum bp_result result = BP_RESULT_FAILURE;
	const struct command_table_helper *cmd = bp->cmd_helper;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_6 params;

	memset(&params, 0, sizeof(params));
	params.ucPhyId = cmd->phy_id_to_atom(cntl->transmitter);
	params.ucAction = (uint8_t)cntl->action;

	if (cntl->action == TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS)
		params.ucDPLaneSet = (uint8_t)cntl->lane_settings;
	else
		params.ucDigMode = cmd->signal_type_to_atom_dig_mode(cntl->signal);

	params.ucLaneNum = (uint8_t)cntl->lanes_number;
	params.ucHPDSel = cmd->hpd_sel_to_atom(cntl->hpd_sel);
	params.ucDigEncoderSel = cmd->dig_encoder_sel_to_atom(cntl->engine_id);
	params.ucConnObjId = (uint8_t)cntl->connector_obj_id.id;
	params.ulSymClock = cntl->pixel_clock/10;

	/*
	 * In SI/TN case, caller have to set usPixelClock as following:
	 * DP mode: usPixelClock = DP_LINK_CLOCK/10
	 * (DP_LINK_CLOCK = 1.62GHz, 2.7GHz, 5.4GHz)
	 * DVI single link mode: usPixelClock = pixel clock
	 * DVI dual link mode: usPixelClock = pixel clock
	 * HDMI mode: usPixelClock = pixel clock * deep_color_ratio
	 * (=1: 8bpp, =1.25: 10bpp, =1.5:12bpp, =2: 16bpp)
	 * LVDS mode: usPixelClock = pixel clock
	 */
	switch (cntl->signal) {
	case SIGNAL_TYPE_HDMI_TYPE_A:
		switch (cntl->color_depth) {
		case COLOR_DEPTH_101010:
			params.ulSymClock =
				cpu_to_le16((le16_to_cpu(params.ulSymClock) * 30) / 24);
			break;
		case COLOR_DEPTH_121212:
			params.ulSymClock =
				cpu_to_le16((le16_to_cpu(params.ulSymClock) * 36) / 24);
			break;
		case COLOR_DEPTH_161616:
			params.ulSymClock =
				cpu_to_le16((le16_to_cpu(params.ulSymClock) * 48) / 24);
			break;
		default:
			break;
		}
		break;
		default:
			break;
	}

	if (EXEC_BIOS_CMD_TABLE(UNIPHYTransmitterControl, params))
		result = BP_RESULT_OK;
	return result;
}