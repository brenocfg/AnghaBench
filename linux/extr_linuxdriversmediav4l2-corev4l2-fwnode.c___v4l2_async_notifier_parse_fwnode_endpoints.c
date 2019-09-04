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
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {unsigned int max_subdevs; unsigned int num_subdevs; } ;
struct fwnode_handle {int dummy; } ;
struct fwnode_endpoint {unsigned int port; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_fwnode (struct device*) ; 
 int fwnode_device_is_available (struct fwnode_handle*) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (int /*<<< orphan*/ ,struct fwnode_handle*) ; 
 struct fwnode_handle* fwnode_graph_get_port_parent (struct fwnode_handle*) ; 
 int fwnode_graph_parse_endpoint (struct fwnode_handle*,struct fwnode_endpoint*) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int v4l2_async_notifier_fwnode_parse_endpoint (struct device*,struct v4l2_async_notifier*,struct fwnode_handle*,size_t,int (*) (struct device*,struct v4l2_fwnode_endpoint*,struct v4l2_async_subdev*)) ; 
 int v4l2_async_notifier_realloc (struct v4l2_async_notifier*,unsigned int) ; 

__attribute__((used)) static int __v4l2_async_notifier_parse_fwnode_endpoints(
	struct device *dev, struct v4l2_async_notifier *notifier,
	size_t asd_struct_size, unsigned int port, bool has_port,
	int (*parse_endpoint)(struct device *dev,
			    struct v4l2_fwnode_endpoint *vep,
			    struct v4l2_async_subdev *asd))
{
	struct fwnode_handle *fwnode;
	unsigned int max_subdevs = notifier->max_subdevs;
	int ret;

	if (WARN_ON(asd_struct_size < sizeof(struct v4l2_async_subdev)))
		return -EINVAL;

	for (fwnode = NULL; (fwnode = fwnode_graph_get_next_endpoint(
				     dev_fwnode(dev), fwnode)); ) {
		struct fwnode_handle *dev_fwnode;
		bool is_available;

		dev_fwnode = fwnode_graph_get_port_parent(fwnode);
		is_available = fwnode_device_is_available(dev_fwnode);
		fwnode_handle_put(dev_fwnode);
		if (!is_available)
			continue;

		if (has_port) {
			struct fwnode_endpoint ep;

			ret = fwnode_graph_parse_endpoint(fwnode, &ep);
			if (ret) {
				fwnode_handle_put(fwnode);
				return ret;
			}

			if (ep.port != port)
				continue;
		}
		max_subdevs++;
	}

	/* No subdevs to add? Return here. */
	if (max_subdevs == notifier->max_subdevs)
		return 0;

	ret = v4l2_async_notifier_realloc(notifier, max_subdevs);
	if (ret)
		return ret;

	for (fwnode = NULL; (fwnode = fwnode_graph_get_next_endpoint(
				     dev_fwnode(dev), fwnode)); ) {
		struct fwnode_handle *dev_fwnode;
		bool is_available;

		dev_fwnode = fwnode_graph_get_port_parent(fwnode);
		is_available = fwnode_device_is_available(dev_fwnode);
		fwnode_handle_put(dev_fwnode);
		if (!is_available)
			continue;

		if (has_port) {
			struct fwnode_endpoint ep;

			ret = fwnode_graph_parse_endpoint(fwnode, &ep);
			if (ret)
				break;

			if (ep.port != port)
				continue;
		}

		if (WARN_ON(notifier->num_subdevs >= notifier->max_subdevs)) {
			ret = -EINVAL;
			break;
		}

		ret = v4l2_async_notifier_fwnode_parse_endpoint(
			dev, notifier, fwnode, asd_struct_size, parse_endpoint);
		if (ret < 0)
			break;
	}

	fwnode_handle_put(fwnode);

	return ret;
}