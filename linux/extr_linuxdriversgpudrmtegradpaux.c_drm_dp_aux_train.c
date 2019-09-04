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
struct drm_dp_link {unsigned int num_lanes; } ;
struct drm_dp_aux {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_EDP_CONFIGURATION_SET ; 
 int DP_LINK_STATUS_SIZE ; 
 int /*<<< orphan*/  DP_TRAINING_LANE0_SET ; 
#define  DP_TRAINING_PATTERN_1 129 
#define  DP_TRAINING_PATTERN_2 128 
 int DP_TRAINING_PATTERN_DISABLE ; 
 int DP_TRAINING_PATTERN_MASK ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int DP_TRAIN_MAX_PRE_EMPHASIS_REACHED ; 
 int DP_TRAIN_MAX_SWING_REACHED ; 
 int DP_TRAIN_PRE_EMPH_LEVEL_0 ; 
 int DP_TRAIN_VOLTAGE_SWING_LEVEL_0 ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_dp_channel_eq_ok (int*,unsigned int) ; 
 int /*<<< orphan*/  drm_dp_clock_recovery_ok (int*,unsigned int) ; 
 int drm_dp_dpcd_read_link_status (struct drm_dp_aux*,int*) ; 
 int drm_dp_dpcd_write (struct drm_dp_aux*,int /*<<< orphan*/ ,int*,unsigned int) ; 
 int drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int drm_dp_aux_train(struct drm_dp_aux *aux, struct drm_dp_link *link,
		     u8 pattern)
{
	u8 tp = pattern & DP_TRAINING_PATTERN_MASK;
	u8 status[DP_LINK_STATUS_SIZE], values[4];
	unsigned int i;
	int err;

	err = drm_dp_dpcd_writeb(aux, DP_TRAINING_PATTERN_SET, pattern);
	if (err < 0)
		return err;

	if (tp == DP_TRAINING_PATTERN_DISABLE)
		return 0;

	for (i = 0; i < link->num_lanes; i++)
		values[i] = DP_TRAIN_MAX_PRE_EMPHASIS_REACHED |
			    DP_TRAIN_PRE_EMPH_LEVEL_0 |
			    DP_TRAIN_MAX_SWING_REACHED |
			    DP_TRAIN_VOLTAGE_SWING_LEVEL_0;

	err = drm_dp_dpcd_write(aux, DP_TRAINING_LANE0_SET, values,
				link->num_lanes);
	if (err < 0)
		return err;

	usleep_range(500, 1000);

	err = drm_dp_dpcd_read_link_status(aux, status);
	if (err < 0)
		return err;

	switch (tp) {
	case DP_TRAINING_PATTERN_1:
		if (!drm_dp_clock_recovery_ok(status, link->num_lanes))
			return -EAGAIN;

		break;

	case DP_TRAINING_PATTERN_2:
		if (!drm_dp_channel_eq_ok(status, link->num_lanes))
			return -EAGAIN;

		break;

	default:
		dev_err(aux->dev, "unsupported training pattern %u\n", tp);
		return -EINVAL;
	}

	err = drm_dp_dpcd_writeb(aux, DP_EDP_CONFIGURATION_SET, 0);
	if (err < 0)
		return err;

	return 0;
}