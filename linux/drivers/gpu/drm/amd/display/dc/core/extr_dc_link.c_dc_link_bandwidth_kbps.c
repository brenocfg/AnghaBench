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
typedef  int uint32_t ;
struct dc_link_settings {int link_rate; int lane_count; } ;
struct TYPE_4__ {scalar_t__ FEC_CAPABLE; } ;
struct TYPE_5__ {TYPE_1__ bits; } ;
struct TYPE_6__ {TYPE_2__ fec_cap; } ;
struct dc_link {TYPE_3__ dpcd_caps; } ;

/* Variables and functions */
 long long BIT_ULL (int) ; 
 int LINK_RATE_REF_FREQ_IN_KHZ ; 
 int mul_u64_u32_shr (long long,int,int) ; 

uint32_t dc_link_bandwidth_kbps(
	const struct dc_link *link,
	const struct dc_link_settings *link_setting)
{
	uint32_t link_bw_kbps =
		link_setting->link_rate * LINK_RATE_REF_FREQ_IN_KHZ; /* bytes per sec */

	link_bw_kbps *= 8;   /* 8 bits per byte*/
	link_bw_kbps *= link_setting->lane_count;

#ifdef CONFIG_DRM_AMD_DC_DSC_SUPPORT
	if (link->dpcd_caps.fec_cap.bits.FEC_CAPABLE) {
		/* Account for FEC overhead.
		 * We have to do it based on caps,
		 * and not based on FEC being set ready,
		 * because FEC is set ready too late in
		 * the process to correctly be picked up
		 * by mode enumeration.
		 *
		 * There's enough zeros at the end of 'kbps'
		 * that make the below operation 100% precise
		 * for our purposes.
		 * 'long long' makes it work even for HDMI 2.1
		 * max bandwidth (and much, much bigger bandwidths
		 * than that, actually).
		 *
		 * NOTE: Reducing link BW by 3% may not be precise
		 * because it may be a stream BT that increases by 3%, and so
		 * 1/1.03 = 0.970873 factor should have been used instead,
		 * but the difference is minimal and is in a safe direction,
		 * which all works well around potential ambiguity of DP 1.4a spec.
		 */
		link_bw_kbps = mul_u64_u32_shr(BIT_ULL(32) * 970LL / 1000,
					       link_bw_kbps, 32);
	}
#endif

	return link_bw_kbps;

}