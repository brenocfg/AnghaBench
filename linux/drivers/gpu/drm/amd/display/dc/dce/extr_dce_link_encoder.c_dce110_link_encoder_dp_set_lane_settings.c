#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  POST_CURSOR2_SET; int /*<<< orphan*/  PRE_EMPHASIS_SET; int /*<<< orphan*/  VOLTAGE_SWING_SET; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
union dpcd_training_lane_set {int /*<<< orphan*/  raw; TYPE_4__ bits; TYPE_1__ member_0; } ;
struct TYPE_8__ {size_t lane_count; int link_rate; } ;
struct link_training_settings {TYPE_5__* lane_settings; TYPE_3__ link_settings; } ;
struct link_encoder {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  hpd_source; int /*<<< orphan*/  connector; int /*<<< orphan*/  transmitter; } ;
struct dce110_link_encoder {TYPE_2__ base; } ;
struct bp_transmitter_control {size_t lanes_number; int pixel_clock; size_t lane_select; int /*<<< orphan*/  lane_settings; int /*<<< orphan*/  hpd_sel; int /*<<< orphan*/  connector_obj_id; int /*<<< orphan*/  transmitter; int /*<<< orphan*/  action; int /*<<< orphan*/  member_0; } ;
typedef  size_t int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  POST_CURSOR2; int /*<<< orphan*/  PRE_EMPHASIS; int /*<<< orphan*/  VOLTAGE_SWING; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int LINK_RATE_HIGH2 ; 
 int LINK_RATE_REF_FREQ_IN_KHZ ; 
 struct dce110_link_encoder* TO_DCE110_LINK_ENC (struct link_encoder*) ; 
 int /*<<< orphan*/  TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS ; 
 int /*<<< orphan*/  link_transmitter_control (struct dce110_link_encoder*,struct bp_transmitter_control*) ; 

void dce110_link_encoder_dp_set_lane_settings(
	struct link_encoder *enc,
	const struct link_training_settings *link_settings)
{
	struct dce110_link_encoder *enc110 = TO_DCE110_LINK_ENC(enc);
	union dpcd_training_lane_set training_lane_set = { { 0 } };
	int32_t lane = 0;
	struct bp_transmitter_control cntl = { 0 };

	if (!link_settings) {
		BREAK_TO_DEBUGGER();
		return;
	}

	cntl.action = TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS;
	cntl.transmitter = enc110->base.transmitter;
	cntl.connector_obj_id = enc110->base.connector;
	cntl.lanes_number = link_settings->link_settings.lane_count;
	cntl.hpd_sel = enc110->base.hpd_source;
	cntl.pixel_clock = link_settings->link_settings.link_rate *
						LINK_RATE_REF_FREQ_IN_KHZ;

	for (lane = 0; lane < link_settings->link_settings.lane_count; lane++) {
		/* translate lane settings */

		training_lane_set.bits.VOLTAGE_SWING_SET =
			link_settings->lane_settings[lane].VOLTAGE_SWING;
		training_lane_set.bits.PRE_EMPHASIS_SET =
			link_settings->lane_settings[lane].PRE_EMPHASIS;

		/* post cursor 2 setting only applies to HBR2 link rate */
		if (link_settings->link_settings.link_rate == LINK_RATE_HIGH2) {
			/* this is passed to VBIOS
			 * to program post cursor 2 level */

			training_lane_set.bits.POST_CURSOR2_SET =
				link_settings->lane_settings[lane].POST_CURSOR2;
		}

		cntl.lane_select = lane;
		cntl.lane_settings = training_lane_set.raw;

		/* call VBIOS table to set voltage swing and pre-emphasis */
		link_transmitter_control(enc110, &cntl);
	}
}