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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_2__ bus; } ;
struct ov7670_info {int pclk_hb_disable; int /*<<< orphan*/  mbus_config; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_MBUS_PARALLEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct fwnode_handle* dev_fwnode (struct device*) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (struct fwnode_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 scalar_t__ fwnode_property_present (struct fwnode_handle*,char*) ; 
 int v4l2_fwnode_endpoint_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int ov7670_parse_dt(struct device *dev,
			   struct ov7670_info *info)
{
	struct fwnode_handle *fwnode = dev_fwnode(dev);
	struct v4l2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
	struct fwnode_handle *ep;
	int ret;

	if (!fwnode)
		return -EINVAL;

	info->pclk_hb_disable = false;
	if (fwnode_property_present(fwnode, "ov7670,pclk-hb-disable"))
		info->pclk_hb_disable = true;

	ep = fwnode_graph_get_next_endpoint(fwnode, NULL);
	if (!ep)
		return -EINVAL;

	ret = v4l2_fwnode_endpoint_parse(ep, &bus_cfg);
	fwnode_handle_put(ep);
	if (ret)
		return ret;

	if (bus_cfg.bus_type != V4L2_MBUS_PARALLEL) {
		dev_err(dev, "Unsupported media bus type\n");
		return ret;
	}
	info->mbus_config = bus_cfg.bus.parallel.flags;

	return 0;
}