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
struct intel_dp {scalar_t__* dpcd; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 size_t DP_DPCD_REV ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,scalar_t__*) ; 
 scalar_t__ drm_dp_dpcd_read (int /*<<< orphan*/ *,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  intel_dp_extended_receiver_capabilities (struct intel_dp*) ; 

bool
intel_dp_read_dpcd(struct intel_dp *intel_dp)
{
	if (drm_dp_dpcd_read(&intel_dp->aux, 0x000, intel_dp->dpcd,
			     sizeof(intel_dp->dpcd)) < 0)
		return false; /* aux transfer failed */

	intel_dp_extended_receiver_capabilities(intel_dp);

	DRM_DEBUG_KMS("DPCD: %*ph\n", (int) sizeof(intel_dp->dpcd), intel_dp->dpcd);

	return intel_dp->dpcd[DP_DPCD_REV] != 0;
}