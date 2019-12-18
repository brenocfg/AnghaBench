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
struct csi_state {int flags; int /*<<< orphan*/  lock; scalar_t__ debug; } ;

/* Variables and functions */
 int ST_POWERED ; 
 int /*<<< orphan*/  mipi_csis_dump_regs (struct csi_state*) ; 
 int /*<<< orphan*/  mipi_csis_log_counters (struct csi_state*,int) ; 
 struct csi_state* mipi_sd_to_csis_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mipi_csis_log_status(struct v4l2_subdev *mipi_sd)
{
	struct csi_state *state = mipi_sd_to_csis_state(mipi_sd);

	mutex_lock(&state->lock);
	mipi_csis_log_counters(state, true);
	if (state->debug && (state->flags & ST_POWERED))
		mipi_csis_dump_regs(state);
	mutex_unlock(&state->lock);

	return 0;
}