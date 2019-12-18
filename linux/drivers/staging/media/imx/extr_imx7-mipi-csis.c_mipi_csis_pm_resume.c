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
struct v4l2_subdev {int dummy; } ;
struct device {int dummy; } ;
struct csi_state {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  mipi_phy_regulator; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ST_POWERED ; 
 int ST_STREAMING ; 
 int ST_SUSPENDED ; 
 struct v4l2_subdev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mipi_csis_clk_enable (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_start_stream (struct csi_state*) ; 
 struct csi_state* mipi_sd_to_csis_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mipi_csis_pm_resume(struct device *dev, bool runtime)
{
	struct v4l2_subdev *mipi_sd = dev_get_drvdata(dev);
	struct csi_state *state = mipi_sd_to_csis_state(mipi_sd);
	int ret = 0;

	mutex_lock(&state->lock);
	if (!runtime && !(state->flags & ST_SUSPENDED))
		goto unlock;

	if (!(state->flags & ST_POWERED)) {
		ret = regulator_enable(state->mipi_phy_regulator);
		if (ret)
			goto unlock;

		state->flags |= ST_POWERED;
		mipi_csis_clk_enable(state);
	}
	if (state->flags & ST_STREAMING)
		mipi_csis_start_stream(state);

	state->flags &= ~ST_SUSPENDED;

unlock:
	mutex_unlock(&state->lock);

	return ret ? -EAGAIN : 0;
}