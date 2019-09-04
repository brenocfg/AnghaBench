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
struct TYPE_4__ {unsigned int flags; } ;
struct TYPE_3__ {TYPE_2__ parallel; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_1__ bus; } ;
struct tvp5150 {scalar_t__ mbus_type; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int V4L2_MBUS_FIELD_EVEN_LOW ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 scalar_t__ V4L2_MBUS_PARALLEL ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int tvp5150_parse_dt(struct tvp5150 *decoder, struct device_node *np)
{
	struct v4l2_fwnode_endpoint bus_cfg;
	struct device_node *ep;
#ifdef CONFIG_MEDIA_CONTROLLER
	struct device_node *connectors, *child;
	struct media_entity *input;
	const char *name;
	u32 input_type;
#endif
	unsigned int flags;
	int ret = 0;

	ep = of_graph_get_next_endpoint(np, NULL);
	if (!ep)
		return -EINVAL;

	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(ep), &bus_cfg);
	if (ret)
		goto err;

	flags = bus_cfg.bus.parallel.flags;

	if (bus_cfg.bus_type == V4L2_MBUS_PARALLEL &&
	    !(flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH &&
	      flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH &&
	      flags & V4L2_MBUS_FIELD_EVEN_LOW)) {
		ret = -EINVAL;
		goto err;
	}

	decoder->mbus_type = bus_cfg.bus_type;

#ifdef CONFIG_MEDIA_CONTROLLER
	connectors = of_get_child_by_name(np, "connectors");

	if (!connectors)
		goto err;

	for_each_available_child_of_node(connectors, child) {
		ret = of_property_read_u32(child, "input", &input_type);
		if (ret) {
			dev_err(decoder->sd.dev,
				 "missing type property in node %s\n",
				 child->name);
			goto err_connector;
		}

		if (input_type >= TVP5150_INPUT_NUM) {
			ret = -EINVAL;
			goto err_connector;
		}

		input = &decoder->input_ent[input_type];

		/* Each input connector can only be defined once */
		if (input->name) {
			dev_err(decoder->sd.dev,
				 "input %s with same type already exists\n",
				 input->name);
			ret = -EINVAL;
			goto err_connector;
		}

		switch (input_type) {
		case TVP5150_COMPOSITE0:
		case TVP5150_COMPOSITE1:
			input->function = MEDIA_ENT_F_CONN_COMPOSITE;
			break;
		case TVP5150_SVIDEO:
			input->function = MEDIA_ENT_F_CONN_SVIDEO;
			break;
		}

		input->flags = MEDIA_ENT_FL_CONNECTOR;

		ret = of_property_read_string(child, "label", &name);
		if (ret < 0) {
			dev_err(decoder->sd.dev,
				 "missing label property in node %s\n",
				 child->name);
			goto err_connector;
		}

		input->name = name;
	}

err_connector:
	of_node_put(connectors);
#endif
err:
	of_node_put(ep);
	return ret;
}