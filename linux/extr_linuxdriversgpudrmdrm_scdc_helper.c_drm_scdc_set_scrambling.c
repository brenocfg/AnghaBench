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

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  SCDC_SCRAMBLING_ENABLE ; 
 int /*<<< orphan*/  SCDC_TMDS_CONFIG ; 
 int drm_scdc_readb (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_scdc_writeb (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool drm_scdc_set_scrambling(struct i2c_adapter *adapter, bool enable)
{
	u8 config;
	int ret;

	ret = drm_scdc_readb(adapter, SCDC_TMDS_CONFIG, &config);
	if (ret < 0) {
		DRM_DEBUG_KMS("Failed to read TMDS config: %d\n", ret);
		return false;
	}

	if (enable)
		config |= SCDC_SCRAMBLING_ENABLE;
	else
		config &= ~SCDC_SCRAMBLING_ENABLE;

	ret = drm_scdc_writeb(adapter, SCDC_TMDS_CONFIG, config);
	if (ret < 0) {
		DRM_DEBUG_KMS("Failed to enable scrambling: %d\n", ret);
		return false;
	}

	return true;
}