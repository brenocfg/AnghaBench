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
typedef  int /*<<< orphan*/  u64 ;
struct ocelot_port {int chip_port; struct ocelot* ocelot; } ;
struct ocelot {int num_stats; int /*<<< orphan*/ * stats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocelot_update_stats (struct ocelot*) ; 

__attribute__((used)) static void ocelot_get_ethtool_stats(struct net_device *dev,
				     struct ethtool_stats *stats, u64 *data)
{
	struct ocelot_port *port = netdev_priv(dev);
	struct ocelot *ocelot = port->ocelot;
	int i;

	/* check and update now */
	ocelot_update_stats(ocelot);

	/* Copy all counters */
	for (i = 0; i < ocelot->num_stats; i++)
		*data++ = ocelot->stats[port->chip_port * ocelot->num_stats + i];
}