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
struct mipi_dsi_host {struct device* dev; } ;
struct mipi_dsi_device_info {int channel; int /*<<< orphan*/  type; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct mipi_dsi_device {int channel; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mipi_dsi_device* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct mipi_dsi_device*) ; 
 int PTR_ERR (struct mipi_dsi_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  kfree (struct mipi_dsi_device*) ; 
 int mipi_dsi_device_add (struct mipi_dsi_device*) ; 
 struct mipi_dsi_device* mipi_dsi_device_alloc (struct mipi_dsi_host*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct mipi_dsi_device *
mipi_dsi_device_register_full(struct mipi_dsi_host *host,
			      const struct mipi_dsi_device_info *info)
{
	struct mipi_dsi_device *dsi;
	struct device *dev = host->dev;
	int ret;

	if (!info) {
		dev_err(dev, "invalid mipi_dsi_device_info pointer\n");
		return ERR_PTR(-EINVAL);
	}

	if (info->channel > 3) {
		dev_err(dev, "invalid virtual channel: %u\n", info->channel);
		return ERR_PTR(-EINVAL);
	}

	dsi = mipi_dsi_device_alloc(host);
	if (IS_ERR(dsi)) {
		dev_err(dev, "failed to allocate DSI device %ld\n",
			PTR_ERR(dsi));
		return dsi;
	}

	dsi->dev.of_node = info->node;
	dsi->channel = info->channel;
	strlcpy(dsi->name, info->type, sizeof(dsi->name));

	ret = mipi_dsi_device_add(dsi);
	if (ret) {
		dev_err(dev, "failed to add DSI device %d\n", ret);
		kfree(dsi);
		return ERR_PTR(ret);
	}

	return dsi;
}