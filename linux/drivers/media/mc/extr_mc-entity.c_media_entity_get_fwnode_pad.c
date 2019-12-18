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
struct media_entity {unsigned int num_pads; TYPE_1__* pads; TYPE_2__* ops; } ;
struct fwnode_handle {int dummy; } ;
struct fwnode_endpoint {int dummy; } ;
struct TYPE_4__ {int (* get_fwnode_pad ) (struct fwnode_endpoint*) ;} ;
struct TYPE_3__ {unsigned long flags; } ;

/* Variables and functions */
 int ENXIO ; 
 int fwnode_graph_parse_endpoint (struct fwnode_handle*,struct fwnode_endpoint*) ; 
 int stub1 (struct fwnode_endpoint*) ; 

int media_entity_get_fwnode_pad(struct media_entity *entity,
				struct fwnode_handle *fwnode,
				unsigned long direction_flags)
{
	struct fwnode_endpoint endpoint;
	unsigned int i;
	int ret;

	if (!entity->ops || !entity->ops->get_fwnode_pad) {
		for (i = 0; i < entity->num_pads; i++) {
			if (entity->pads[i].flags & direction_flags)
				return i;
		}

		return -ENXIO;
	}

	ret = fwnode_graph_parse_endpoint(fwnode, &endpoint);
	if (ret)
		return ret;

	ret = entity->ops->get_fwnode_pad(&endpoint);
	if (ret < 0)
		return ret;

	if (ret >= entity->num_pads)
		return -ENXIO;

	if (!(entity->pads[ret].flags & direction_flags))
		return -ENXIO;

	return ret;
}