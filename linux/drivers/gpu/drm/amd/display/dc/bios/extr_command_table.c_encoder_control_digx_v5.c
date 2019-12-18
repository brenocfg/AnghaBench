#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct bp_encoder_control {int pixel_clock; scalar_t__ signal; int color_depth; scalar_t__ lanes_number; int /*<<< orphan*/  enable_dp_audio; int /*<<< orphan*/  action; scalar_t__ engine_id; } ;
struct bios_parser {TYPE_1__* cmd_helper; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_5__ {int ulPixelClock; int /*<<< orphan*/  ucBitPerColor; void* ucLaneNum; void* ucDigMode; int /*<<< orphan*/  ucAction; void* ucDigId; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {scalar_t__ (* encoder_mode_bp_to_atom ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* encoder_action_to_atom ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ ENCODER_STREAM_SETUP_PARAMETERS_V5 ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
#define  COLOR_DEPTH_101010 131 
#define  COLOR_DEPTH_121212 130 
#define  COLOR_DEPTH_161616 129 
#define  COLOR_DEPTH_888 128 
 int /*<<< orphan*/  DIGxEncoderControl ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  PANEL_10BIT_PER_COLOR ; 
 int /*<<< orphan*/  PANEL_12BIT_PER_COLOR ; 
 int /*<<< orphan*/  PANEL_16BIT_PER_COLOR ; 
 int /*<<< orphan*/  PANEL_8BIT_PER_COLOR ; 
 scalar_t__ SIGNAL_TYPE_HDMI_TYPE_A ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result encoder_control_digx_v5(
	struct bios_parser *bp,
	struct bp_encoder_control *cntl)
{
	enum bp_result result = BP_RESULT_FAILURE;
	ENCODER_STREAM_SETUP_PARAMETERS_V5 params = {0};

	params.ucDigId = (uint8_t)(cntl->engine_id);
	params.ucAction = bp->cmd_helper->encoder_action_to_atom(cntl->action);

	params.ulPixelClock = cntl->pixel_clock / 10;
	params.ucDigMode =
			(uint8_t)(bp->cmd_helper->encoder_mode_bp_to_atom(
					cntl->signal,
					cntl->enable_dp_audio));
	params.ucLaneNum = (uint8_t)(cntl->lanes_number);

	switch (cntl->color_depth) {
	case COLOR_DEPTH_888:
		params.ucBitPerColor = PANEL_8BIT_PER_COLOR;
		break;
	case COLOR_DEPTH_101010:
		params.ucBitPerColor = PANEL_10BIT_PER_COLOR;
		break;
	case COLOR_DEPTH_121212:
		params.ucBitPerColor = PANEL_12BIT_PER_COLOR;
		break;
	case COLOR_DEPTH_161616:
		params.ucBitPerColor = PANEL_16BIT_PER_COLOR;
		break;
	default:
		break;
	}

	if (cntl->signal == SIGNAL_TYPE_HDMI_TYPE_A)
		switch (cntl->color_depth) {
		case COLOR_DEPTH_101010:
			params.ulPixelClock =
				(params.ulPixelClock * 30) / 24;
			break;
		case COLOR_DEPTH_121212:
			params.ulPixelClock =
				(params.ulPixelClock * 36) / 24;
			break;
		case COLOR_DEPTH_161616:
			params.ulPixelClock =
				(params.ulPixelClock * 48) / 24;
			break;
		default:
			break;
		}

	if (EXEC_BIOS_CMD_TABLE(DIGxEncoderControl, params))
		result = BP_RESULT_OK;

	return result;
}