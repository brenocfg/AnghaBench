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
struct analogix_dp_device {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int DP_LINK_SCRAMBLING_DISABLE ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int /*<<< orphan*/  analogix_dp_disable_scrambling (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_enable_scrambling (struct analogix_dp_device*) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int analogix_dp_enable_scramble(struct analogix_dp_device *dp,
				       bool enable)
{
	u8 data;
	int ret;

	if (enable) {
		analogix_dp_enable_scrambling(dp);

		ret = drm_dp_dpcd_readb(&dp->aux, DP_TRAINING_PATTERN_SET,
					&data);
		if (ret != 1)
			return ret;
		ret = drm_dp_dpcd_writeb(&dp->aux, DP_TRAINING_PATTERN_SET,
				   (u8)(data & ~DP_LINK_SCRAMBLING_DISABLE));
	} else {
		analogix_dp_disable_scrambling(dp);

		ret = drm_dp_dpcd_readb(&dp->aux, DP_TRAINING_PATTERN_SET,
					&data);
		if (ret != 1)
			return ret;
		ret = drm_dp_dpcd_writeb(&dp->aux, DP_TRAINING_PATTERN_SET,
				   (u8)(data | DP_LINK_SCRAMBLING_DISABLE));
	}
	return ret < 0 ? ret : 0;
}