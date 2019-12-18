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
struct usbnet {int /*<<< orphan*/  net; } ;
struct mii_bus {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  asix_mdio_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asix_mdio_bus_write(struct mii_bus *bus, int phy_id, int regnum,
			       u16 val)
{
	asix_mdio_write(((struct usbnet *)bus->priv)->net, phy_id, regnum, val);
	return 0;
}