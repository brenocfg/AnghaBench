#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int if_type; int bus_width; int hdpol; int vdpol; } ;
struct vpfe_subdev_info {TYPE_4__ vpfe_param; int /*<<< orphan*/ * routes; scalar_t__ can_route; TYPE_1__* inputs; scalar_t__ grp_id; } ;
struct vpfe_device {int /*<<< orphan*/  notifier; struct device* pdev; } ;
struct vpfe_config {int /*<<< orphan*/ * asd; struct vpfe_subdev_info* sub_devs; } ;
struct TYPE_6__ {int bus_width; unsigned int flags; } ;
struct TYPE_7__ {TYPE_2__ parallel; } ;
struct v4l2_fwnode_endpoint {TYPE_3__ bus; int /*<<< orphan*/  bus_type; } ;
struct v4l2_async_subdev {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; struct vpfe_config* platform_data; } ;
struct TYPE_5__ {unsigned int index; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  std; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_INPUT_TYPE_CAMERA ; 
 int /*<<< orphan*/  V4L2_IN_CAP_STD ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int VPFE_RAW_BAYER ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct vpfe_config* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (int /*<<< orphan*/ ,struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  v4l2_async_notifier_add_fwnode_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (int /*<<< orphan*/ *) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static struct vpfe_config *
vpfe_get_pdata(struct vpfe_device *vpfe)
{
	struct device_node *endpoint = NULL;
	struct device *dev = vpfe->pdev;
	struct vpfe_subdev_info *sdinfo;
	struct vpfe_config *pdata;
	unsigned int flags;
	unsigned int i;
	int err;

	dev_dbg(dev, "vpfe_get_pdata\n");

	v4l2_async_notifier_init(&vpfe->notifier);

	if (!IS_ENABLED(CONFIG_OF) || !dev->of_node)
		return dev->platform_data;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	for (i = 0; ; i++) {
		struct v4l2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
		struct device_node *rem;

		endpoint = of_graph_get_next_endpoint(dev->of_node, endpoint);
		if (!endpoint)
			break;

		sdinfo = &pdata->sub_devs[i];
		sdinfo->grp_id = 0;

		/* we only support camera */
		sdinfo->inputs[0].index = i;
		strscpy(sdinfo->inputs[0].name, "Camera",
			sizeof(sdinfo->inputs[0].name));
		sdinfo->inputs[0].type = V4L2_INPUT_TYPE_CAMERA;
		sdinfo->inputs[0].std = V4L2_STD_ALL;
		sdinfo->inputs[0].capabilities = V4L2_IN_CAP_STD;

		sdinfo->can_route = 0;
		sdinfo->routes = NULL;

		of_property_read_u32(endpoint, "ti,am437x-vpfe-interface",
				     &sdinfo->vpfe_param.if_type);
		if (sdinfo->vpfe_param.if_type < 0 ||
			sdinfo->vpfe_param.if_type > 4) {
			sdinfo->vpfe_param.if_type = VPFE_RAW_BAYER;
		}

		err = v4l2_fwnode_endpoint_parse(of_fwnode_handle(endpoint),
						 &bus_cfg);
		if (err) {
			dev_err(dev, "Could not parse the endpoint\n");
			goto cleanup;
		}

		sdinfo->vpfe_param.bus_width = bus_cfg.bus.parallel.bus_width;

		if (sdinfo->vpfe_param.bus_width < 8 ||
			sdinfo->vpfe_param.bus_width > 16) {
			dev_err(dev, "Invalid bus width.\n");
			goto cleanup;
		}

		flags = bus_cfg.bus.parallel.flags;

		if (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
			sdinfo->vpfe_param.hdpol = 1;

		if (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
			sdinfo->vpfe_param.vdpol = 1;

		rem = of_graph_get_remote_port_parent(endpoint);
		if (!rem) {
			dev_err(dev, "Remote device at %pOF not found\n",
				endpoint);
			goto cleanup;
		}

		pdata->asd[i] = v4l2_async_notifier_add_fwnode_subdev(
			&vpfe->notifier, of_fwnode_handle(rem),
			sizeof(struct v4l2_async_subdev));
		of_node_put(rem);
		if (IS_ERR(pdata->asd[i]))
			goto cleanup;
	}

	of_node_put(endpoint);
	return pdata;

cleanup:
	v4l2_async_notifier_cleanup(&vpfe->notifier);
	of_node_put(endpoint);
	return NULL;
}