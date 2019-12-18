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
struct TYPE_2__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct rpi_touchscreen {TYPE_1__ base; int /*<<< orphan*/  dsi; struct i2c_client* i2c; } ;
struct mipi_dsi_host {int dummy; } ;
struct mipi_dsi_device_info {int /*<<< orphan*/ * node; int /*<<< orphan*/  channel; int /*<<< orphan*/  type; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ID ; 
 int /*<<< orphan*/  REG_POWERON ; 
 int /*<<< orphan*/  RPI_DSI_DRIVER_NAME ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct rpi_touchscreen* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rpi_touchscreen*) ; 
 int /*<<< orphan*/  mipi_dsi_device_register_full (struct mipi_dsi_host*,struct mipi_dsi_device_info*) ; 
 struct mipi_dsi_host* of_find_mipi_dsi_host_by_node (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_graph_get_remote_port (struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  rpi_touchscreen_funcs ; 
 int rpi_touchscreen_i2c_read (struct rpi_touchscreen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpi_touchscreen_i2c_write (struct rpi_touchscreen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpi_touchscreen_probe(struct i2c_client *i2c,
				 const struct i2c_device_id *id)
{
	struct device *dev = &i2c->dev;
	struct rpi_touchscreen *ts;
	struct device_node *endpoint, *dsi_host_node;
	struct mipi_dsi_host *host;
	int ret, ver;
	struct mipi_dsi_device_info info = {
		.type = RPI_DSI_DRIVER_NAME,
		.channel = 0,
		.node = NULL,
	};

	ts = devm_kzalloc(dev, sizeof(*ts), GFP_KERNEL);
	if (!ts)
		return -ENOMEM;

	i2c_set_clientdata(i2c, ts);

	ts->i2c = i2c;

	ver = rpi_touchscreen_i2c_read(ts, REG_ID);
	if (ver < 0) {
		dev_err(dev, "Atmel I2C read failed: %d\n", ver);
		return -ENODEV;
	}

	switch (ver) {
	case 0xde: /* ver 1 */
	case 0xc3: /* ver 2 */
		break;
	default:
		dev_err(dev, "Unknown Atmel firmware revision: 0x%02x\n", ver);
		return -ENODEV;
	}

	/* Turn off at boot, so we can cleanly sequence powering on. */
	rpi_touchscreen_i2c_write(ts, REG_POWERON, 0);

	/* Look up the DSI host.  It needs to probe before we do. */
	endpoint = of_graph_get_next_endpoint(dev->of_node, NULL);
	if (!endpoint)
		return -ENODEV;

	dsi_host_node = of_graph_get_remote_port_parent(endpoint);
	if (!dsi_host_node)
		goto error;

	host = of_find_mipi_dsi_host_by_node(dsi_host_node);
	of_node_put(dsi_host_node);
	if (!host) {
		of_node_put(endpoint);
		return -EPROBE_DEFER;
	}

	info.node = of_graph_get_remote_port(endpoint);
	if (!info.node)
		goto error;

	of_node_put(endpoint);

	ts->dsi = mipi_dsi_device_register_full(host, &info);
	if (IS_ERR(ts->dsi)) {
		dev_err(dev, "DSI device registration failed: %ld\n",
			PTR_ERR(ts->dsi));
		return PTR_ERR(ts->dsi);
	}

	ts->base.dev = dev;
	ts->base.funcs = &rpi_touchscreen_funcs;

	/* This appears last, as it's what will unblock the DSI host
	 * driver's component bind function.
	 */
	ret = drm_panel_add(&ts->base);
	if (ret)
		return ret;

	return 0;

error:
	of_node_put(endpoint);
	return -ENODEV;
}