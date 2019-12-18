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
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int /*<<< orphan*/  PTR_ERR (struct phy*) ; 
 struct phy* devm_of_phy_get (struct device*,struct device_node*,char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static struct phy *devm_of_phy_optional_get_index(struct device *dev,
						  struct device_node *np,
						  const char *consumer,
						  unsigned int index)
{
	struct phy *phy;
	char *name;

	name = kasprintf(GFP_KERNEL, "%s-%u", consumer, index);
	if (!name)
		return ERR_PTR(-ENOMEM);

	phy = devm_of_phy_get(dev, np, name);
	kfree(name);

	if (IS_ERR(phy) && PTR_ERR(phy) == -ENODEV)
		phy = NULL;

	return phy;
}