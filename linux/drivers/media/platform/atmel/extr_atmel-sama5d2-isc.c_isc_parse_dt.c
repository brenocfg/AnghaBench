#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int flags; } ;
struct TYPE_6__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_2__ bus; } ;
struct isc_subdev_entity {int pfe_cfg0; int /*<<< orphan*/  list; TYPE_4__* asd; } ;
struct isc_device {int /*<<< orphan*/  subdev_entities; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_7__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_8__ {TYPE_3__ match; int /*<<< orphan*/  match_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ISC_PFE_CFG0_CCIR656 ; 
 int ISC_PFE_CFG0_CCIR_CRC ; 
 int ISC_PFE_CFG0_HPOL_LOW ; 
 int ISC_PFE_CFG0_PPOL_LOW ; 
 int ISC_PFE_CFG0_VPOL_LOW ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 scalar_t__ V4L2_MBUS_BT656 ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 unsigned int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*,struct device_node*) ; 
 struct isc_subdev_entity* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int isc_parse_dt(struct device *dev, struct isc_device *isc)
{
	struct device_node *np = dev->of_node;
	struct device_node *epn = NULL, *rem;
	struct isc_subdev_entity *subdev_entity;
	unsigned int flags;
	int ret;

	INIT_LIST_HEAD(&isc->subdev_entities);

	while (1) {
		struct v4l2_fwnode_endpoint v4l2_epn = { .bus_type = 0 };

		epn = of_graph_get_next_endpoint(np, epn);
		if (!epn)
			return 0;

		rem = of_graph_get_remote_port_parent(epn);
		if (!rem) {
			dev_notice(dev, "Remote device at %pOF not found\n",
				   epn);
			continue;
		}

		ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(epn),
						 &v4l2_epn);
		if (ret) {
			of_node_put(rem);
			ret = -EINVAL;
			dev_err(dev, "Could not parse the endpoint\n");
			break;
		}

		subdev_entity = devm_kzalloc(dev, sizeof(*subdev_entity),
					     GFP_KERNEL);
		if (!subdev_entity) {
			of_node_put(rem);
			ret = -ENOMEM;
			break;
		}

		/* asd will be freed by the subsystem once it's added to the
		 * notifier list
		 */
		subdev_entity->asd = kzalloc(sizeof(*subdev_entity->asd),
					     GFP_KERNEL);
		if (!subdev_entity->asd) {
			of_node_put(rem);
			ret = -ENOMEM;
			break;
		}

		flags = v4l2_epn.bus.parallel.flags;

		if (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
			subdev_entity->pfe_cfg0 = ISC_PFE_CFG0_HPOL_LOW;

		if (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_VPOL_LOW;

		if (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_PPOL_LOW;

		if (v4l2_epn.bus_type == V4L2_MBUS_BT656)
			subdev_entity->pfe_cfg0 |= ISC_PFE_CFG0_CCIR_CRC |
					ISC_PFE_CFG0_CCIR656;

		subdev_entity->asd->match_type = V4L2_ASYNC_MATCH_FWNODE;
		subdev_entity->asd->match.fwnode = of_fwnode_handle(rem);
		list_add_tail(&subdev_entity->list, &isc->subdev_entities);
	}

	of_node_put(epn);
	return ret;
}