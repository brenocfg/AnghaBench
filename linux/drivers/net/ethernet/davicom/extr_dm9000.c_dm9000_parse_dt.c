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
struct dm9000_plat_data {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  flags; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  DM9000_PLATF_EXT_PHY ; 
 int /*<<< orphan*/  DM9000_PLATF_NO_EEPROM ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENXIO ; 
 struct dm9000_plat_data* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (void const*) ; 
 struct dm9000_plat_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,void const*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 void* of_get_mac_address (struct device_node*) ; 

__attribute__((used)) static struct dm9000_plat_data *dm9000_parse_dt(struct device *dev)
{
	struct dm9000_plat_data *pdata;
	struct device_node *np = dev->of_node;
	const void *mac_addr;

	if (!IS_ENABLED(CONFIG_OF) || !np)
		return ERR_PTR(-ENXIO);

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return ERR_PTR(-ENOMEM);

	if (of_find_property(np, "davicom,ext-phy", NULL))
		pdata->flags |= DM9000_PLATF_EXT_PHY;
	if (of_find_property(np, "davicom,no-eeprom", NULL))
		pdata->flags |= DM9000_PLATF_NO_EEPROM;

	mac_addr = of_get_mac_address(np);
	if (!IS_ERR(mac_addr))
		ether_addr_copy(pdata->dev_addr, mac_addr);

	return pdata;
}