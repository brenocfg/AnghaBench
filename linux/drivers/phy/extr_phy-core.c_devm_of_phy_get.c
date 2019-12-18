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
struct phy {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct phy*) ; 
 int /*<<< orphan*/  devm_phy_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct phy**) ; 
 struct phy** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct phy**) ; 
 struct phy* of_phy_get (struct device_node*,char const*) ; 

struct phy *devm_of_phy_get(struct device *dev, struct device_node *np,
			    const char *con_id)
{
	struct phy **ptr, *phy;

	ptr = devres_alloc(devm_phy_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	phy = of_phy_get(np, con_id);
	if (!IS_ERR(phy)) {
		*ptr = phy;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return phy;
}