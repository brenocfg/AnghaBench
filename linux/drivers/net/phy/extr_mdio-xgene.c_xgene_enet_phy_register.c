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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct phy_device*) ; 
 struct phy_device* get_phy_device (struct mii_bus*,int,int) ; 
 int /*<<< orphan*/  phy_device_free (struct phy_device*) ; 
 scalar_t__ phy_device_register (struct phy_device*) ; 

struct phy_device *xgene_enet_phy_register(struct mii_bus *bus, int phy_addr)
{
	struct phy_device *phy_dev;

	phy_dev = get_phy_device(bus, phy_addr, false);
	if (!phy_dev || IS_ERR(phy_dev))
		return NULL;

	if (phy_device_register(phy_dev))
		phy_device_free(phy_dev);

	return phy_dev;
}