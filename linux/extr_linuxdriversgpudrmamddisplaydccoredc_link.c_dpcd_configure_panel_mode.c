#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int PANEL_MODE_EDP; } ;
union dpcd_edp_config {int /*<<< orphan*/  raw; TYPE_1__ bits; } ;
struct TYPE_5__ {int /*<<< orphan*/  panel_mode_edp; } ;
struct dc_link {TYPE_2__ dpcd_caps; int /*<<< orphan*/  link_index; TYPE_3__* ctx; } ;
typedef  enum dp_panel_mode { ____Placeholder_dp_panel_mode } dp_panel_mode ;
typedef  enum ddc_result { ____Placeholder_ddc_result } ddc_result ;
struct TYPE_6__ {int /*<<< orphan*/  logger; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_DETECTION_DP_CAPS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int DDC_RESULT_SUCESSFULL ; 
 int DDC_RESULT_UNKNOWN ; 
 int /*<<< orphan*/  DP_EDP_CONFIGURATION_SET ; 
 int DP_PANEL_MODE_DEFAULT ; 
#define  DP_PANEL_MODE_EDP 129 
#define  DP_PANEL_MODE_SPECIAL 128 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int core_link_write_dpcd (struct dc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (union dpcd_edp_config*,char,int) ; 

__attribute__((used)) static void dpcd_configure_panel_mode(
	struct dc_link *link,
	enum dp_panel_mode panel_mode)
{
	union dpcd_edp_config edp_config_set;
	bool panel_mode_edp = false;
	DC_LOGGER_INIT(link->ctx->logger);

	memset(&edp_config_set, '\0', sizeof(union dpcd_edp_config));

	if (DP_PANEL_MODE_DEFAULT != panel_mode) {

		switch (panel_mode) {
		case DP_PANEL_MODE_EDP:
		case DP_PANEL_MODE_SPECIAL:
			panel_mode_edp = true;
			break;

		default:
			break;
		}

		/*set edp panel mode in receiver*/
		core_link_read_dpcd(
			link,
			DP_EDP_CONFIGURATION_SET,
			&edp_config_set.raw,
			sizeof(edp_config_set.raw));

		if (edp_config_set.bits.PANEL_MODE_EDP
			!= panel_mode_edp) {
			enum ddc_result result = DDC_RESULT_UNKNOWN;

			edp_config_set.bits.PANEL_MODE_EDP =
			panel_mode_edp;
			result = core_link_write_dpcd(
				link,
				DP_EDP_CONFIGURATION_SET,
				&edp_config_set.raw,
				sizeof(edp_config_set.raw));

			ASSERT(result == DDC_RESULT_SUCESSFULL);
		}
	}
	DC_LOG_DETECTION_DP_CAPS("Link: %d eDP panel mode supported: %d "
			"eDP panel mode enabled: %d \n",
			link->link_index,
			link->dpcd_caps.panel_mode_edp,
			panel_mode_edp);
}