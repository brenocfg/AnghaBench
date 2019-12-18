#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rhine_private {int quirks; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ dev_is_pci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct rhine_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rhine_chip_reset (struct net_device*) ; 
 int /*<<< orphan*/  rhine_reload_eeprom (long,struct net_device*) ; 
 int rqRhineI ; 

__attribute__((used)) static void rhine_hw_init(struct net_device *dev, long pioaddr)
{
	struct rhine_private *rp = netdev_priv(dev);

	/* Reset the chip to erase previous misconfiguration. */
	rhine_chip_reset(dev);

	/* Rhine-I needs extra time to recuperate before EEPROM reload */
	if (rp->quirks & rqRhineI)
		msleep(5);

	/* Reload EEPROM controlled bytes cleared by soft reset */
	if (dev_is_pci(dev->dev.parent))
		rhine_reload_eeprom(pioaddr, dev);
}