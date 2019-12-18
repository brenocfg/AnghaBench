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
typedef  int /*<<< orphan*/  uint16_t ;
struct command_table_helper {scalar_t__ (* encoder_mode_bp_to_atom ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* encoder_action_to_atom ) (int /*<<< orphan*/ ) ;scalar_t__ (* transmitter_bp_to_atom ) (scalar_t__) ;} ;
struct bp_encoder_control {scalar_t__ transmitter; int pixel_clock; scalar_t__ lanes_number; int /*<<< orphan*/  enable_dp_audio; int /*<<< orphan*/  signal; int /*<<< orphan*/  action; } ;
struct TYPE_4__ {int ucLinkSel; void* ucTransmitterSel; } ;
struct TYPE_5__ {void* ucLaneNum; void* ucEncoderMode; int /*<<< orphan*/  usPixelClock; int /*<<< orphan*/  ucAction; TYPE_1__ acConfig; } ;
typedef  TYPE_2__ DIG_ENCODER_CONTROL_PARAMETERS_V2 ;

/* Variables and functions */
 scalar_t__ TRANSMITTER_UNIPHY_B ; 
 scalar_t__ TRANSMITTER_UNIPHY_D ; 
 scalar_t__ TRANSMITTER_UNIPHY_F ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dal_cmd_table_helper_assign_control_parameter(
	const struct command_table_helper *h,
	struct bp_encoder_control *control,
	DIG_ENCODER_CONTROL_PARAMETERS_V2 *ctrl_param)
{
	/* there are three transmitter blocks, each one has two links 4-lanes
	 * each, A+B, C+D, E+F, Uniphy A, C and E are enumerated as link 0 in
	 * each transmitter block B, D and F as link 1, third transmitter block
	 * has non splitable links (UniphyE and UniphyF can not be configured
	 * separately to drive two different streams)
	 */
	if ((control->transmitter == TRANSMITTER_UNIPHY_B) ||
		(control->transmitter == TRANSMITTER_UNIPHY_D) ||
		(control->transmitter == TRANSMITTER_UNIPHY_F)) {
		/* Bit2: Link Select
		 * =0: PHY linkA/C/E
		 * =1: PHY linkB/D/F
		 */
		ctrl_param->acConfig.ucLinkSel = 1;
	}

	/* Bit[4:3]: Transmitter Selection
	 * =00: Digital Transmitter1 ( UNIPHY linkAB )
	 * =01: Digital Transmitter2 ( UNIPHY linkCD )
	 * =02: Digital Transmitter3 ( UNIPHY linkEF )
	 * =03: Reserved
	 */
	ctrl_param->acConfig.ucTransmitterSel =
		(uint8_t)(h->transmitter_bp_to_atom(control->transmitter));

	/* We need to convert from KHz units into 10KHz units */
	ctrl_param->ucAction = h->encoder_action_to_atom(control->action);
	ctrl_param->usPixelClock = cpu_to_le16((uint16_t)(control->pixel_clock / 10));
	ctrl_param->ucEncoderMode =
		(uint8_t)(h->encoder_mode_bp_to_atom(
			control->signal, control->enable_dp_audio));
	ctrl_param->ucLaneNum = (uint8_t)(control->lanes_number);
}