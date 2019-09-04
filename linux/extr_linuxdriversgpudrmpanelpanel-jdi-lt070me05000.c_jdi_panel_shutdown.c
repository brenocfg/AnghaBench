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
struct jdi_panel {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  jdi_panel_disable (int /*<<< orphan*/ *) ; 
 struct jdi_panel* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 

__attribute__((used)) static void jdi_panel_shutdown(struct mipi_dsi_device *dsi)
{
	struct jdi_panel *jdi = mipi_dsi_get_drvdata(dsi);

	jdi_panel_disable(&jdi->base);
}