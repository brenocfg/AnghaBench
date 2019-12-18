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
struct intel_dp {int lane_count; int /*<<< orphan*/  aux; int /*<<< orphan*/  train_set; } ;

/* Variables and functions */
 int DP_TRAINING_PATTERN_DISABLE ; 
 int DP_TRAINING_PATTERN_MASK ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int drm_dp_dpcd_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  intel_dp_program_link_training_pattern (struct intel_dp*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
intel_dp_set_link_train(struct intel_dp *intel_dp,
			u8 dp_train_pat)
{
	u8 buf[sizeof(intel_dp->train_set) + 1];
	int ret, len;

	intel_dp_program_link_training_pattern(intel_dp, dp_train_pat);

	buf[0] = dp_train_pat;
	if ((dp_train_pat & DP_TRAINING_PATTERN_MASK) ==
	    DP_TRAINING_PATTERN_DISABLE) {
		/* don't write DP_TRAINING_LANEx_SET on disable */
		len = 1;
	} else {
		/* DP_TRAINING_LANEx_SET follow DP_TRAINING_PATTERN_SET */
		memcpy(buf + 1, intel_dp->train_set, intel_dp->lane_count);
		len = intel_dp->lane_count + 1;
	}

	ret = drm_dp_dpcd_write(&intel_dp->aux, DP_TRAINING_PATTERN_SET,
				buf, len);

	return ret == len;
}