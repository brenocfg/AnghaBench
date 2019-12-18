#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parallel; } ;
struct v4l2_fwnode_endpoint {TYPE_1__ bus; int /*<<< orphan*/  bus_type; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ops; } ;
struct sun4i_csi {TYPE_2__ notifier; int /*<<< orphan*/  asd; int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FWNODE_GRAPH_ENDPOINT_NEXT ; 
 int /*<<< orphan*/  V4L2_MBUS_PARALLEL ; 
 int /*<<< orphan*/  dev_fwnode (int /*<<< orphan*/ ) ; 
 struct fwnode_handle* fwnode_graph_get_endpoint_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int /*<<< orphan*/  sun4i_csi_notify_ops ; 
 int v4l2_async_notifier_add_fwnode_remote_subdev (TYPE_2__*,struct fwnode_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_2__*) ; 
 int v4l2_fwnode_endpoint_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int sun4i_csi_notifier_init(struct sun4i_csi *csi)
{
	struct v4l2_fwnode_endpoint vep = {
		.bus_type = V4L2_MBUS_PARALLEL,
	};
	struct fwnode_handle *ep;
	int ret;

	v4l2_async_notifier_init(&csi->notifier);

	ep = fwnode_graph_get_endpoint_by_id(dev_fwnode(csi->dev), 0, 0,
					     FWNODE_GRAPH_ENDPOINT_NEXT);
	if (!ep)
		return -EINVAL;

	ret = v4l2_fwnode_endpoint_parse(ep, &vep);
	if (ret)
		goto out;

	csi->bus = vep.bus.parallel;

	ret = v4l2_async_notifier_add_fwnode_remote_subdev(&csi->notifier,
							   ep, &csi->asd);
	if (ret)
		goto out;

	csi->notifier.ops = &sun4i_csi_notify_ops;

out:
	fwnode_handle_put(ep);
	return ret;
}