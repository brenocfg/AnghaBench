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
struct mipi_dsi_device {int dummy; } ;

/* Variables and functions */
 struct osd101t2587_panel* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  osd101t2587_panel_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd101t2587_panel_unprepare (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void osd101t2587_panel_shutdown(struct mipi_dsi_device *dsi)
{
	struct osd101t2587_panel *osd101t2587 = mipi_dsi_get_drvdata(dsi);

	osd101t2587_panel_disable(&osd101t2587->base);
	osd101t2587_panel_unprepare(&osd101t2587->base);
}