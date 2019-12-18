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
struct phy_provider {int dummy; } ;
struct module {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct phy_provider* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct phy_provider*) ; 
 struct phy_provider* __of_phy_provider_register (struct device*,struct device_node*,struct module*,struct phy* (*) (struct device*,struct of_phandle_args*)) ; 
 int /*<<< orphan*/  devm_phy_provider_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct phy_provider**) ; 
 struct phy_provider** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct phy_provider**) ; 

struct phy_provider *__devm_of_phy_provider_register(struct device *dev,
	struct device_node *children, struct module *owner,
	struct phy * (*of_xlate)(struct device *dev,
				 struct of_phandle_args *args))
{
	struct phy_provider **ptr, *phy_provider;

	ptr = devres_alloc(devm_phy_provider_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	phy_provider = __of_phy_provider_register(dev, children, owner,
						  of_xlate);
	if (!IS_ERR(phy_provider)) {
		*ptr = phy_provider;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return phy_provider;
}