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
typedef  int /*<<< orphan*/  tmds_oen ;
struct i2c_adapter {int dummy; } ;
typedef  int ssize_t ;
typedef  enum drm_dp_dual_mode_type { ____Placeholder_drm_dp_dual_mode_type } drm_dp_dual_mode_type ;

/* Variables and functions */
 int DP_DUAL_MODE_TMDS_DISABLE ; 
 int /*<<< orphan*/  DP_DUAL_MODE_TMDS_OEN ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int DRM_DP_DUAL_MODE_TYPE2_DVI ; 
 int drm_dp_dual_mode_read (struct i2c_adapter*,int /*<<< orphan*/ ,int*,int) ; 

int drm_dp_dual_mode_get_tmds_output(enum drm_dp_dual_mode_type type,
				     struct i2c_adapter *adapter,
				     bool *enabled)
{
	uint8_t tmds_oen;
	ssize_t ret;

	if (type < DRM_DP_DUAL_MODE_TYPE2_DVI) {
		*enabled = true;
		return 0;
	}

	ret = drm_dp_dual_mode_read(adapter, DP_DUAL_MODE_TMDS_OEN,
				    &tmds_oen, sizeof(tmds_oen));
	if (ret) {
		DRM_DEBUG_KMS("Failed to query state of TMDS output buffers\n");
		return ret;
	}

	*enabled = !(tmds_oen & DP_DUAL_MODE_TMDS_DISABLE);

	return 0;
}