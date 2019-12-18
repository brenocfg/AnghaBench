#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int link_rate; int link_spread; int /*<<< orphan*/  lane_count; } ;
struct link_training_settings {TYPE_2__* lane_settings; TYPE_1__ link_settings; } ;
struct dc_link {int dummy; } ;
typedef  enum link_training_result { ____Placeholder_link_training_result } link_training_result ;
struct TYPE_4__ {int /*<<< orphan*/  PRE_EMPHASIS; int /*<<< orphan*/  VOLTAGE_SWING; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_MSG_LT (struct dc_link*,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
#define  LINK_RATE_HIGH 142 
#define  LINK_RATE_HIGH2 141 
#define  LINK_RATE_HIGH3 140 
#define  LINK_RATE_LOW 139 
#define  LINK_RATE_RBR2 138 
#define  LINK_SPREAD_05_DOWNSPREAD_30KHZ 137 
#define  LINK_SPREAD_05_DOWNSPREAD_33KHZ 136 
#define  LINK_SPREAD_DISABLED 135 
#define  LINK_TRAINING_CR_FAIL_LANE0 134 
#define  LINK_TRAINING_CR_FAIL_LANE1 133 
#define  LINK_TRAINING_CR_FAIL_LANE23 132 
#define  LINK_TRAINING_EQ_FAIL_CR 131 
#define  LINK_TRAINING_EQ_FAIL_EQ 130 
#define  LINK_TRAINING_LQA_FAIL 129 
#define  LINK_TRAINING_SUCCESS 128 

__attribute__((used)) static void print_status_message(
	struct dc_link *link,
	const struct link_training_settings *lt_settings,
	enum link_training_result status)
{
	char *link_rate = "Unknown";
	char *lt_result = "Unknown";
	char *lt_spread = "Disabled";

	switch (lt_settings->link_settings.link_rate) {
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

	switch (lt_settings->link_settings.link_spread) {
	case LINK_SPREAD_DISABLED:
		lt_spread = "Disabled";
		break;
	case LINK_SPREAD_05_DOWNSPREAD_30KHZ:
		lt_spread = "0.5% 30KHz";
		break;
	case LINK_SPREAD_05_DOWNSPREAD_33KHZ:
		lt_spread = "0.5% 33KHz";
		break;
	default:
		break;
	}

	/* Connectivity log: link training */
	CONN_MSG_LT(link, "%sx%d %s VS=%d, PE=%d, DS=%s",
				link_rate,
				lt_settings->link_settings.lane_count,
				lt_result,
				lt_settings->lane_settings[0].VOLTAGE_SWING,
				lt_settings->lane_settings[0].PRE_EMPHASIS,
				lt_spread);
}