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
typedef  int u8 ;
struct intel_dp {int* dpcd; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 size_t DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_MSTM_CAP ; 
 int DP_MST_CAP ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool
intel_dp_sink_can_mst(struct intel_dp *intel_dp)
{
	u8 mstm_cap;

	if (intel_dp->dpcd[DP_DPCD_REV] < 0x12)
		return false;

	if (drm_dp_dpcd_readb(&intel_dp->aux, DP_MSTM_CAP, &mstm_cap) != 1)
		return false;

	return mstm_cap & DP_MST_CAP;
}