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
struct wuxga_nt_panel {int /*<<< orphan*/  base; } ;
struct mipi_dsi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int mipi_dsi_detach (struct mipi_dsi_device*) ; 
 struct wuxga_nt_panel* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  wuxga_nt_panel_del (struct wuxga_nt_panel*) ; 
 int wuxga_nt_panel_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wuxga_nt_panel_remove(struct mipi_dsi_device *dsi)
{
	struct wuxga_nt_panel *wuxga_nt = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = wuxga_nt_panel_disable(&wuxga_nt->base);
	if (ret < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", ret);

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", ret);

	wuxga_nt_panel_del(wuxga_nt);

	return 0;
}