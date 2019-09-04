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
struct of_endpoint {int /*<<< orphan*/  id; int /*<<< orphan*/  port; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct coresight_platform_data {int /*<<< orphan*/  cpu; int /*<<< orphan*/ * child_ports; void** child_names; int /*<<< orphan*/ * outports; scalar_t__ nr_outport; int /*<<< orphan*/  nr_inport; void* name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 struct coresight_platform_data* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* dev_name (struct device*) ; 
 struct coresight_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int of_coresight_alloc_memory (struct device*,struct coresight_platform_data*) ; 
 int /*<<< orphan*/  of_coresight_get_cpu (struct device_node const*) ; 
 struct device* of_coresight_get_endpoint_device (struct device_node*) ; 
 int /*<<< orphan*/  of_coresight_get_ports (struct device_node const*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node const*,struct device_node*) ; 
 struct device_node* of_graph_get_remote_port (struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int of_graph_parse_endpoint (struct device_node*,struct of_endpoint*) ; 

struct coresight_platform_data *
of_get_coresight_platform_data(struct device *dev,
			       const struct device_node *node)
{
	int i = 0, ret = 0;
	struct coresight_platform_data *pdata;
	struct of_endpoint endpoint, rendpoint;
	struct device *rdev;
	struct device_node *ep = NULL;
	struct device_node *rparent = NULL;
	struct device_node *rport = NULL;

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return ERR_PTR(-ENOMEM);

	/* Use device name as sysfs handle */
	pdata->name = dev_name(dev);

	/* Get the number of input and output port for this component */
	of_coresight_get_ports(node, &pdata->nr_inport, &pdata->nr_outport);

	if (pdata->nr_outport) {
		ret = of_coresight_alloc_memory(dev, pdata);
		if (ret)
			return ERR_PTR(ret);

		/* Iterate through each port to discover topology */
		do {
			/* Get a handle on a port */
			ep = of_graph_get_next_endpoint(node, ep);
			if (!ep)
				break;

			/*
			 * No need to deal with input ports, processing for as
			 * processing for output ports will deal with them.
			 */
			if (of_find_property(ep, "slave-mode", NULL))
				continue;

			/* Get a handle on the local endpoint */
			ret = of_graph_parse_endpoint(ep, &endpoint);

			if (ret)
				continue;

			/* The local out port number */
			pdata->outports[i] = endpoint.port;

			/*
			 * Get a handle on the remote port and parent
			 * attached to it.
			 */
			rparent = of_graph_get_remote_port_parent(ep);
			rport = of_graph_get_remote_port(ep);

			if (!rparent || !rport)
				continue;

			if (of_graph_parse_endpoint(rport, &rendpoint))
				continue;

			rdev = of_coresight_get_endpoint_device(rparent);
			if (!rdev)
				return ERR_PTR(-EPROBE_DEFER);

			pdata->child_names[i] = dev_name(rdev);
			pdata->child_ports[i] = rendpoint.id;

			i++;
		} while (ep);
	}

	pdata->cpu = of_coresight_get_cpu(node);

	return pdata;
}