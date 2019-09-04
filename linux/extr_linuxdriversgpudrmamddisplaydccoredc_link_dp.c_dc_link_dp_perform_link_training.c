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
struct TYPE_6__ {int /*<<< orphan*/  lane_count; int /*<<< orphan*/  link_rate; int /*<<< orphan*/  link_spread; } ;
struct link_training_settings {TYPE_2__* lane_settings; TYPE_1__ link_settings; } ;
struct dc_link_settings {int /*<<< orphan*/  lane_count; int /*<<< orphan*/  link_rate; } ;
struct dc_link {TYPE_5__* ctx; scalar_t__ dp_ss_off; } ;
typedef  int /*<<< orphan*/  lt_settings ;
typedef  enum link_training_result { ____Placeholder_link_training_result } link_training_result ;
struct TYPE_10__ {TYPE_4__* dc; } ;
struct TYPE_8__ {int /*<<< orphan*/  ltFailCount; } ;
struct TYPE_9__ {TYPE_3__ debug_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  PRE_EMPHASIS; int /*<<< orphan*/  VOLTAGE_SWING; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_MSG_LT (struct dc_link*,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  LINK_RATE_HIGH 139 
#define  LINK_RATE_HIGH2 138 
#define  LINK_RATE_HIGH3 137 
#define  LINK_RATE_LOW 136 
#define  LINK_RATE_RBR2 135 
 int /*<<< orphan*/  LINK_SPREAD_05_DOWNSPREAD_30KHZ ; 
 int /*<<< orphan*/  LINK_SPREAD_DISABLED ; 
#define  LINK_TRAINING_CR_FAIL_LANE0 134 
#define  LINK_TRAINING_CR_FAIL_LANE1 133 
#define  LINK_TRAINING_CR_FAIL_LANE23 132 
#define  LINK_TRAINING_EQ_FAIL_CR 131 
#define  LINK_TRAINING_EQ_FAIL_EQ 130 
#define  LINK_TRAINING_LQA_FAIL 129 
#define  LINK_TRAINING_SUCCESS 128 
 int /*<<< orphan*/  dpcd_set_link_settings (struct dc_link*,struct link_training_settings*) ; 
 int /*<<< orphan*/  memset (struct link_training_settings*,char,int) ; 
 int perform_channel_equalization_sequence (struct dc_link*,struct link_training_settings*) ; 
 int perform_clock_recovery_sequence (struct dc_link*,struct link_training_settings*) ; 
 int perform_link_training_int (struct dc_link*,struct link_training_settings*,int) ; 

enum link_training_result dc_link_dp_perform_link_training(
	struct dc_link *link,
	const struct dc_link_settings *link_setting,
	bool skip_video_pattern)
{
	enum link_training_result status = LINK_TRAINING_SUCCESS;

	char *link_rate = "Unknown";
	char *lt_result = "Unknown";

	struct link_training_settings lt_settings;

	memset(&lt_settings, '\0', sizeof(lt_settings));

	lt_settings.link_settings.link_rate = link_setting->link_rate;
	lt_settings.link_settings.lane_count = link_setting->lane_count;

	/*@todo[vdevulap] move SS to LS, should not be handled by displaypath*/

	/* TODO hard coded to SS for now
	 * lt_settings.link_settings.link_spread =
	 * dal_display_path_is_ss_supported(
	 * path_mode->display_path) ?
	 * LINK_SPREAD_05_DOWNSPREAD_30KHZ :
	 * LINK_SPREAD_DISABLED;
	 */
	if (link->dp_ss_off)
		lt_settings.link_settings.link_spread = LINK_SPREAD_DISABLED;
	else
		lt_settings.link_settings.link_spread = LINK_SPREAD_05_DOWNSPREAD_30KHZ;

	/* 1. set link rate, lane count and spread*/
	dpcd_set_link_settings(link, &lt_settings);

	/* 2. perform link training (set link training done
	 *  to false is done as well)*/
	status = perform_clock_recovery_sequence(link, &lt_settings);
	if (status == LINK_TRAINING_SUCCESS) {
		status = perform_channel_equalization_sequence(link,
				&lt_settings);
	}

	if ((status == LINK_TRAINING_SUCCESS) || !skip_video_pattern) {
		status = perform_link_training_int(link,
				&lt_settings,
				status);
	}

	/* 6. print status message*/
	switch (lt_settings.link_settings.link_rate) {

	case LINK_RATE_LOW:
		link_rate = "RBR";
		break;
	case LINK_RATE_HIGH:
		link_rate = "HBR";
		break;
	case LINK_RATE_HIGH2:
		link_rate = "HBR2";
		break;
	case LINK_RATE_RBR2:
		link_rate = "RBR2";
		break;
	case LINK_RATE_HIGH3:
		link_rate = "HBR3";
		break;
	default:
		break;
	}

	switch (status) {
	case LINK_TRAINING_SUCCESS:
		lt_result = "pass";
		break;
	case LINK_TRAINING_CR_FAIL_LANE0:
		lt_result = "CR failed lane0";
		break;
	case LINK_TRAINING_CR_FAIL_LANE1:
		lt_result = "CR failed lane1";
		break;
	case LINK_TRAINING_CR_FAIL_LANE23:
		lt_result = "CR failed lane23";
		break;
	case LINK_TRAINING_EQ_FAIL_CR:
		lt_result = "CR failed in EQ";
		break;
	case LINK_TRAINING_EQ_FAIL_EQ:
		lt_result = "EQ failed";
		break;
	case LINK_TRAINING_LQA_FAIL:
		lt_result = "LQA failed";
		break;
	default:
		break;
	}

	/* Connectivity log: link training */
	CONN_MSG_LT(link, "%sx%d %s VS=%d, PE=%d",
			link_rate,
			lt_settings.link_settings.lane_count,
			lt_result,
			lt_settings.lane_settings[0].VOLTAGE_SWING,
			lt_settings.lane_settings[0].PRE_EMPHASIS);

	if (status != LINK_TRAINING_SUCCESS)
		link->ctx->dc->debug_data.ltFailCount++;

	return status;
}