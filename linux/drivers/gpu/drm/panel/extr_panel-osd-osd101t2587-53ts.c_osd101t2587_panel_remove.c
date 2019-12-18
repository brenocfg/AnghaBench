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
struct osd101t2587_panel {int /*<<< orphan*/  base; } ;
struct mipi_dsi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int mipi_dsi_detach (struct mipi_dsi_device*) ; 
 struct osd101t2587_panel* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 
 int osd101t2587_panel_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd101t2587_panel_unprepare (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int osd101t2587_panel_remove(struct mipi_dsi_device *dsi)
{
	struct osd101t2587_panel *osd101t2587 = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = osd101t2587_panel_disable(&osd101t2587->base);
	if (ret < 0)
		dev_warn(&dsi->dev, "failed to disable panel: %d\n", ret);

	osd101t2587_panel_unprepare(&osd101t2587->base);

	drm_panel_remove(&osd101t2587->base);

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", ret);

	return ret;
}