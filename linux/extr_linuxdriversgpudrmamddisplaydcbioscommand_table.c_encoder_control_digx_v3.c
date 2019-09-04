#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bp_encoder_control {scalar_t__ lanes_number; int pixel_clock; int /*<<< orphan*/  enable_dp_audio; int /*<<< orphan*/  signal; int /*<<< orphan*/  action; scalar_t__ engine_id; } ;
struct bios_parser {TYPE_2__* cmd_helper; } ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_5__ {int ucDPLinkRate; void* ucDigSel; } ;
struct TYPE_7__ {void* ucLaneNum; void* ucEncoderMode; int /*<<< orphan*/  usPixelClock; int /*<<< orphan*/  ucAction; TYPE_1__ acConfig; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {scalar_t__ (* encoder_mode_bp_to_atom ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* encoder_action_to_atom ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ DIG_ENCODER_CONTROL_PARAMETERS_V3 ;

/* Variables and functions */
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 int /*<<< orphan*/  DIGxEncoderControl ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_3__) ; 
 scalar_t__ LANE_COUNT_FOUR ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum bp_result encoder_control_digx_v3(
	struct bios_parser *bp,
	struct bp_encoder_control *cntl)
{
	enum bp_result result = BP_RESULT_FAILURE;
	DIG_ENCODER_CONTROL_PARAMETERS_V3 params = {0};

	if (LANE_COUNT_FOUR < cntl->lanes_number)
		params.acConfig.ucDPLinkRate = 1; /* dual link 2.7GHz */
	else
		params.acConfig.ucDPLinkRate = 0; /* single link 1.62GHz */

	params.acConfig.ucDigSel = (uint8_t)(cntl->engine_id);

	/* We need to convert from KHz units into 10KHz units */
	params.ucAction = bp->cmd_helper->encoder_action_to_atom(cntl->action);
	params.usPixelClock = cpu_to_le16((uint16_t)(cntl->pixel_clock / 10));
	params.ucEncoderMode =
			(uint8_t)bp->cmd_helper->encoder_mode_bp_to_atom(
					cntl->signal,
					cntl->enable_dp_audio);
	params.ucLaneNum = (uint8_t)(cntl->lanes_number);

	if (EXEC_BIOS_CMD_TABLE(DIGxEncoderControl, params))
		result = BP_RESULT_OK;

	return result;
}