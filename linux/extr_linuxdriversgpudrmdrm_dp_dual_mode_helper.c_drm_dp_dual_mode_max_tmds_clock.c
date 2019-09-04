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
typedef  int uint8_t ;
struct i2c_adapter {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  max_tmds_clock ;
typedef  enum drm_dp_dual_mode_type { ____Placeholder_drm_dp_dual_mode_type } drm_dp_dual_mode_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DUAL_MODE_MAX_TMDS_CLOCK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int DRM_DP_DUAL_MODE_NONE ; 
 int DRM_DP_DUAL_MODE_TYPE2_DVI ; 
 scalar_t__ drm_dp_dual_mode_read (struct i2c_adapter*,int /*<<< orphan*/ ,int*,int) ; 

int drm_dp_dual_mode_max_tmds_clock(enum drm_dp_dual_mode_type type,
				    struct i2c_adapter *adapter)
{
	uint8_t max_tmds_clock;
	ssize_t ret;

	/* native HDMI so no limit */
	if (type == DRM_DP_DUAL_MODE_NONE)
		return 0;

	/*
	 * Type 1 adaptors are limited to 165MHz
	 * Type 2 adaptors can tells us their limit
	 */
	if (type < DRM_DP_DUAL_MODE_TYPE2_DVI)
		return 165000;

	ret = drm_dp_dual_mode_read(adapter, DP_DUAL_MODE_MAX_TMDS_CLOCK,
				    &max_tmds_clock, sizeof(max_tmds_clock));
	if (ret || max_tmds_clock == 0x00 || max_tmds_clock == 0xff) {
		DRM_DEBUG_KMS("Failed to query max TMDS clock\n");
		return 165000;
	}

	return max_tmds_clock * 5000 / 2;
}