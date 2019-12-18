#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ MAX_DOWN_SPREAD; } ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
union max_down_spread {scalar_t__ raw; TYPE_6__ bits; TYPE_2__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  LANE_COUNT_SET; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
union lane_count_set {scalar_t__ raw; TYPE_3__ bits; TYPE_1__ member_0; } ;
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int use_link_rate_set; int /*<<< orphan*/  link_spread; scalar_t__ link_rate; scalar_t__ link_rate_set; int /*<<< orphan*/  lane_count; } ;
struct TYPE_10__ {scalar_t__ edp_supported_link_rates_count; scalar_t__* edp_supported_link_rates; } ;
struct dc_link {TYPE_5__ cur_link_settings; TYPE_4__ dpcd_caps; } ;
typedef  int /*<<< orphan*/  max_down_spread ;
typedef  int /*<<< orphan*/  link_rate_set ;
typedef  int /*<<< orphan*/  link_bw_set ;
typedef  int /*<<< orphan*/  lane_count_set ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;

/* Variables and functions */
 int DC_ERROR_UNEXPECTED ; 
 int DC_OK ; 
 int /*<<< orphan*/  DP_LANE_COUNT_SET ; 
 int /*<<< orphan*/  DP_LINK_BW_SET ; 
 int /*<<< orphan*/  DP_LINK_RATE_SET ; 
 int /*<<< orphan*/  DP_MAX_DOWNSPREAD ; 
 int /*<<< orphan*/  LINK_SPREAD_05_DOWNSPREAD_30KHZ ; 
 int /*<<< orphan*/  LINK_SPREAD_DISABLED ; 
 int core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void read_edp_current_link_settings_on_detect(struct dc_link *link)
{
	union lane_count_set lane_count_set = { {0} };
	uint8_t link_bw_set;
	uint8_t link_rate_set;
	uint32_t read_dpcd_retry_cnt = 10;
	enum dc_status status = DC_ERROR_UNEXPECTED;
	int i;
	union max_down_spread max_down_spread = { {0} };

	// Read DPCD 00101h to find out the number of lanes currently set
	for (i = 0; i < read_dpcd_retry_cnt; i++) {
		status = core_link_read_dpcd(
				link,
				DP_LANE_COUNT_SET,
				&lane_count_set.raw,
				sizeof(lane_count_set));
		/* First DPCD read after VDD ON can fail if the particular board
		 * does not have HPD pin wired correctly. So if DPCD read fails,
		 * which it should never happen, retry a few times. Target worst
		 * case scenario of 80 ms.
		 */
		if (status == DC_OK) {
			link->cur_link_settings.lane_count = lane_count_set.bits.LANE_COUNT_SET;
			break;
		}

		msleep(8);
	}

	// Read DPCD 00100h to find if standard link rates are set
	core_link_read_dpcd(link, DP_LINK_BW_SET,
			&link_bw_set, sizeof(link_bw_set));

	if (link_bw_set == 0) {
		/* If standard link rates are not being used,
		 * Read DPCD 00115h to find the link rate set used
		 */
		core_link_read_dpcd(link, DP_LINK_RATE_SET,
				&link_rate_set, sizeof(link_rate_set));

		if (link_rate_set < link->dpcd_caps.edp_supported_link_rates_count) {
			link->cur_link_settings.link_rate =
				link->dpcd_caps.edp_supported_link_rates[link_rate_set];
			link->cur_link_settings.link_rate_set = link_rate_set;
			link->cur_link_settings.use_link_rate_set = true;
		}
	} else {
		link->cur_link_settings.link_rate = link_bw_set;
		link->cur_link_settings.use_link_rate_set = false;
	}
	// Read DPCD 00003h to find the max down spread.
	core_link_read_dpcd(link, DP_MAX_DOWNSPREAD,
			&max_down_spread.raw, sizeof(max_down_spread));
	link->cur_link_settings.link_spread =
		max_down_spread.bits.MAX_DOWN_SPREAD ?
		LINK_SPREAD_05_DOWNSPREAD_30KHZ : LINK_SPREAD_DISABLED;
}