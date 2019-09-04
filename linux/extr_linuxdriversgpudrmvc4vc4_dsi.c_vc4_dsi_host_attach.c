#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc4_dsi {int lanes; int mode_flags; int divider; TYPE_1__* pdev; int /*<<< orphan*/  format; int /*<<< orphan*/  channel; } ;
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int lanes; int mode_flags; int format; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PFORMAT_RGB565 ; 
 int /*<<< orphan*/  DSI_PFORMAT_RGB666 ; 
 int /*<<< orphan*/  DSI_PFORMAT_RGB666_PACKED ; 
 int /*<<< orphan*/  DSI_PFORMAT_RGB888 ; 
#define  MIPI_DSI_FMT_RGB565 131 
#define  MIPI_DSI_FMT_RGB666 130 
#define  MIPI_DSI_FMT_RGB666_PACKED 129 
#define  MIPI_DSI_FMT_RGB888 128 
 int MIPI_DSI_MODE_VIDEO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct vc4_dsi* host_to_dsi (struct mipi_dsi_host*) ; 

__attribute__((used)) static int vc4_dsi_host_attach(struct mipi_dsi_host *host,
			       struct mipi_dsi_device *device)
{
	struct vc4_dsi *dsi = host_to_dsi(host);

	dsi->lanes = device->lanes;
	dsi->channel = device->channel;
	dsi->mode_flags = device->mode_flags;

	switch (device->format) {
	case MIPI_DSI_FMT_RGB888:
		dsi->format = DSI_PFORMAT_RGB888;
		dsi->divider = 24 / dsi->lanes;
		break;
	case MIPI_DSI_FMT_RGB666:
		dsi->format = DSI_PFORMAT_RGB666;
		dsi->divider = 24 / dsi->lanes;
		break;
	case MIPI_DSI_FMT_RGB666_PACKED:
		dsi->format = DSI_PFORMAT_RGB666_PACKED;
		dsi->divider = 18 / dsi->lanes;
		break;
	case MIPI_DSI_FMT_RGB565:
		dsi->format = DSI_PFORMAT_RGB565;
		dsi->divider = 16 / dsi->lanes;
		break;
	default:
		dev_err(&dsi->pdev->dev, "Unknown DSI format: %d.\n",
			dsi->format);
		return 0;
	}

	if (!(dsi->mode_flags & MIPI_DSI_MODE_VIDEO)) {
		dev_err(&dsi->pdev->dev,
			"Only VIDEO mode panels supported currently.\n");
		return 0;
	}

	return 0;
}