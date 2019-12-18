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
struct net_device {int dummy; } ;
struct mvpp2_port {int /*<<< orphan*/  nrxqs; int /*<<< orphan*/  ntxqs; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ETH_SS_STATS ; 
 int MVPP2_N_ETHTOOL_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mvpp2_ethtool_get_sset_count(struct net_device *dev, int sset)
{
	struct mvpp2_port *port = netdev_priv(dev);

	if (sset == ETH_SS_STATS)
		return MVPP2_N_ETHTOOL_STATS(port->ntxqs, port->nrxqs);

	return -EOPNOTSUPP;
}