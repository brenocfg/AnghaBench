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
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device {int lanes; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; } ;
struct dw_dsi {int lanes; int /*<<< orphan*/  mode_flags; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 struct dw_dsi* host_to_dsi (struct mipi_dsi_host*) ; 

__attribute__((used)) static int dsi_host_attach(struct mipi_dsi_host *host,
			   struct mipi_dsi_device *mdsi)
{
	struct dw_dsi *dsi = host_to_dsi(host);

	if (mdsi->lanes < 1 || mdsi->lanes > 4) {
		DRM_ERROR("dsi device params invalid\n");
		return -EINVAL;
	}

	dsi->lanes = mdsi->lanes;
	dsi->format = mdsi->format;
	dsi->mode_flags = mdsi->mode_flags;

	return 0;
}