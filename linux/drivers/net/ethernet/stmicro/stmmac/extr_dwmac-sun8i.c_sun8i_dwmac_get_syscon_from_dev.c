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
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct regmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct regmap* dev_get_regmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static struct regmap *sun8i_dwmac_get_syscon_from_dev(struct device_node *node)
{
	struct device_node *syscon_node;
	struct platform_device *syscon_pdev;
	struct regmap *regmap = NULL;

	syscon_node = of_parse_phandle(node, "syscon", 0);
	if (!syscon_node)
		return ERR_PTR(-ENODEV);

	syscon_pdev = of_find_device_by_node(syscon_node);
	if (!syscon_pdev) {
		/* platform device might not be probed yet */
		regmap = ERR_PTR(-EPROBE_DEFER);
		goto out_put_node;
	}

	/* If no regmap is found then the other device driver is at fault */
	regmap = dev_get_regmap(&syscon_pdev->dev, NULL);
	if (!regmap)
		regmap = ERR_PTR(-EINVAL);

	platform_device_put(syscon_pdev);
out_put_node:
	of_node_put(syscon_node);
	return regmap;
}