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
struct truly_nt35597 {int /*<<< orphan*/  panel; scalar_t__* dsi; } ;
struct mipi_dsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mipi_dsi_detach (scalar_t__) ; 
 int /*<<< orphan*/  mipi_dsi_device_unregister (scalar_t__) ; 
 struct truly_nt35597* mipi_dsi_get_drvdata (struct mipi_dsi_device*) ; 

__attribute__((used)) static int truly_nt35597_remove(struct mipi_dsi_device *dsi)
{
	struct truly_nt35597 *ctx = mipi_dsi_get_drvdata(dsi);

	if (ctx->dsi[0])
		mipi_dsi_detach(ctx->dsi[0]);
	if (ctx->dsi[1]) {
		mipi_dsi_detach(ctx->dsi[1]);
		mipi_dsi_device_unregister(ctx->dsi[1]);
	}

	drm_panel_remove(&ctx->panel);
	return 0;
}