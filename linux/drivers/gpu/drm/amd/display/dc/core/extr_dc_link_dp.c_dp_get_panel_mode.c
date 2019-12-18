#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int branch_dev_id; scalar_t__ panel_mode_edp; int /*<<< orphan*/  branch_dev_name; } ;
struct dc_link {scalar_t__ connector_signal; TYPE_1__ dpcd_caps; } ;
typedef  enum dp_panel_mode { ____Placeholder_dp_panel_mode } dp_panel_mode ;

/* Variables and functions */
#define  DP_BRANCH_DEVICE_ID_00001A 129 
#define  DP_BRANCH_DEVICE_ID_0022B9 128 
 int DP_PANEL_MODE_DEFAULT ; 
 int DP_PANEL_MODE_EDP ; 
 int DP_PANEL_MODE_SPECIAL ; 
 int /*<<< orphan*/  DP_VGA_LVDS_CONVERTER_ID_2 ; 
 int /*<<< orphan*/  DP_VGA_LVDS_CONVERTER_ID_3 ; 
 scalar_t__ SIGNAL_TYPE_DISPLAY_PORT ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

enum dp_panel_mode dp_get_panel_mode(struct dc_link *link)
{
	/* We need to explicitly check that connector
	 * is not DP. Some Travis_VGA get reported
	 * by video bios as DP.
	 */
	if (link->connector_signal != SIGNAL_TYPE_DISPLAY_PORT) {

		switch (link->dpcd_caps.branch_dev_id) {
		case DP_BRANCH_DEVICE_ID_0022B9:
			/* alternate scrambler reset is required for Travis
			 * for the case when external chip does not
			 * provide sink device id, alternate scrambler
			 * scheme will  be overriden later by querying
			 * Encoder features
			 */
			if (strncmp(
				link->dpcd_caps.branch_dev_name,
				DP_VGA_LVDS_CONVERTER_ID_2,
				sizeof(
				link->dpcd_caps.
				branch_dev_name)) == 0) {
					return DP_PANEL_MODE_SPECIAL;
			}
			break;
		case DP_BRANCH_DEVICE_ID_00001A:
			/* alternate scrambler reset is required for Travis
			 * for the case when external chip does not provide
			 * sink device id, alternate scrambler scheme will
			 * be overriden later by querying Encoder feature
			 */
			if (strncmp(link->dpcd_caps.branch_dev_name,
				DP_VGA_LVDS_CONVERTER_ID_3,
				sizeof(
				link->dpcd_caps.
				branch_dev_name)) == 0) {
					return DP_PANEL_MODE_SPECIAL;
			}
			break;
		default:
			break;
		}
	}

	if (link->dpcd_caps.panel_mode_edp) {
		return DP_PANEL_MODE_EDP;
	}

	return DP_PANEL_MODE_DEFAULT;
}