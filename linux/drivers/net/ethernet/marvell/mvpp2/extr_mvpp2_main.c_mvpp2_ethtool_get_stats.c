#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct mvpp2_port {int /*<<< orphan*/  gather_stats_lock; int /*<<< orphan*/  nrxqs; int /*<<< orphan*/  ntxqs; int /*<<< orphan*/  ethtool_stats; TYPE_1__ stats_work; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int MVPP2_N_ETHTOOL_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_gather_hw_statistics (int /*<<< orphan*/ *) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mvpp2_ethtool_get_stats(struct net_device *dev,
				    struct ethtool_stats *stats, u64 *data)
{
	struct mvpp2_port *port = netdev_priv(dev);

	/* Update statistics for the given port, then take the lock to avoid
	 * concurrent accesses on the ethtool_stats structure during its copy.
	 */
	mvpp2_gather_hw_statistics(&port->stats_work.work);

	mutex_lock(&port->gather_stats_lock);
	memcpy(data, port->ethtool_stats,
	       sizeof(u64) * MVPP2_N_ETHTOOL_STATS(port->ntxqs, port->nrxqs));
	mutex_unlock(&port->gather_stats_lock);
}