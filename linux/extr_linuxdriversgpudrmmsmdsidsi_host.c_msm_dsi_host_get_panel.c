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
struct msm_dsi_host {unsigned long mode_flags; int /*<<< orphan*/  device_node; } ;
struct mipi_dsi_host {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 struct drm_panel* of_drm_find_panel (int /*<<< orphan*/ ) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

struct drm_panel *msm_dsi_host_get_panel(struct mipi_dsi_host *host,
				unsigned long *panel_flags)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	struct drm_panel *panel;

	panel = of_drm_find_panel(msm_host->device_node);
	if (panel_flags)
			*panel_flags = msm_host->mode_flags;

	return panel;
}