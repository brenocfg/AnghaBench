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
struct edp_ctrl {int /*<<< orphan*/  dpcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_link_train_channel_eq_delay (int /*<<< orphan*/ ) ; 
 int edp_train_pattern_set_write (struct edp_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int edp_clear_training_pattern(struct edp_ctrl *ctrl)
{
	int ret;

	ret = edp_train_pattern_set_write(ctrl, 0);

	drm_dp_link_train_channel_eq_delay(ctrl->dpcd);

	return ret;
}