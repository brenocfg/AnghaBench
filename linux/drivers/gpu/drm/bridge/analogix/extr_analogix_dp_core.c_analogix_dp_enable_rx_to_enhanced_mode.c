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
 int DPCD_LANE_COUNT_SET (int /*<<< orphan*/ ) ; 
 int DP_LANE_COUNT_ENHANCED_FRAME_EN ; 
 int /*<<< orphan*/  DP_LANE_COUNT_SET ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
analogix_dp_enable_rx_to_enhanced_mode(struct analogix_dp_device *dp,
				       bool enable)
{
	u8 data;
	int ret;

	ret = drm_dp_dpcd_readb(&dp->aux, DP_LANE_COUNT_SET, &data);
	if (ret != 1)
		return ret;

	if (enable)
		ret = drm_dp_dpcd_writeb(&dp->aux, DP_LANE_COUNT_SET,
					 DP_LANE_COUNT_ENHANCED_FRAME_EN |
					 DPCD_LANE_COUNT_SET(data));
	else
		ret = drm_dp_dpcd_writeb(&dp->aux, DP_LANE_COUNT_SET,
					 DPCD_LANE_COUNT_SET(data));

	return ret < 0 ? ret : 0;
}