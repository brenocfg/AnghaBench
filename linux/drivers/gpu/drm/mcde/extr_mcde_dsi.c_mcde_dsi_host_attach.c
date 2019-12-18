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
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int lanes; int mode_flags; int /*<<< orphan*/  format; } ;
struct mcde_dsi {TYPE_1__* mcde; struct mipi_dsi_device* mdsi; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct mipi_dsi_device* mdsi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,...) ; 
 struct mcde_dsi* host_to_mcde_dsi (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  mipi_dsi_pixel_format_to_bpp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcde_dsi_host_attach(struct mipi_dsi_host *host,
				struct mipi_dsi_device *mdsi)
{
	struct mcde_dsi *d = host_to_mcde_dsi(host);

	if (mdsi->lanes < 1 || mdsi->lanes > 2) {
		DRM_ERROR("dsi device params invalid, 1 or 2 lanes supported\n");
		return -EINVAL;
	}

	dev_info(d->dev, "attached DSI device with %d lanes\n", mdsi->lanes);
	/* MIPI_DSI_FMT_RGB88 etc */
	dev_info(d->dev, "format %08x, %dbpp\n", mdsi->format,
		 mipi_dsi_pixel_format_to_bpp(mdsi->format));
	dev_info(d->dev, "mode flags: %08lx\n", mdsi->mode_flags);

	d->mdsi = mdsi;
	if (d->mcde)
		d->mcde->mdsi = mdsi;

	return 0;
}