#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_5__ {TYPE_1__ match; int /*<<< orphan*/  match_type; } ;
struct TYPE_6__ {TYPE_2__ asd; struct device_node* node; } ;
struct atmel_isi {TYPE_3__ entity; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int isi_graph_parse(struct atmel_isi *isi, struct device_node *node)
{
	struct device_node *ep = NULL;
	struct device_node *remote;

	ep = of_graph_get_next_endpoint(node, ep);
	if (!ep)
		return -EINVAL;

	remote = of_graph_get_remote_port_parent(ep);
	of_node_put(ep);
	if (!remote)
		return -EINVAL;

	/* Remote node to connect */
	isi->entity.node = remote;
	isi->entity.asd.match_type = V4L2_ASYNC_MATCH_FWNODE;
	isi->entity.asd.match.fwnode = of_fwnode_handle(remote);
	return 0;
}