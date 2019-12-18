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
struct exynos_dsi {int /*<<< orphan*/  in_bridge_node; int /*<<< orphan*/  esc_clk_rate; int /*<<< orphan*/  burst_clk_rate; int /*<<< orphan*/  pll_clk_rate; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PORT_IN ; 
 int exynos_dsi_of_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_graph_get_remote_node (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_dsi_parse_dt(struct exynos_dsi *dsi)
{
	struct device *dev = dsi->dev;
	struct device_node *node = dev->of_node;
	int ret;

	ret = exynos_dsi_of_read_u32(node, "samsung,pll-clock-frequency",
				     &dsi->pll_clk_rate);
	if (ret < 0)
		return ret;

	ret = exynos_dsi_of_read_u32(node, "samsung,burst-clock-frequency",
				     &dsi->burst_clk_rate);
	if (ret < 0)
		return ret;

	ret = exynos_dsi_of_read_u32(node, "samsung,esc-clock-frequency",
				     &dsi->esc_clk_rate);
	if (ret < 0)
		return ret;

	dsi->in_bridge_node = of_graph_get_remote_node(node, DSI_PORT_IN, 0);

	return 0;
}