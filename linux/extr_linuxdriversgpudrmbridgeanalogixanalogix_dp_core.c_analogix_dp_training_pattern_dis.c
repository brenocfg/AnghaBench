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
struct analogix_dp_device {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NONE ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_DISABLE ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int /*<<< orphan*/  analogix_dp_set_training_pattern (struct analogix_dp_device*,int /*<<< orphan*/ ) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int analogix_dp_training_pattern_dis(struct analogix_dp_device *dp)
{
	int ret;

	analogix_dp_set_training_pattern(dp, DP_NONE);

	ret = drm_dp_dpcd_writeb(&dp->aux, DP_TRAINING_PATTERN_SET,
				 DP_TRAINING_PATTERN_DISABLE);

	return ret < 0 ? ret : 0;
}