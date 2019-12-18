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
struct tegra_xusb_padctl {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct tegra_xusb_padctl* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct tegra_xusb_padctl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

struct tegra_xusb_padctl *tegra_xusb_padctl_get(struct device *dev)
{
	struct tegra_xusb_padctl *padctl;
	struct platform_device *pdev;
	struct device_node *np;

	np = of_parse_phandle(dev->of_node, "nvidia,xusb-padctl", 0);
	if (!np)
		return ERR_PTR(-EINVAL);

	/*
	 * This is slightly ugly. A better implementation would be to keep a
	 * registry of pad controllers, but since there will almost certainly
	 * only ever be one per SoC that would be a little overkill.
	 */
	pdev = of_find_device_by_node(np);
	if (!pdev) {
		of_node_put(np);
		return ERR_PTR(-ENODEV);
	}

	of_node_put(np);

	padctl = platform_get_drvdata(pdev);
	if (!padctl) {
		put_device(&pdev->dev);
		return ERR_PTR(-EPROBE_DEFER);
	}

	return padctl;
}