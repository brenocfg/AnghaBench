#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* funcs; } ;
struct analogix_dp_device {int /*<<< orphan*/  clock; int /*<<< orphan*/  dev; int /*<<< orphan*/  aux; TYPE_2__* plat_data; TYPE_3__ connector; int /*<<< orphan*/  bridge; } ;
struct TYPE_5__ {scalar_t__ panel; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* destroy ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  analogix_dp_bridge_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_aux_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_detach (scalar_t__) ; 
 scalar_t__ drm_panel_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void analogix_dp_unbind(struct analogix_dp_device *dp)
{
	analogix_dp_bridge_disable(dp->bridge);
	dp->connector.funcs->destroy(&dp->connector);

	if (dp->plat_data->panel) {
		if (drm_panel_unprepare(dp->plat_data->panel))
			DRM_ERROR("failed to turnoff the panel\n");
		drm_panel_detach(dp->plat_data->panel);
	}

	drm_dp_aux_unregister(&dp->aux);
	pm_runtime_disable(dp->dev);
	clk_disable_unprepare(dp->clock);
}