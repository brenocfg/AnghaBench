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
struct mipi_dsi_device_info {char* type; int /*<<< orphan*/ * node; int /*<<< orphan*/  channel; } ;
struct mipi_dsi_device {int mode_flags; int /*<<< orphan*/  format; int /*<<< orphan*/  lanes; } ;
struct device {int dummy; } ;
struct adv7511 {int /*<<< orphan*/  num_dsi_lanes; struct mipi_dsi_device* dsi; int /*<<< orphan*/  host_node; TYPE_1__* i2c_main; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  MIPI_DSI_FMT_RGB888 ; 
 int MIPI_DSI_MODE_EOT_PACKET ; 
 int MIPI_DSI_MODE_VIDEO ; 
 int MIPI_DSI_MODE_VIDEO_HSE ; 
 int MIPI_DSI_MODE_VIDEO_SYNC_PULSE ; 
 int PTR_ERR (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int mipi_dsi_attach (struct mipi_dsi_device*) ; 
 struct mipi_dsi_device* mipi_dsi_device_register_full (struct mipi_dsi_host*,struct mipi_dsi_device_info const*) ; 
 int /*<<< orphan*/  mipi_dsi_device_unregister (struct mipi_dsi_device*) ; 
 struct mipi_dsi_host* of_find_mipi_dsi_host_by_node (int /*<<< orphan*/ ) ; 

int adv7533_attach_dsi(struct adv7511 *adv)
{
	struct device *dev = &adv->i2c_main->dev;
	struct mipi_dsi_host *host;
	struct mipi_dsi_device *dsi;
	int ret = 0;
	const struct mipi_dsi_device_info info = { .type = "adv7533",
						   .channel = 0,
						   .node = NULL,
						 };

	host = of_find_mipi_dsi_host_by_node(adv->host_node);
	if (!host) {
		dev_err(dev, "failed to find dsi host\n");
		return -EPROBE_DEFER;
	}

	dsi = mipi_dsi_device_register_full(host, &info);
	if (IS_ERR(dsi)) {
		dev_err(dev, "failed to create dsi device\n");
		ret = PTR_ERR(dsi);
		goto err_dsi_device;
	}

	adv->dsi = dsi;

	dsi->lanes = adv->num_dsi_lanes;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			  MIPI_DSI_MODE_EOT_PACKET | MIPI_DSI_MODE_VIDEO_HSE;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "failed to attach dsi to host\n");
		goto err_dsi_attach;
	}

	return 0;

err_dsi_attach:
	mipi_dsi_device_unregister(dsi);
err_dsi_device:
	return ret;
}