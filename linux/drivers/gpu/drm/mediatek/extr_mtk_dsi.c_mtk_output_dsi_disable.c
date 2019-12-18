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
struct mtk_dsi {int enabled; scalar_t__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ drm_panel_disable (scalar_t__) ; 
 int /*<<< orphan*/  mtk_dsi_poweroff (struct mtk_dsi*) ; 

__attribute__((used)) static void mtk_output_dsi_disable(struct mtk_dsi *dsi)
{
	if (!dsi->enabled)
		return;

	if (dsi->panel) {
		if (drm_panel_disable(dsi->panel)) {
			DRM_ERROR("failed to disable the panel\n");
			return;
		}
	}

	mtk_dsi_poweroff(dsi);

	dsi->enabled = false;
}