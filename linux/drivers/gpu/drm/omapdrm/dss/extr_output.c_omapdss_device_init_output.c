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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct omap_dss_device {scalar_t__ type; int /*<<< orphan*/ * panel; int /*<<< orphan*/  bridge; TYPE_1__* next; TYPE_3__* dev; int /*<<< orphan*/  of_ports; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 scalar_t__ ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_drm_find_bridge (struct device_node*) ; 
 int /*<<< orphan*/ * of_drm_find_panel (struct device_node*) ; 
 struct device_node* of_graph_get_remote_node (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  omapdss_device_put (TYPE_1__*) ; 
 TYPE_1__* omapdss_find_device_by_node (struct device_node*) ; 

int omapdss_device_init_output(struct omap_dss_device *out)
{
	struct device_node *remote_node;

	remote_node = of_graph_get_remote_node(out->dev->of_node,
					       ffs(out->of_ports) - 1, 0);
	if (!remote_node) {
		dev_dbg(out->dev, "failed to find video sink\n");
		return 0;
	}

	out->next = omapdss_find_device_by_node(remote_node);
	out->bridge = of_drm_find_bridge(remote_node);
	out->panel = of_drm_find_panel(remote_node);
	if (IS_ERR(out->panel))
		out->panel = NULL;

	of_node_put(remote_node);

	if (out->next && out->type != out->next->type) {
		dev_err(out->dev, "output type and display type don't match\n");
		omapdss_device_put(out->next);
		out->next = NULL;
		return -EINVAL;
	}

	return out->next || out->bridge || out->panel ? 0 : -EPROBE_DEFER;
}