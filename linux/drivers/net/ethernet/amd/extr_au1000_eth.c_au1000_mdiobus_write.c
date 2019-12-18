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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mii_bus {struct net_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  au1000_enable_mac (struct net_device* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1000_mdio_write (struct net_device* const,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1000_mdiobus_write(struct mii_bus *bus, int phy_addr, int regnum,
				u16 value)
{
	struct net_device *const dev = bus->priv;

	/* make sure the MAC associated with this
	 * mii_bus is enabled
	 */
	au1000_enable_mac(dev, 0);

	au1000_mdio_write(dev, phy_addr, regnum, value);
	return 0;
}