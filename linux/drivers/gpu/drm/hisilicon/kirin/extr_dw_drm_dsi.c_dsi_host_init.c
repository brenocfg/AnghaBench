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
struct mipi_dsi_host {int /*<<< orphan*/ * ops; struct device* dev; } ;
struct dw_dsi {struct mipi_dsi_host host; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  dsi_host_ops ; 
 int mipi_dsi_host_register (struct mipi_dsi_host*) ; 

__attribute__((used)) static int dsi_host_init(struct device *dev, struct dw_dsi *dsi)
{
	struct mipi_dsi_host *host = &dsi->host;
	int ret;

	host->dev = dev;
	host->ops = &dsi_host_ops;
	ret = mipi_dsi_host_register(host);
	if (ret) {
		DRM_ERROR("failed to register dsi host\n");
		return ret;
	}

	return 0;
}