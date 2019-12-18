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
typedef  int /*<<< orphan*/  u32 ;
struct ocelot_port {struct ocelot* ocelot; } ;
struct ocelot {int num_phys_ports; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_PGID_PGID ; 
 int /*<<< orphan*/  GENMASK (int,int /*<<< orphan*/ ) ; 
 int PGID_CPU ; 
 int /*<<< orphan*/  __dev_mc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocelot_mc_sync ; 
 int /*<<< orphan*/  ocelot_mc_unsync ; 
 int /*<<< orphan*/  ocelot_write_rix (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocelot_set_rx_mode(struct net_device *dev)
{
	struct ocelot_port *port = netdev_priv(dev);
	struct ocelot *ocelot = port->ocelot;
	int i;
	u32 val;

	/* This doesn't handle promiscuous mode because the bridge core is
	 * setting IFF_PROMISC on all slave interfaces and all frames would be
	 * forwarded to the CPU port.
	 */
	val = GENMASK(ocelot->num_phys_ports - 1, 0);
	for (i = ocelot->num_phys_ports + 1; i < PGID_CPU; i++)
		ocelot_write_rix(ocelot, val, ANA_PGID_PGID, i);

	__dev_mc_sync(dev, ocelot_mc_sync, ocelot_mc_unsync);
}