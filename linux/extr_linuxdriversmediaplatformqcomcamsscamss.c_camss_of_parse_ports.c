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
struct v4l2_async_notifier {int num_subdevs; TYPE_2__** subdevs; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_4__ {TYPE_1__ match; int /*<<< orphan*/  match_type; } ;
struct camss_async_subdev {TYPE_2__ asd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 int camss_of_parse_endpoint_node (struct device*,struct device_node*,struct camss_async_subdev*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_available (struct device_node*) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (int /*<<< orphan*/ ,struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int camss_of_parse_ports(struct device *dev,
				struct v4l2_async_notifier *notifier)
{
	struct device_node *node = NULL;
	struct device_node *remote = NULL;
	unsigned int size, i;
	int ret;

	while ((node = of_graph_get_next_endpoint(dev->of_node, node)))
		if (of_device_is_available(node))
			notifier->num_subdevs++;

	of_node_put(node);
	size = sizeof(*notifier->subdevs) * notifier->num_subdevs;
	notifier->subdevs = devm_kzalloc(dev, size, GFP_KERNEL);
	if (!notifier->subdevs) {
		dev_err(dev, "Failed to allocate memory\n");
		return -ENOMEM;
	}

	i = 0;
	while ((node = of_graph_get_next_endpoint(dev->of_node, node))) {
		struct camss_async_subdev *csd;

		if (!of_device_is_available(node))
			continue;

		csd = devm_kzalloc(dev, sizeof(*csd), GFP_KERNEL);
		if (!csd) {
			of_node_put(node);
			dev_err(dev, "Failed to allocate memory\n");
			return -ENOMEM;
		}

		notifier->subdevs[i++] = &csd->asd;

		ret = camss_of_parse_endpoint_node(dev, node, csd);
		if (ret < 0) {
			of_node_put(node);
			return ret;
		}

		remote = of_graph_get_remote_port_parent(node);
		if (!remote) {
			dev_err(dev, "Cannot get remote parent\n");
			of_node_put(node);
			return -EINVAL;
		}

		csd->asd.match_type = V4L2_ASYNC_MATCH_FWNODE;
		csd->asd.match.fwnode = of_fwnode_handle(remote);
	}
	of_node_put(node);

	return notifier->num_subdevs;
}