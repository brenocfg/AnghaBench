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
struct sharp_panel {int /*<<< orphan*/  base; } ;
struct mipi_dsi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mipi_dsi_detach (struct mipi_dsi_device*) ; 
 struct sharp_panel* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  sharp_panel_del (struct sharp_panel*) ; 
 int sharp_panel_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sharp_panel_remove(struct mipi_dsi_device *dsi)
{
	struct sharp_panel *sharp = mipi_dsi_get_drvdata(dsi);
	int err;

	/* only detach from host for the DSI-LINK2 interface */
	if (!sharp) {
		mipi_dsi_detach(dsi);
		return 0;
	}

	err = sharp_panel_disable(&sharp->base);
	if (err < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", err);

	err = mipi_dsi_detach(dsi);
	if (err < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", err);

	sharp_panel_del(sharp);

	return 0;
}