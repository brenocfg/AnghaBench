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
struct v4l2_subdev {int dummy; } ;
struct csi_state {int flags; TYPE_1__* pdev; int /*<<< orphan*/  lock; scalar_t__ debug; int /*<<< orphan*/  src_sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ST_STREAMING ; 
 int ST_SUSPENDED ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  mipi_csis_clear_counters (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_log_counters (struct csi_state*,int) ; 
 int /*<<< orphan*/  mipi_csis_start_stream (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_stop_stream (struct csi_state*) ; 
 struct csi_state* mipi_sd_to_csis_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_power ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int mipi_csis_s_stream(struct v4l2_subdev *mipi_sd, int enable)
{
	struct csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	int ret = 0;

	if (enable) {
		mipi_csis_clear_counters(state);
		ret = pm_runtime_get_sync(&state->pdev->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(&state->pdev->dev);
			return ret;
		}
		ret = v4l2_subdev_call(state->src_sd, core, s_power, 1);
		if (ret < 0)
			return ret;
	}

	mutex_lock(&state->lock);
	if (enable) {
		if (state->flags & ST_SUSPENDED) {
			ret = -EBUSY;
			goto unlock;
		}

		mipi_csis_start_stream(state);
		ret = v4l2_subdev_call(state->src_sd, video, s_stream, 1);
		if (ret < 0)
			goto unlock;

		mipi_csis_log_counters(state, true);

		state->flags |= ST_STREAMING;
	} else {
		v4l2_subdev_call(state->src_sd, video, s_stream, 0);
		ret = v4l2_subdev_call(state->src_sd, core, s_power, 1);
		mipi_csis_stop_stream(state);
		state->flags &= ~ST_STREAMING;
		if (state->debug)
			mipi_csis_log_counters(state, true);
	}

unlock:
	mutex_unlock(&state->lock);
	if (!enable)
		pm_runtime_put(&state->pdev->dev);

	return ret;
}