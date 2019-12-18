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
struct phy_device {int dummy; } ;
struct mdio_device {int flags; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int MDIO_DEVICE_FLAG_PHY ; 
 struct device* bus_find_device_by_of_node (int /*<<< orphan*/ *,struct device_node*) ; 
 int /*<<< orphan*/  mdio_bus_type ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct mdio_device* to_mdio_device (struct device*) ; 
 struct phy_device* to_phy_device (struct device*) ; 

struct phy_device *of_phy_find_device(struct device_node *phy_np)
{
	struct device *d;
	struct mdio_device *mdiodev;

	if (!phy_np)
		return NULL;

	d = bus_find_device_by_of_node(&mdio_bus_type, phy_np);
	if (d) {
		mdiodev = to_mdio_device(d);
		if (mdiodev->flags & MDIO_DEVICE_FLAG_PHY)
			return to_phy_device(d);
		put_device(d);
	}

	return NULL;
}