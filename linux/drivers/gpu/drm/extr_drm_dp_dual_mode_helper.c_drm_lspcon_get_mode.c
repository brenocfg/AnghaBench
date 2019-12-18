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
struct i2c_adapter {int dummy; } ;
typedef  enum drm_lspcon_mode { ____Placeholder_drm_lspcon_mode } drm_lspcon_mode ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DUAL_MODE_LSPCON_CURRENT_MODE ; 
 int DP_DUAL_MODE_LSPCON_MODE_PCON ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_LSPCON_MODE_LS ; 
 int DRM_LSPCON_MODE_PCON ; 
 int EFAULT ; 
 int EINVAL ; 
 int drm_dp_dual_mode_read (struct i2c_adapter*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int drm_lspcon_get_mode(struct i2c_adapter *adapter,
			enum drm_lspcon_mode *mode)
{
	u8 data;
	int ret = 0;
	int retry;

	if (!mode) {
		DRM_ERROR("NULL input\n");
		return -EINVAL;
	}

	/* Read Status: i2c over aux */
	for (retry = 0; retry < 6; retry++) {
		if (retry)
			usleep_range(500, 1000);

		ret = drm_dp_dual_mode_read(adapter,
					    DP_DUAL_MODE_LSPCON_CURRENT_MODE,
					    &data, sizeof(data));
		if (!ret)
			break;
	}

	if (ret < 0) {
		DRM_DEBUG_KMS("LSPCON read(0x80, 0x41) failed\n");
		return -EFAULT;
	}

	if (data & DP_DUAL_MODE_LSPCON_MODE_PCON)
		*mode = DRM_LSPCON_MODE_PCON;
	else
		*mode = DRM_LSPCON_MODE_LS;
	return 0;
}