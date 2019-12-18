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
 int bcm_enet_mdio_read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int bcm_enet_mdio_read_phylib(struct mii_bus *bus, int mii_id,
				     int regnum)
{
	return bcm_enet_mdio_read(bus->priv, mii_id, regnum);
}