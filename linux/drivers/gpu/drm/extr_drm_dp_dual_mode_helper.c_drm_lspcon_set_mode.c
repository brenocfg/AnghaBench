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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_adapter {int dummy; } ;
typedef  enum drm_lspcon_mode { ____Placeholder_drm_lspcon_mode } drm_lspcon_mode ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DUAL_MODE_LSPCON_MODE_CHANGE ; 
 int /*<<< orphan*/  DP_DUAL_MODE_LSPCON_MODE_PCON ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int DRM_LSPCON_MODE_LS ; 
 int DRM_LSPCON_MODE_PCON ; 
 int ETIMEDOUT ; 
 int drm_dp_dual_mode_write (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int drm_lspcon_get_mode (struct i2c_adapter*,int*) ; 
 int /*<<< orphan*/  msleep (int) ; 

int drm_lspcon_set_mode(struct i2c_adapter *adapter,
			enum drm_lspcon_mode mode)
{
	u8 data = 0;
	int ret;
	int time_out = 200;
	enum drm_lspcon_mode current_mode;

	if (mode == DRM_LSPCON_MODE_PCON)
		data = DP_DUAL_MODE_LSPCON_MODE_PCON;

	/* Change mode */
	ret = drm_dp_dual_mode_write(adapter, DP_DUAL_MODE_LSPCON_MODE_CHANGE,
				     &data, sizeof(data));
	if (ret < 0) {
		DRM_ERROR("LSPCON mode change failed\n");
		return ret;
	}

	/*
	 * Confirm mode change by reading the status bit.
	 * Sometimes, it takes a while to change the mode,
	 * so wait and retry until time out or done.
	 */
	do {
		ret = drm_lspcon_get_mode(adapter, &current_mode);
		if (ret) {
			DRM_ERROR("can't confirm LSPCON mode change\n");
			return ret;
		} else {
			if (current_mode != mode) {
				msleep(10);
				time_out -= 10;
			} else {
				DRM_DEBUG_KMS("LSPCON mode changed to %s\n",
						mode == DRM_LSPCON_MODE_LS ?
						"LS" : "PCON");
				return 0;
			}
		}
	} while (time_out);

	DRM_ERROR("LSPCON mode change timed out\n");
	return -ETIMEDOUT;
}