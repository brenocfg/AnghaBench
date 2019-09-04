#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_2__ bus; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_9__ {TYPE_3__ match; int /*<<< orphan*/  match_type; int /*<<< orphan*/  list; } ;
struct ceu_subdev {TYPE_4__ asd; int /*<<< orphan*/  mbus_flags; } ;
struct ceu_device {TYPE_4__** asds; struct ceu_subdev* subdevs; TYPE_5__* dev; } ;
struct TYPE_10__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 scalar_t__ V4L2_MBUS_PARALLEL ; 
 int ceu_init_async_subdevs (struct ceu_device*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  fwnode_graph_get_remote_port_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (struct device_node*,int /*<<< orphan*/ ,unsigned int) ; 
 int of_graph_get_endpoint_count (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int ceu_parse_dt(struct ceu_device *ceudev)
{
	struct device_node *of = ceudev->dev->of_node;
	struct v4l2_fwnode_endpoint fw_ep;
	struct ceu_subdev *ceu_sd;
	struct device_node *ep;
	unsigned int i;
	int num_ep;
	int ret;

	num_ep = of_graph_get_endpoint_count(of);
	if (!num_ep)
		return -ENODEV;

	ret = ceu_init_async_subdevs(ceudev, num_ep);
	if (ret)
		return ret;

	for (i = 0; i < num_ep; i++) {
		ep = of_graph_get_endpoint_by_regs(of, 0, i);
		if (!ep) {
			dev_err(ceudev->dev,
				"No subdevice connected on endpoint %u.\n", i);
			ret = -ENODEV;
			goto error_put_node;
		}

		ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(ep), &fw_ep);
		if (ret) {
			dev_err(ceudev->dev,
				"Unable to parse endpoint #%u.\n", i);
			goto error_put_node;
		}

		if (fw_ep.bus_type != V4L2_MBUS_PARALLEL) {
			dev_err(ceudev->dev,
				"Only parallel input supported.\n");
			ret = -EINVAL;
			goto error_put_node;
		}

		/* Setup the ceu subdevice and the async subdevice. */
		ceu_sd = &ceudev->subdevs[i];
		INIT_LIST_HEAD(&ceu_sd->asd.list);

		ceu_sd->mbus_flags = fw_ep.bus.parallel.flags;
		ceu_sd->asd.match_type = V4L2_ASYNC_MATCH_FWNODE;
		ceu_sd->asd.match.fwnode =
			fwnode_graph_get_remote_port_parent(
					of_fwnode_handle(ep));

		ceudev->asds[i] = &ceu_sd->asd;
		of_node_put(ep);
	}

	return num_ep;

error_put_node:
	of_node_put(ep);
	return ret;
}