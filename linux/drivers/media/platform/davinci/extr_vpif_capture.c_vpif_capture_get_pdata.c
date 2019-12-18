#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct vpif_subdev_info {int /*<<< orphan*/  name; } ;
struct vpif_capture_config {unsigned int* asd_sizes; unsigned int subdev_count; char* card_name; int /*<<< orphan*/ * asd; struct vpif_capture_chan_config* chan_config; struct vpif_subdev_info* subdev_info; } ;
struct TYPE_17__ {int hd_pol; int vd_pol; } ;
struct vpif_capture_chan_config {TYPE_6__ vpif_if; TYPE_3__* inputs; int /*<<< orphan*/  input_count; } ;
struct TYPE_15__ {unsigned int flags; int /*<<< orphan*/  bus_width; } ;
struct TYPE_16__ {TYPE_4__ parallel; } ;
struct v4l2_fwnode_endpoint {TYPE_5__ bus; int /*<<< orphan*/  bus_type; } ;
struct v4l2_async_subdev {int dummy; } ;
struct TYPE_19__ {scalar_t__ of_node; struct vpif_capture_config* platform_data; TYPE_1__* parent; } ;
struct platform_device {TYPE_8__ dev; } ;
struct device_node {int /*<<< orphan*/  full_name; } ;
struct TYPE_18__ {int /*<<< orphan*/  notifier; } ;
struct TYPE_13__ {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  std; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {TYPE_2__ input; } ;
struct TYPE_12__ {scalar_t__ of_node; } ;

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
 unsigned int VPIF_CAPTURE_NUM_CHANNELS ; 
 int /*<<< orphan*/  dev_dbg (TYPE_8__*,char*,struct device_node*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_8__*,char*) ; 
 void* devm_kcalloc (TYPE_8__*,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct vpif_capture_config* devm_kzalloc (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (scalar_t__,struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_add_fwnode_subdev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (int /*<<< orphan*/ *) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 
 TYPE_7__ vpif_obj ; 

__attribute__((used)) static struct vpif_capture_config *
vpif_capture_get_pdata(struct platform_device *pdev)
{
	struct device_node *endpoint = NULL;
	struct device_node *rem = NULL;
	struct vpif_capture_config *pdata;
	struct vpif_subdev_info *sdinfo;
	struct vpif_capture_chan_config *chan;
	unsigned int i;

	v4l2_async_notifier_init(&vpif_obj.notifier);

	/*
	 * DT boot: OF node from parent device contains
	 * video ports & endpoints data.
	 */
	if (pdev->dev.parent && pdev->dev.parent->of_node)
		pdev->dev.of_node = pdev->dev.parent->of_node;
	if (!IS_ENABLED(CONFIG_OF) || !pdev->dev.of_node)
		return pdev->dev.platform_data;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;
	pdata->subdev_info =
		devm_kcalloc(&pdev->dev,
			     VPIF_CAPTURE_NUM_CHANNELS,
			     sizeof(*pdata->subdev_info),
			     GFP_KERNEL);

	if (!pdata->subdev_info)
		return NULL;

	for (i = 0; i < VPIF_CAPTURE_NUM_CHANNELS; i++) {
		struct v4l2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
		unsigned int flags;
		int err;

		endpoint = of_graph_get_next_endpoint(pdev->dev.of_node,
						      endpoint);
		if (!endpoint)
			break;

		rem = of_graph_get_remote_port_parent(endpoint);
		if (!rem) {
			dev_dbg(&pdev->dev, "Remote device at %pOF not found\n",
				endpoint);
			goto done;
		}

		sdinfo = &pdata->subdev_info[i];
		chan = &pdata->chan_config[i];
		chan->inputs = devm_kcalloc(&pdev->dev,
					    VPIF_CAPTURE_NUM_CHANNELS,
					    sizeof(*chan->inputs),
					    GFP_KERNEL);
		if (!chan->inputs)
			goto err_cleanup;

		chan->input_count++;
		chan->inputs[i].input.type = V4L2_INPUT_TYPE_CAMERA;
		chan->inputs[i].input.std = V4L2_STD_ALL;
		chan->inputs[i].input.capabilities = V4L2_IN_CAP_STD;

		err = v4l2_fwnode_endpoint_parse(of_fwnode_handle(endpoint),
						 &bus_cfg);
		if (err) {
			dev_err(&pdev->dev, "Could not parse the endpoint\n");
			of_node_put(rem);
			goto done;
		}

		dev_dbg(&pdev->dev, "Endpoint %pOF, bus_width = %d\n",
			endpoint, bus_cfg.bus.parallel.bus_width);

		flags = bus_cfg.bus.parallel.flags;

		if (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
			chan->vpif_if.hd_pol = 1;

		if (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
			chan->vpif_if.vd_pol = 1;

		dev_dbg(&pdev->dev, "Remote device %pOF found\n", rem);
		sdinfo->name = rem->full_name;

		pdata->asd[i] = v4l2_async_notifier_add_fwnode_subdev(
			&vpif_obj.notifier, of_fwnode_handle(rem),
			sizeof(struct v4l2_async_subdev));
		if (IS_ERR(pdata->asd[i]))
			goto err_cleanup;

		of_node_put(rem);
	}

done:
	of_node_put(endpoint);
	pdata->asd_sizes[0] = i;
	pdata->subdev_count = i;
	pdata->card_name = "DA850/OMAP-L138 Video Capture";

	return pdata;

err_cleanup:
	of_node_put(rem);
	of_node_put(endpoint);
	v4l2_async_notifier_cleanup(&vpif_obj.notifier);

	return NULL;
}