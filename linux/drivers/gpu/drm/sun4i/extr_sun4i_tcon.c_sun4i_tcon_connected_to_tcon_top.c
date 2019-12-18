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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_SUN8I_TCON_TOP ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_remote_node (struct device_node*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  sun8i_tcon_top_of_table ; 

__attribute__((used)) static bool sun4i_tcon_connected_to_tcon_top(struct device_node *node)
{
	struct device_node *remote;
	bool ret = false;

	remote = of_graph_get_remote_node(node, 0, -1);
	if (remote) {
		ret = !!(IS_ENABLED(CONFIG_DRM_SUN8I_TCON_TOP) &&
			 of_match_node(sun8i_tcon_top_of_table, remote));
		of_node_put(remote);
	}

	return ret;
}