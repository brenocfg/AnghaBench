#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mipi_dsi_host {TYPE_1__* dev; } ;
struct mipi_dsi_device {int dummy; } ;
struct dw_mipi_dsi_plat_data {int /*<<< orphan*/  priv_data; TYPE_2__* host_ops; } ;
struct dw_mipi_dsi {int /*<<< orphan*/  bridge; struct dw_mipi_dsi_plat_data* plat_data; } ;
struct TYPE_4__ {int (* detach ) (int /*<<< orphan*/ ,struct mipi_dsi_device*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_of_panel_bridge_remove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct dw_mipi_dsi* host_to_dsi (struct mipi_dsi_host*) ; 
 int stub1 (int /*<<< orphan*/ ,struct mipi_dsi_device*) ; 

__attribute__((used)) static int dw_mipi_dsi_host_detach(struct mipi_dsi_host *host,
				   struct mipi_dsi_device *device)
{
	struct dw_mipi_dsi *dsi = host_to_dsi(host);
	const struct dw_mipi_dsi_plat_data *pdata = dsi->plat_data;
	int ret;

	if (pdata->host_ops && pdata->host_ops->detach) {
		ret = pdata->host_ops->detach(pdata->priv_data, device);
		if (ret < 0)
			return ret;
	}

	drm_of_panel_bridge_remove(host->dev->of_node, 1, 0);

	drm_bridge_remove(&dsi->bridge);

	return 0;
}