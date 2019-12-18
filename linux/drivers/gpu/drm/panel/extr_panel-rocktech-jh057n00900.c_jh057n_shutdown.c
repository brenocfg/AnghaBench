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
struct jh057n {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,int) ; 
 int drm_panel_disable (int /*<<< orphan*/ *) ; 
 int drm_panel_unprepare (int /*<<< orphan*/ *) ; 
 struct jh057n* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 

__attribute__((used)) static void jh057n_shutdown(struct mipi_dsi_device *dsi)
{
	struct jh057n *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = drm_panel_unprepare(&ctx->panel);
	if (ret < 0)
		DRM_DEV_ERROR(&dsi->dev, "Failed to unprepare panel: %d\n",
			      ret);

	ret = drm_panel_disable(&ctx->panel);
	if (ret < 0)
		DRM_DEV_ERROR(&dsi->dev, "Failed to disable panel: %d\n",
			      ret);
}