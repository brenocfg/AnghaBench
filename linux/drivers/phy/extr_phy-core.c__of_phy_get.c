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
struct phy_provider {int /*<<< orphan*/  owner; int /*<<< orphan*/  dev; struct phy* (* of_xlate ) (int /*<<< orphan*/ ,struct of_phandle_args*) ;} ;
struct phy {int dummy; } ;
struct of_phandle_args {int /*<<< orphan*/  np; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_is_available (int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 struct phy_provider* of_phy_provider_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_provider_mutex ; 
 struct phy* stub1 (int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct phy *_of_phy_get(struct device_node *np, int index)
{
	int ret;
	struct phy_provider *phy_provider;
	struct phy *phy = NULL;
	struct of_phandle_args args;

	ret = of_parse_phandle_with_args(np, "phys", "#phy-cells",
		index, &args);
	if (ret)
		return ERR_PTR(-ENODEV);

	/* This phy type handled by the usb-phy subsystem for now */
	if (of_device_is_compatible(args.np, "usb-nop-xceiv"))
		return ERR_PTR(-ENODEV);

	mutex_lock(&phy_provider_mutex);
	phy_provider = of_phy_provider_lookup(args.np);
	if (IS_ERR(phy_provider) || !try_module_get(phy_provider->owner)) {
		phy = ERR_PTR(-EPROBE_DEFER);
		goto out_unlock;
	}

	if (!of_device_is_available(args.np)) {
		dev_warn(phy_provider->dev, "Requested PHY is disabled\n");
		phy = ERR_PTR(-ENODEV);
		goto out_put_module;
	}

	phy = phy_provider->of_xlate(phy_provider->dev, &args);

out_put_module:
	module_put(phy_provider->owner);

out_unlock:
	mutex_unlock(&phy_provider_mutex);
	of_node_put(args.np);

	return phy;
}