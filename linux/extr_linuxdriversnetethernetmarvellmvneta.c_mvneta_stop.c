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
struct net_device {int /*<<< orphan*/  irq; } ;
struct mvneta_port {int is_stopped; int /*<<< orphan*/  ports; int /*<<< orphan*/  node_dead; int /*<<< orphan*/  node_online; int /*<<< orphan*/  lock; int /*<<< orphan*/  neta_armada3700; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_NET_MVNETA_DEAD ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance_nocalls (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mvneta_port*) ; 
 int /*<<< orphan*/  free_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_cleanup_rxqs (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_cleanup_txqs (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_mdio_remove (struct mvneta_port*) ; 
 int /*<<< orphan*/  mvneta_percpu_disable ; 
 int /*<<< orphan*/  mvneta_stop_dev (struct mvneta_port*) ; 
 struct mvneta_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct mvneta_port*,int) ; 
 int /*<<< orphan*/  online_hpstate ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mvneta_stop(struct net_device *dev)
{
	struct mvneta_port *pp = netdev_priv(dev);

	if (!pp->neta_armada3700) {
		/* Inform that we are stopping so we don't want to setup the
		 * driver for new CPUs in the notifiers. The code of the
		 * notifier for CPU online is protected by the same spinlock,
		 * so when we get the lock, the notifer work is done.
		 */
		spin_lock(&pp->lock);
		pp->is_stopped = true;
		spin_unlock(&pp->lock);

		mvneta_stop_dev(pp);
		mvneta_mdio_remove(pp);

		cpuhp_state_remove_instance_nocalls(online_hpstate,
						    &pp->node_online);
		cpuhp_state_remove_instance_nocalls(CPUHP_NET_MVNETA_DEAD,
						    &pp->node_dead);
		on_each_cpu(mvneta_percpu_disable, pp, true);
		free_percpu_irq(dev->irq, pp->ports);
	} else {
		mvneta_stop_dev(pp);
		mvneta_mdio_remove(pp);
		free_irq(dev->irq, pp);
	}

	mvneta_cleanup_rxqs(pp);
	mvneta_cleanup_txqs(pp);

	return 0;
}