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
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct platform_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct device_node* of_get_compatible_child (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct platform_device* of_platform_device_create (struct device_node*,int /*<<< orphan*/ *,struct device*) ; 

__attribute__((used)) static struct platform_device *meson_mx_mmc_slot_pdev(struct device *parent)
{
	struct device_node *slot_node;
	struct platform_device *pdev;

	/*
	 * TODO: the MMC core framework currently does not support
	 * controllers with multiple slots properly. So we only register
	 * the first slot for now
	 */
	slot_node = of_get_compatible_child(parent->of_node, "mmc-slot");
	if (!slot_node) {
		dev_warn(parent, "no 'mmc-slot' sub-node found\n");
		return ERR_PTR(-ENOENT);
	}

	pdev = of_platform_device_create(slot_node, NULL, parent);
	of_node_put(slot_node);

	return pdev;
}