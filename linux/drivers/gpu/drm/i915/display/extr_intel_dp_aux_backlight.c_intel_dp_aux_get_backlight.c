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
typedef  int u32 ;
typedef  int u16 ;
struct intel_dp {int* edp_dpcd; int /*<<< orphan*/  aux; } ;
struct intel_connector {TYPE_1__* encoder; } ;
typedef  int /*<<< orphan*/  read_val ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int DP_EDP_BACKLIGHT_BRIGHTNESS_BYTE_COUNT ; 
 int /*<<< orphan*/  DP_EDP_BACKLIGHT_BRIGHTNESS_MSB ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int**,int) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 intel_dp_aux_get_backlight(struct intel_connector *connector)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&connector->encoder->base);
	u8 read_val[2] = { 0x0 };
	u16 level = 0;

	if (drm_dp_dpcd_read(&intel_dp->aux, DP_EDP_BACKLIGHT_BRIGHTNESS_MSB,
			     &read_val, sizeof(read_val)) < 0) {
		DRM_DEBUG_KMS("Failed to read DPCD register 0x%x\n",
			      DP_EDP_BACKLIGHT_BRIGHTNESS_MSB);
		return 0;
	}
	level = read_val[0];
	if (intel_dp->edp_dpcd[2] & DP_EDP_BACKLIGHT_BRIGHTNESS_BYTE_COUNT)
		level = (read_val[0] << 8 | read_val[1]);

	return level;
}