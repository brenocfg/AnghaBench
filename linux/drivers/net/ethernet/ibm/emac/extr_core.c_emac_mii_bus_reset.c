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
struct emac_instance {int dummy; } ;

/* Variables and functions */
 int emac_reset (struct emac_instance*) ; 
 struct emac_instance* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int emac_mii_bus_reset(struct mii_bus *bus)
{
	struct emac_instance *dev = netdev_priv(bus->priv);

	return emac_reset(dev);
}