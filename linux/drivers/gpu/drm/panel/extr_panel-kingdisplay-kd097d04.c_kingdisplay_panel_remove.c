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
struct mipi_dsi_device {int /*<<< orphan*/  dev; } ;
struct kingdisplay_panel {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kingdisplay_panel_del (struct kingdisplay_panel*) ; 
 int kingdisplay_panel_disable (int /*<<< orphan*/ *) ; 
 int kingdisplay_panel_unprepare (int /*<<< orphan*/ *) ; 
 int mipi_dsi_detach (struct mipi_dsi_device*) ; 
 struct kingdisplay_panel* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 

__attribute__((used)) static int kingdisplay_panel_remove(struct mipi_dsi_device *dsi)
{
	struct kingdisplay_panel *kingdisplay = mipi_dsi_get_drvdata(dsi);
	int err;

	err = kingdisplay_panel_unprepare(&kingdisplay->base);
	if (err < 0)
		DRM_DEV_ERROR(&dsi->dev, "failed to unprepare panel: %d\n",
			      err);

	err = kingdisplay_panel_disable(&kingdisplay->base);
	if (err < 0)
		DRM_DEV_ERROR(&dsi->dev, "failed to disable panel: %d\n", err);

	err = mipi_dsi_detach(dsi);
	if (err < 0)
		DRM_DEV_ERROR(&dsi->dev, "failed to detach from DSI host: %d\n",
			      err);

	kingdisplay_panel_del(kingdisplay);

	return 0;
}