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
struct analogix_dp_device {int panel_is_modeset; int /*<<< orphan*/  panel_lock; TYPE_1__* plat_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 int drm_panel_prepare (int /*<<< orphan*/ ) ; 
 int drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int analogix_dp_prepare_panel(struct analogix_dp_device *dp,
				     bool prepare, bool is_modeset_prepare)
{
	int ret = 0;

	if (!dp->plat_data->panel)
		return 0;

	mutex_lock(&dp->panel_lock);

	/*
	 * Exit early if this is a temporary prepare/unprepare and we're already
	 * modeset (since we neither want to prepare twice or unprepare early).
	 */
	if (dp->panel_is_modeset && !is_modeset_prepare)
		goto out;

	if (prepare)
		ret = drm_panel_prepare(dp->plat_data->panel);
	else
		ret = drm_panel_unprepare(dp->plat_data->panel);

	if (ret)
		goto out;

	if (is_modeset_prepare)
		dp->panel_is_modeset = prepare;

out:
	mutex_unlock(&dp->panel_lock);
	return ret;
}