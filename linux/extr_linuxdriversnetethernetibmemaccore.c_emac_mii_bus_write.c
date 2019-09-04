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
 int /*<<< orphan*/  emac_mdio_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emac_mii_bus_write(struct mii_bus *bus, int addr,
			      int regnum, u16 val)
{
	emac_mdio_write(bus->priv, addr, regnum, val);
	return 0;
}