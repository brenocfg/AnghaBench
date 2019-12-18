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
struct phy {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct device_link {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct cdns_pcie {int phy_count; struct device_link** link; struct phy** phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_FLAG_STATELESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int cdns_pcie_enable_phy (struct cdns_pcie*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct device_link* device_link_add (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_link_del (struct device_link*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_get (struct device*,char const*) ; 
 int /*<<< orphan*/  devm_phy_put (struct device*,struct phy*) ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_string_index (struct device_node*,char*,int,char const**) ; 

int cdns_pcie_init_phy(struct device *dev, struct cdns_pcie *pcie)
{
	struct device_node *np = dev->of_node;
	int phy_count;
	struct phy **phy;
	struct device_link **link;
	int i;
	int ret;
	const char *name;

	phy_count = of_property_count_strings(np, "phy-names");
	if (phy_count < 1) {
		dev_err(dev, "no phy-names.  PHY will not be initialized\n");
		pcie->phy_count = 0;
		return 0;
	}

	phy = devm_kcalloc(dev, phy_count, sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	link = devm_kcalloc(dev, phy_count, sizeof(*link), GFP_KERNEL);
	if (!link)
		return -ENOMEM;

	for (i = 0; i < phy_count; i++) {
		of_property_read_string_index(np, "phy-names", i, &name);
		phy[i] = devm_phy_get(dev, name);
		if (IS_ERR(phy[i])) {
			ret = PTR_ERR(phy[i]);
			goto err_phy;
		}
		link[i] = device_link_add(dev, &phy[i]->dev, DL_FLAG_STATELESS);
		if (!link[i]) {
			devm_phy_put(dev, phy[i]);
			ret = -EINVAL;
			goto err_phy;
		}
	}

	pcie->phy_count = phy_count;
	pcie->phy = phy;
	pcie->link = link;

	ret =  cdns_pcie_enable_phy(pcie);
	if (ret)
		goto err_phy;

	return 0;

err_phy:
	while (--i >= 0) {
		device_link_del(link[i]);
		devm_phy_put(dev, phy[i]);
	}

	return ret;
}