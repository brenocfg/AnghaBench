#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_6__ {TYPE_1__ match; int /*<<< orphan*/  match_type; } ;
struct xvip_graph_entity {int /*<<< orphan*/  list; TYPE_2__ asd; struct device_node* node; } ;
struct xvip_composite_device {int /*<<< orphan*/  num_subdevs; int /*<<< orphan*/  entities; TYPE_3__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,struct device_node*) ; 
 struct xvip_graph_entity* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ xvip_graph_find_entity (struct xvip_composite_device*,struct device_node*) ; 

__attribute__((used)) static int xvip_graph_parse_one(struct xvip_composite_device *xdev,
				struct device_node *node)
{
	struct xvip_graph_entity *entity;
	struct device_node *remote;
	struct device_node *ep = NULL;
	int ret = 0;

	dev_dbg(xdev->dev, "parsing node %pOF\n", node);

	while (1) {
		ep = of_graph_get_next_endpoint(node, ep);
		if (ep == NULL)
			break;

		dev_dbg(xdev->dev, "handling endpoint %pOF\n", ep);

		remote = of_graph_get_remote_port_parent(ep);
		if (remote == NULL) {
			ret = -EINVAL;
			break;
		}

		/* Skip entities that we have already processed. */
		if (remote == xdev->dev->of_node ||
		    xvip_graph_find_entity(xdev, remote)) {
			of_node_put(remote);
			continue;
		}

		entity = devm_kzalloc(xdev->dev, sizeof(*entity), GFP_KERNEL);
		if (entity == NULL) {
			of_node_put(remote);
			ret = -ENOMEM;
			break;
		}

		entity->node = remote;
		entity->asd.match_type = V4L2_ASYNC_MATCH_FWNODE;
		entity->asd.match.fwnode = of_fwnode_handle(remote);
		list_add_tail(&entity->list, &xdev->entities);
		xdev->num_subdevs++;
	}

	of_node_put(ep);
	return ret;
}