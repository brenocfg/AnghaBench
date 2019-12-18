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
struct mipi_dsi_device {int dummy; } ;
struct kingdisplay_panel {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  kingdisplay_panel_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kingdisplay_panel_unprepare (int /*<<< orphan*/ *) ; 
 struct kingdisplay_panel* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 

__attribute__((used)) static void kingdisplay_panel_shutdown(struct mipi_dsi_device *dsi)
{
	struct kingdisplay_panel *kingdisplay = mipi_dsi_get_drvdata(dsi);

	kingdisplay_panel_unprepare(&kingdisplay->base);
	kingdisplay_panel_disable(&kingdisplay->base);
}