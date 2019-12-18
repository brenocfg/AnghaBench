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
struct drm_panel {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IS_ERR (struct drm_panel*) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct drm_bridge* of_drm_find_bridge (struct device_node*) ; 
 struct drm_panel* of_drm_find_panel (struct device_node*) ; 
 struct device_node* of_graph_get_remote_node (struct device_node const*,int,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

int drm_of_find_panel_or_bridge(const struct device_node *np,
				int port, int endpoint,
				struct drm_panel **panel,
				struct drm_bridge **bridge)
{
	int ret = -EPROBE_DEFER;
	struct device_node *remote;

	if (!panel && !bridge)
		return -EINVAL;
	if (panel)
		*panel = NULL;

	remote = of_graph_get_remote_node(np, port, endpoint);
	if (!remote)
		return -ENODEV;

	if (!of_device_is_available(remote)) {
		of_node_put(remote);
		return -ENODEV;
	}

	if (panel) {
		*panel = of_drm_find_panel(remote);
		if (!IS_ERR(*panel))
			ret = 0;
		else
			*panel = NULL;
	}

	/* No panel found yet, check for a bridge next. */
	if (bridge) {
		if (ret) {
			*bridge = of_drm_find_bridge(remote);
			if (*bridge)
				ret = 0;
		} else {
			*bridge = NULL;
		}

	}

	of_node_put(remote);
	return ret;
}