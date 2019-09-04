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
struct sharp_nt_panel {struct mipi_dsi_device* dsi; } ;
struct mipi_dsi_device {int lanes; int mode_flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int MIPI_DSI_MODE_EOT_PACKET ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int MIPI_DSI_MODE_VIDEO_HSE ; 
 struct sharp_nt_panel* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct sharp_nt_panel*) ; 
 int sharp_nt_panel_add (struct sharp_nt_panel*) ; 

__attribute__((used)) static int sharp_nt_panel_probe(struct mipi_dsi_device *dsi)
{
	struct sharp_nt_panel *sharp_nt;
	int ret;

	dsi->lanes = 2;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
			MIPI_DSI_MODE_VIDEO_HSE |
			MIPI_DSI_CLOCK_NON_CONTINUOUS |
			MIPI_DSI_MODE_EOT_PACKET;

	sharp_nt = devm_kzalloc(&dsi->dev, sizeof(*sharp_nt), GFP_KERNEL);
	if (!sharp_nt)
		return -ENOMEM;

	mipi_dsi_set_drvdata(dsi, sharp_nt);

	sharp_nt->dsi = dsi;

	ret = sharp_nt_panel_add(sharp_nt);
	if (ret < 0)
		return ret;

	return mipi_dsi_attach(dsi);
}