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
struct tegra_bpmp {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct tegra_bpmp* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct tegra_bpmp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

struct tegra_bpmp *tegra_bpmp_get(struct device *dev)
{
	struct platform_device *pdev;
	struct tegra_bpmp *bpmp;
	struct device_node *np;

	np = of_parse_phandle(dev->of_node, "nvidia,bpmp", 0);
	if (!np)
		return ERR_PTR(-ENOENT);

	pdev = of_find_device_by_node(np);
	if (!pdev) {
		bpmp = ERR_PTR(-ENODEV);
		goto put;
	}

	bpmp = platform_get_drvdata(pdev);
	if (!bpmp) {
		bpmp = ERR_PTR(-EPROBE_DEFER);
		put_device(&pdev->dev);
		goto put;
	}

put:
	of_node_put(np);
	return bpmp;
}