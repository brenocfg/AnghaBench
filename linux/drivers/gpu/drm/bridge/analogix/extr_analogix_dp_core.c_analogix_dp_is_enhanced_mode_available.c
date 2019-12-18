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
struct analogix_dp_device {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCD_ENHANCED_FRAME_CAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_MAX_LANE_COUNT ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int analogix_dp_is_enhanced_mode_available(struct analogix_dp_device *dp,
						  u8 *enhanced_mode_support)
{
	u8 data;
	int ret;

	ret = drm_dp_dpcd_readb(&dp->aux, DP_MAX_LANE_COUNT, &data);
	if (ret != 1) {
		*enhanced_mode_support = 0;
		return ret;
	}

	*enhanced_mode_support = DPCD_ENHANCED_FRAME_CAP(data);

	return 0;
}