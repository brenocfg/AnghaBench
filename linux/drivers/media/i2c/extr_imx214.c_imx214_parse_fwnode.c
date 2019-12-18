#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_fwnode_endpoint {unsigned int nr_of_link_frequencies; scalar_t__* link_frequencies; int /*<<< orphan*/  bus_type; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IMX214_DEFAULT_LINK_FREQ ; 
 int /*<<< orphan*/  V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int v4l2_fwnode_endpoint_alloc_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  v4l2_fwnode_endpoint_free (struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int imx214_parse_fwnode(struct device *dev)
{
	struct fwnode_handle *endpoint;
	struct v4l2_fwnode_endpoint bus_cfg = {
		.bus_type = V4L2_MBUS_CSI2_DPHY,
	};
	unsigned int i;
	int ret;

	endpoint = fwnode_graph_get_next_endpoint(dev_fwnode(dev), NULL);
	if (!endpoint) {
		dev_err(dev, "endpoint node not found\n");
		return -EINVAL;
	}

	ret = v4l2_fwnode_endpoint_alloc_parse(endpoint, &bus_cfg);
	if (ret) {
		dev_err(dev, "parsing endpoint node failed\n");
		goto done;
	}

	for (i = 0; i < bus_cfg.nr_of_link_frequencies; i++)
		if (bus_cfg.link_frequencies[i] == IMX214_DEFAULT_LINK_FREQ)
			break;

	if (i == bus_cfg.nr_of_link_frequencies) {
		dev_err(dev, "link-frequencies %d not supported, Please review your DT\n",
			IMX214_DEFAULT_LINK_FREQ);
		ret = -EINVAL;
		goto done;
	}

done:
	v4l2_fwnode_endpoint_free(&bus_cfg);
	fwnode_handle_put(endpoint);
	return ret;
}