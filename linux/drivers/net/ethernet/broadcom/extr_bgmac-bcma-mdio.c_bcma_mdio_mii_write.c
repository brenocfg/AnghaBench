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
struct mii_bus {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int bcma_mdio_phy_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcma_mdio_mii_write(struct mii_bus *bus, int mii_id, int regnum,
			       u16 value)
{
	return bcma_mdio_phy_write(bus->priv, mii_id, regnum, value);
}