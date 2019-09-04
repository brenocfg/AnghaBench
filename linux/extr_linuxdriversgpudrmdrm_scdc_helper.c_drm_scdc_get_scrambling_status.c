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

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  SCDC_SCRAMBLER_STATUS ; 
 int SCDC_SCRAMBLING_STATUS ; 
 int drm_scdc_readb (struct i2c_adapter*,int /*<<< orphan*/ ,int*) ; 

bool drm_scdc_get_scrambling_status(struct i2c_adapter *adapter)
{
	u8 status;
	int ret;

	ret = drm_scdc_readb(adapter, SCDC_SCRAMBLER_STATUS, &status);
	if (ret < 0) {
		DRM_DEBUG_KMS("Failed to read scrambling status: %d\n", ret);
		return false;
	}

	return status & SCDC_SCRAMBLING_STATUS;
}