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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_get_compatible_child (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static struct device *dwc3_meson_g12_find_child(struct device *dev,
						const char *compatible)
{
	struct platform_device *pdev;
	struct device_node *np;

	np = of_get_compatible_child(dev->of_node, compatible);
	if (!np)
		return NULL;

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	if (!pdev)
		return NULL;

	return &pdev->dev;
}