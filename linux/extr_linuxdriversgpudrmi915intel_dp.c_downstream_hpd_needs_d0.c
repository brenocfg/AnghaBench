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
struct intel_dp {int* dpcd; int* downstream_ports; } ;

/* Variables and functions */
 size_t DP_DOWNSTREAMPORT_PRESENT ; 
 size_t DP_DPCD_REV ; 
 int DP_DS_PORT_HPD ; 
 int DP_DWN_STRM_PORT_PRESENT ; 

__attribute__((used)) static bool downstream_hpd_needs_d0(struct intel_dp *intel_dp)
{
	/*
	 * DPCD 1.2+ should support BRANCH_DEVICE_CTRL, and thus
	 * be capable of signalling downstream hpd with a long pulse.
	 * Whether or not that means D3 is safe to use is not clear,
	 * but let's assume so until proven otherwise.
	 *
	 * FIXME should really check all downstream ports...
	 */
	return intel_dp->dpcd[DP_DPCD_REV] == 0x11 &&
		intel_dp->dpcd[DP_DOWNSTREAMPORT_PRESENT] & DP_DWN_STRM_PORT_PRESENT &&
		intel_dp->downstream_ports[0] & DP_DS_PORT_HPD;
}