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
struct net_device {int flags; } ;
struct lance_private {scalar_t__ tx_old; scalar_t__ tx_new; struct lance_init_block* init_block; } ;
struct lance_init_block {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  LE_MO_PROM ; 
 int /*<<< orphan*/  WRITERAP (struct lance_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITERDP (struct lance_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_restart_lance (struct lance_private*) ; 
 int /*<<< orphan*/  lance_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  lance_load_multicast (struct net_device*) ; 
 int /*<<< orphan*/  load_csrs (struct lance_private*) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule () ; 

void lance_set_multicast(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_init_block *ib = lp->init_block;
	int stopped;

	stopped = netif_queue_stopped(dev);
	if (!stopped)
		netif_stop_queue(dev);

	while (lp->tx_old != lp->tx_new)
		schedule();

	WRITERAP(lp, LE_CSR0);
	WRITERDP(lp, LE_C0_STOP);
	lance_init_ring(dev);

	if (dev->flags & IFF_PROMISC) {
		ib->mode |= LE_MO_PROM;
	} else {
		ib->mode &= ~LE_MO_PROM;
		lance_load_multicast(dev);
	}
	load_csrs(lp);
	init_restart_lance(lp);

	if (!stopped)
		netif_start_queue(dev);
}