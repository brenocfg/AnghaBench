#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct graphics_object_id {int enum_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct bp_external_encoder_control {int action; int pixel_clock; scalar_t__ lanes_number; int /*<<< orphan*/  signal; scalar_t__ color_depth; int /*<<< orphan*/  link_rate; TYPE_1__ connector_obj_id; struct graphics_object_id encoder_id; } ;
struct bios_parser {TYPE_2__* cmd_helper; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_10__ {int ucConfig; void* ucAction; void* ucLaneNum; void* ucEncoderMode; void* usPixelClock; void* ucBitPerColor; void* usConnectorId; } ;
struct TYPE_9__ {TYPE_4__ sExtEncoder; } ;
struct TYPE_8__ {scalar_t__ (* encoder_mode_bp_to_atom ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_3__ EXTERNAL_ENCODER_CONTROL_PS_ALLOCATION_V3 ;
typedef  TYPE_4__ EXTERNAL_ENCODER_CONTROL_PARAMETERS_V3 ;

/* Variables and functions */
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  ENCODER_ID_EXTERNAL_NUTMEG 132 
#define  ENCODER_ID_EXTERNAL_TRAVIS 131 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_3__) ; 
#define  EXTERNAL_ENCODER_CONTROL_ENABLE 130 
#define  EXTERNAL_ENCODER_CONTROL_INIT 129 
#define  EXTERNAL_ENCODER_CONTROL_SETUP 128 
 int /*<<< orphan*/  ExternalEncoderControl ; 
 int /*<<< orphan*/  LINK_RATE_HIGH ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int dal_graphics_object_id_get_encoder_id (struct graphics_object_id) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum bp_result external_encoder_control_v3(
	struct bios_parser *bp,
	struct bp_external_encoder_control *cntl)
{
	enum bp_result result = BP_RESULT_FAILURE;

	/* we need use _PS_Alloc struct */
	EXTERNAL_ENCODER_CONTROL_PS_ALLOCATION_V3 params;
	EXTERNAL_ENCODER_CONTROL_PARAMETERS_V3 *cntl_params;
	struct graphics_object_id encoder;
	bool is_input_signal_dp = false;

	memset(&params, 0, sizeof(params));

	cntl_params = &params.sExtEncoder;

	encoder = cntl->encoder_id;

	/* check if encoder supports external encoder control table */
	switch (dal_graphics_object_id_get_encoder_id(encoder)) {
	case ENCODER_ID_EXTERNAL_NUTMEG:
	case ENCODER_ID_EXTERNAL_TRAVIS:
		is_input_signal_dp = true;
		break;

	default:
		BREAK_TO_DEBUGGER();
		return BP_RESULT_BADINPUT;
	}

	/* Fill information based on the action
	 *
	 * Bit[6:4]: indicate external encoder, applied to all functions.
	 * =0: external encoder1, mapped to external encoder enum id1
	 * =1: external encoder2, mapped to external encoder enum id2
	 *
	 * enum ObjectEnumId
	 * {
	 *  EnumId_Unknown = 0,
	 *  EnumId_1,
	 *  EnumId_2,
	 * };
	 */
	cntl_params->ucConfig = (uint8_t)((encoder.enum_id - 1) << 4);

	switch (cntl->action) {
	case EXTERNAL_ENCODER_CONTROL_INIT:
		/* output display connector type. Only valid in encoder
		 * initialization */
		cntl_params->usConnectorId =
				cpu_to_le16((uint16_t)cntl->connector_obj_id.id);
		break;
	case EXTERNAL_ENCODER_CONTROL_SETUP:
		/* EXTERNAL_ENCODER_CONTROL_PARAMETERS_V3 pixel clock unit in
		 * 10KHz
		 * output display device pixel clock frequency in unit of 10KHz.
		 * Only valid in setup and enableoutput
		 */
		cntl_params->usPixelClock =
				cpu_to_le16((uint16_t)(cntl->pixel_clock / 10));
		/* Indicate display output signal type drive by external
		 * encoder, only valid in setup and enableoutput */
		cntl_params->ucEncoderMode =
				(uint8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
						cntl->signal, false);

		if (is_input_signal_dp) {
			/* Bit[0]: indicate link rate, =1: 2.7Ghz, =0: 1.62Ghz,
			 * only valid in encoder setup with DP mode. */
			if (LINK_RATE_HIGH == cntl->link_rate)
				cntl_params->ucConfig |= 1;
			/* output color depth Indicate encoder data bpc format
			 * in DP mode, only valid in encoder setup in DP mode.
			 */
			cntl_params->ucBitPerColor =
					(uint8_t)(cntl->color_depth);
		}
		/* Indicate how many lanes used by external encoder, only valid
		 * in encoder setup and enableoutput. */
		cntl_params->ucLaneNum = (uint8_t)(cntl->lanes_number);
		break;
	case EXTERNAL_ENCODER_CONTROL_ENABLE:
		cntl_params->usPixelClock =
				cpu_to_le16((uint16_t)(cntl->pixel_clock / 10));
		cntl_params->ucEncoderMode =
				(uint8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
						cntl->signal, false);
		cntl_params->ucLaneNum = (uint8_t)cntl->lanes_number;
		break;
	default:
		break;
	}

	cntl_params->ucAction = (uint8_t)cntl->action;

	if (EXEC_BIOS_CMD_TABLE(ExternalEncoderControl, params))
		result = BP_RESULT_OK;

	return result;
}