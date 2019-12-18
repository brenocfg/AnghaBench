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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {int /*<<< orphan*/  compatible; } ;
struct dw_mipi_dsi_rockchip {TYPE_2__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct device_node* of_node; TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device_node* of_find_compatible_node (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_graph_get_remote_node (struct device_node*,int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct dw_mipi_dsi_rockchip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static struct device
*dw_mipi_dsi_rockchip_find_second(struct dw_mipi_dsi_rockchip *dsi)
{
	const struct of_device_id *match;
	struct device_node *node = NULL, *local;

	match = of_match_device(dsi->dev->driver->of_match_table, dsi->dev);

	local = of_graph_get_remote_node(dsi->dev->of_node, 1, 0);
	if (!local)
		return NULL;

	while ((node = of_find_compatible_node(node, NULL,
					       match->compatible))) {
		struct device_node *remote;

		/* found ourself */
		if (node == dsi->dev->of_node)
			continue;

		remote = of_graph_get_remote_node(node, 1, 0);
		if (!remote)
			continue;

		/* same display device in port1-ep0 for both */
		if (remote == local) {
			struct dw_mipi_dsi_rockchip *dsi2;
			struct platform_device *pdev;

			pdev = of_find_device_by_node(node);

			/*
			 * we have found the second, so will either return it
			 * or return with an error. In any case won't need the
			 * nodes anymore nor continue the loop.
			 */
			of_node_put(remote);
			of_node_put(node);
			of_node_put(local);

			if (!pdev)
				return ERR_PTR(-EPROBE_DEFER);

			dsi2 = platform_get_drvdata(pdev);
			if (!dsi2) {
				platform_device_put(pdev);
				return ERR_PTR(-EPROBE_DEFER);
			}

			return &pdev->dev;
		}

		of_node_put(remote);
	}

	of_node_put(local);

	return NULL;
}