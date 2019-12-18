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
struct tegra_dsi {TYPE_2__* slave; TYPE_1__* dev; } ;
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct tegra_dsi* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tegra_dsi_ganged_probe(struct tegra_dsi *dsi)
{
	struct device_node *np;

	np = of_parse_phandle(dsi->dev->of_node, "nvidia,ganged-mode", 0);
	if (np) {
		struct platform_device *gangster = of_find_device_by_node(np);

		dsi->slave = platform_get_drvdata(gangster);
		of_node_put(np);

		if (!dsi->slave)
			return -EPROBE_DEFER;

		dsi->slave->master = dsi;
	}

	return 0;
}