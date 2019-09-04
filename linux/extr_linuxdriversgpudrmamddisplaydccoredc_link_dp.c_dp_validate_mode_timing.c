#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct dc_link_settings {int dummy; } ;
struct dc_link {struct dc_link_settings verified_link_cap; } ;
struct dc_crtc_timing {scalar_t__ pix_clk_khz; scalar_t__ h_addressable; scalar_t__ v_addressable; } ;

/* Variables and functions */
 scalar_t__ bandwidth_in_kbps_from_link_settings (struct dc_link_settings const*) ; 
 scalar_t__ bandwidth_in_kbps_from_timing (struct dc_crtc_timing const*) ; 

bool dp_validate_mode_timing(
	struct dc_link *link,
	const struct dc_crtc_timing *timing)
{
	uint32_t req_bw;
	uint32_t max_bw;

	const struct dc_link_settings *link_setting;

	/*always DP fail safe mode*/
	if (timing->pix_clk_khz == (uint32_t) 25175 &&
		timing->h_addressable == (uint32_t) 640 &&
		timing->v_addressable == (uint32_t) 480)
		return true;

	/* We always use verified link settings */
	link_setting = &link->verified_link_cap;

	/* TODO: DYNAMIC_VALIDATION needs to be implemented */
	/*if (flags.DYNAMIC_VALIDATION == 1 &&
		link->verified_link_cap.lane_count != LANE_COUNT_UNKNOWN)
		link_setting = &link->verified_link_cap;
	*/

	req_bw = bandwidth_in_kbps_from_timing(timing);
	max_bw = bandwidth_in_kbps_from_link_settings(link_setting);

	if (req_bw <= max_bw) {
		/* remember the biggest mode here, during
		 * initial link training (to get
		 * verified_link_cap), LS sends event about
		 * cannot train at reported cap to upper
		 * layer and upper layer will re-enumerate modes.
		 * this is not necessary if the lower
		 * verified_link_cap is enough to drive
		 * all the modes */

		/* TODO: DYNAMIC_VALIDATION needs to be implemented */
		/* if (flags.DYNAMIC_VALIDATION == 1)
			dpsst->max_req_bw_for_verified_linkcap = dal_max(
				dpsst->max_req_bw_for_verified_linkcap, req_bw); */
		return true;
	} else
		return false;
}