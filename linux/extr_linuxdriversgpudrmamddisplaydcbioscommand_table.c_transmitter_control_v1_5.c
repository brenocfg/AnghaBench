#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint16_t ;
struct command_table_helper {int /*<<< orphan*/  (* dig_encoder_sel_to_atom ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* hpd_sel_to_atom ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* clock_source_id_to_atom_phy_clk_src_id ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* signal_type_to_atom_dig_mode ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* phy_id_to_atom ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {scalar_t__ id; } ;
struct bp_transmitter_control {int pixel_clock; int color_depth; int /*<<< orphan*/  signal; scalar_t__ lane_settings; int /*<<< orphan*/  engine_id; int /*<<< orphan*/  hpd_sel; int /*<<< orphan*/  coherent; int /*<<< orphan*/  pll_id; TYPE_1__ connector_obj_id; scalar_t__ lanes_number; scalar_t__ action; int /*<<< orphan*/  transmitter; } ;
struct bios_parser {struct command_table_helper* cmd_helper; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_7__ {int /*<<< orphan*/  ucHPDSel; int /*<<< orphan*/  ucCoherentMode; int /*<<< orphan*/  ucPhyClkSrcId; } ;
struct TYPE_8__ {void* usSymClock; void* ucDPLaneSet; int /*<<< orphan*/  ucDigEncoderSel; TYPE_2__ asConfig; int /*<<< orphan*/  ucDigMode; void* ucConnObjId; void* ucLaneNum; void* ucAction; int /*<<< orphan*/  ucPhyId; } ;
typedef  TYPE_3__ DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_5 ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
#define  COLOR_DEPTH_101010 130 
#define  COLOR_DEPTH_121212 129 
#define  COLOR_DEPTH_161616 128 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_3__) ; 
 int /*<<< orphan*/  SIGNAL_TYPE_HDMI_TYPE_A ; 
 int /*<<< orphan*/  UNIPHYTransmitterControl ; 
 void* cpu_to_le16 (int) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result transmitter_control_v1_5(
	struct bios_parser *bp,
	struct bp_transmitter_control *cntl)
{
	enum bp_result result = BP_RESULT_FAILURE;
	const struct command_table_helper *cmd = bp->cmd_helper;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_5 params;

	memset(&params, 0, sizeof(params));
	params.ucPhyId = cmd->phy_id_to_atom(cntl->transmitter);
	params.ucAction = (uint8_t)cntl->action;
	params.ucLaneNum = (uint8_t)cntl->lanes_number;
	params.ucConnObjId = (uint8_t)cntl->connector_obj_id.id;

	params.ucDigMode =
		cmd->signal_type_to_atom_dig_mode(cntl->signal);
	params.asConfig.ucPhyClkSrcId =
		cmd->clock_source_id_to_atom_phy_clk_src_id(cntl->pll_id);
	/* 00 - coherent mode */
	params.asConfig.ucCoherentMode = cntl->coherent;
	params.asConfig.ucHPDSel =
		cmd->hpd_sel_to_atom(cntl->hpd_sel);
	params.ucDigEncoderSel =
		cmd->dig_encoder_sel_to_atom(cntl->engine_id);
	params.ucDPLaneSet = (uint8_t) cntl->lane_settings;
	params.usSymClock = cpu_to_le16((uint16_t) (cntl->pixel_clock / 10));
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
	if  (cntl->signal == SIGNAL_TYPE_HDMI_TYPE_A) {
		switch (cntl->color_depth) {
		case COLOR_DEPTH_101010:
			params.usSymClock =
				cpu_to_le16((le16_to_cpu(params.usSymClock) * 30) / 24);
			break;
		case COLOR_DEPTH_121212:
			params.usSymClock =
				cpu_to_le16((le16_to_cpu(params.usSymClock) * 36) / 24);
			break;
		case COLOR_DEPTH_161616:
			params.usSymClock =
				cpu_to_le16((le16_to_cpu(params.usSymClock) * 48) / 24);
			break;
		default:
			break;
		}
	}

	if (EXEC_BIOS_CMD_TABLE(UNIPHYTransmitterControl, params))
		result = BP_RESULT_OK;

	return result;
}