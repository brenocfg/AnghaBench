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
struct mii_bus {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int emac_mdio_read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int emac_mii_bus_read(struct mii_bus *bus, int addr, int regnum)
{
	int ret = emac_mdio_read(bus->priv, addr, regnum);
	/* This is a workaround for powered down ports/phys.
	 * In the wild, this was seen on the Cisco Meraki MX60(W).
	 * This hardware disables ports as part of the handoff
	 * procedure. Accessing the ports will lead to errors
	 * (-ETIMEDOUT, -EREMOTEIO) that do more harm than good.
	 */
	return ret < 0 ? 0xffff : ret;
}