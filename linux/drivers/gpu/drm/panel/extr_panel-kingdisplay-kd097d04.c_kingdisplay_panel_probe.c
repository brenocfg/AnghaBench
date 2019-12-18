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
struct mipi_dsi_device {int lanes; int mode_flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  format; } ;
struct kingdisplay_panel {struct mipi_dsi_device* link; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int MIPI_DSI_MODE_LPM ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int MIPI_DSI_MODE_VIDEO_BURST ; 
 struct kingdisplay_panel* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int kingdisplay_panel_add (struct kingdisplay_panel*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  mipi_dsi_set_drvdata (struct mipi_dsi_device*,struct kingdisplay_panel*) ; 

__attribute__((used)) static int kingdisplay_panel_probe(struct mipi_dsi_device *dsi)
{
	struct kingdisplay_panel *kingdisplay;
	int err;

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM;

	kingdisplay = devm_kzalloc(&dsi->dev, sizeof(*kingdisplay), GFP_KERNEL);
	if (!kingdisplay)
		return -ENOMEM;

	mipi_dsi_set_drvdata(dsi, kingdisplay);
	kingdisplay->link = dsi;

	err = kingdisplay_panel_add(kingdisplay);
	if (err < 0)
		return err;

	return mipi_dsi_attach(dsi);
}