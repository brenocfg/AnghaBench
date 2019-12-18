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
typedef  int /*<<< orphan*/  dpcd_ext ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DP13_DPCD_REV ; 
 size_t DP_DPCD_REV ; 
 int DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT ; 
 size_t DP_TRAINING_AUX_RD_INTERVAL ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int**,int) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void
intel_dp_extended_receiver_capabilities(struct intel_dp *intel_dp)
{
	u8 dpcd_ext[6];

	/*
	 * Prior to DP1.3 the bit represented by
	 * DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT was reserved.
	 * if it is set DP_DPCD_REV at 0000h could be at a value less than
	 * the true capability of the panel. The only way to check is to
	 * then compare 0000h and 2200h.
	 */
	if (!(intel_dp->dpcd[DP_TRAINING_AUX_RD_INTERVAL] &
	      DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT))
		return;

	if (drm_dp_dpcd_read(&intel_dp->aux, DP_DP13_DPCD_REV,
			     &dpcd_ext, sizeof(dpcd_ext)) != sizeof(dpcd_ext)) {
		DRM_ERROR("DPCD failed read at extended capabilities\n");
		return;
	}

	if (intel_dp->dpcd[DP_DPCD_REV] > dpcd_ext[DP_DPCD_REV]) {
		DRM_DEBUG_KMS("DPCD extended DPCD rev less than base DPCD rev\n");
		return;
	}

	if (!memcmp(intel_dp->dpcd, dpcd_ext, sizeof(dpcd_ext)))
		return;

	DRM_DEBUG_KMS("Base DPCD: %*ph\n",
		      (int)sizeof(intel_dp->dpcd), intel_dp->dpcd);

	memcpy(intel_dp->dpcd, dpcd_ext, sizeof(dpcd_ext));
}