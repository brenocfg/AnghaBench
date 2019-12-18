#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  num_data_lanes; } ;
struct TYPE_11__ {TYPE_3__ mipi_csi2; } ;
struct TYPE_8__ {int /*<<< orphan*/  port; } ;
struct v4l2_fwnode_endpoint {TYPE_4__ bus; TYPE_1__ base; int /*<<< orphan*/  bus_type; } ;
struct TYPE_9__ {int /*<<< orphan*/  lanes; int /*<<< orphan*/  port; } ;
struct sensor_async_subdev {int /*<<< orphan*/  asd; TYPE_2__ csi2; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ops; } ;
struct cio2_device {TYPE_5__* pci_dev; TYPE_6__ notifier; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CIO2_NUM_PORTS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FWNODE_GRAPH_ENDPOINT_NEXT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  cio2_async_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_fwnode (int /*<<< orphan*/ *) ; 
 struct fwnode_handle* fwnode_graph_get_endpoint_by_id (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int /*<<< orphan*/  kfree (struct sensor_async_subdev*) ; 
 struct sensor_async_subdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_add_fwnode_remote_subdev (TYPE_6__*,struct fwnode_handle*,int /*<<< orphan*/ *) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int v4l2_fwnode_endpoint_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int cio2_parse_firmware(struct cio2_device *cio2)
{
	unsigned int i;
	int ret;

	for (i = 0; i < CIO2_NUM_PORTS; i++) {
		struct v4l2_fwnode_endpoint vep = {
			.bus_type = V4L2_MBUS_CSI2_DPHY
		};
		struct sensor_async_subdev *s_asd = NULL;
		struct fwnode_handle *ep;

		ep = fwnode_graph_get_endpoint_by_id(
			dev_fwnode(&cio2->pci_dev->dev), i, 0,
			FWNODE_GRAPH_ENDPOINT_NEXT);

		if (!ep)
			continue;

		ret = v4l2_fwnode_endpoint_parse(ep, &vep);
		if (ret)
			goto err_parse;

		s_asd = kzalloc(sizeof(*s_asd), GFP_KERNEL);
		if (!s_asd) {
			ret = -ENOMEM;
			goto err_parse;
		}

		s_asd->csi2.port = vep.base.port;
		s_asd->csi2.lanes = vep.bus.mipi_csi2.num_data_lanes;

		ret = v4l2_async_notifier_add_fwnode_remote_subdev(
			&cio2->notifier, ep, &s_asd->asd);
		if (ret)
			goto err_parse;

		fwnode_handle_put(ep);

		continue;

err_parse:
		fwnode_handle_put(ep);
		kfree(s_asd);
		return ret;
	}

	/*
	 * Proceed even without sensors connected to allow the device to
	 * suspend.
	 */
	cio2->notifier.ops = &cio2_async_ops;
	ret = v4l2_async_notifier_register(&cio2->v4l2_dev, &cio2->notifier);
	if (ret)
		dev_err(&cio2->pci_dev->dev,
			"failed to register async notifier : %d\n", ret);

	return ret;
}