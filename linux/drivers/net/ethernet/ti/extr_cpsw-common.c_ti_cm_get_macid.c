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
typedef  int /*<<< orphan*/  u8 ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOENT ; 
 int cpsw_am33xx_cm_get_macid (struct device*,int,int,int /*<<< orphan*/ *) ; 
 int davinci_emac_3517_get_macid (struct device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 

int ti_cm_get_macid(struct device *dev, int slave, u8 *mac_addr)
{
	if (of_machine_is_compatible("ti,dm8148"))
		return cpsw_am33xx_cm_get_macid(dev, 0x630, slave, mac_addr);

	if (of_machine_is_compatible("ti,am33xx"))
		return cpsw_am33xx_cm_get_macid(dev, 0x630, slave, mac_addr);

	if (of_device_is_compatible(dev->of_node, "ti,am3517-emac"))
		return davinci_emac_3517_get_macid(dev, 0x110, slave, mac_addr);

	if (of_device_is_compatible(dev->of_node, "ti,dm816-emac"))
		return cpsw_am33xx_cm_get_macid(dev, 0x30, slave, mac_addr);

	if (of_machine_is_compatible("ti,am43"))
		return cpsw_am33xx_cm_get_macid(dev, 0x630, slave, mac_addr);

	if (of_machine_is_compatible("ti,dra7"))
		return davinci_emac_3517_get_macid(dev, 0x514, slave, mac_addr);

	dev_info(dev, "incompatible machine/device type for reading mac address\n");
	return -ENOENT;
}