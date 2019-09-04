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
struct sunxi_engine {int dummy; } ;
struct sun4i_drv {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct sunxi_engine* ERR_PTR (int /*<<< orphan*/ ) ; 
 int of_get_child_count (struct device_node*) ; 
 struct device_node* of_graph_get_port_by_id (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct sunxi_engine* sun4i_tcon_find_engine_traverse (struct sun4i_drv*,struct device_node*,int /*<<< orphan*/ ) ; 
 struct sunxi_engine* sun4i_tcon_get_engine_by_id (struct sun4i_drv*,int) ; 
 int sun4i_tcon_of_get_id_from_port (struct device_node*) ; 

__attribute__((used)) static struct sunxi_engine *sun4i_tcon_find_engine(struct sun4i_drv *drv,
						   struct device_node *node)
{
	struct device_node *port;
	struct sunxi_engine *engine;

	port = of_graph_get_port_by_id(node, 0);
	if (!port)
		return ERR_PTR(-EINVAL);

	/*
	 * Is this a corrected device tree with cross pipeline
	 * connections between the backend and TCON?
	 */
	if (of_get_child_count(port) > 1) {
		/* Get our ID directly from an upstream endpoint */
		int id = sun4i_tcon_of_get_id_from_port(port);

		/* Get our engine by matching our ID */
		engine = sun4i_tcon_get_engine_by_id(drv, id);

		of_node_put(port);
		return engine;
	}

	/* Fallback to old method by traversing input endpoints */
	of_node_put(port);
	return sun4i_tcon_find_engine_traverse(drv, node, 0);
}