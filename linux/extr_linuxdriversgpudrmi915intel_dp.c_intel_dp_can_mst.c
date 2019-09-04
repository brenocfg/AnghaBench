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
typedef  int u8 ;
struct intel_dp {int* dpcd; int /*<<< orphan*/  aux; int /*<<< orphan*/  can_mst; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_dp_mst; } ;

/* Variables and functions */
 size_t DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_MSTM_CAP ; 
 int DP_MST_CAP ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__ i915_modparams ; 

__attribute__((used)) static bool
intel_dp_can_mst(struct intel_dp *intel_dp)
{
	u8 mstm_cap;

	if (!i915_modparams.enable_dp_mst)
		return false;

	if (!intel_dp->can_mst)
		return false;

	if (intel_dp->dpcd[DP_DPCD_REV] < 0x12)
		return false;

	if (drm_dp_dpcd_readb(&intel_dp->aux, DP_MSTM_CAP, &mstm_cap) != 1)
		return false;

	return mstm_cap & DP_MST_CAP;
}