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
struct emac_instance {int /*<<< orphan*/  commac; int /*<<< orphan*/  mal; int /*<<< orphan*/  ndev; scalar_t__ mcast_pending; scalar_t__ no_mcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  __emac_set_multicast_list (struct emac_instance*) ; 
 int /*<<< orphan*/  mal_poll_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_addr_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_addr_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void emac_netif_start(struct emac_instance *dev)
{
	netif_tx_lock_bh(dev->ndev);
	netif_addr_lock(dev->ndev);
	dev->no_mcast = 0;
	if (dev->mcast_pending && netif_running(dev->ndev))
		__emac_set_multicast_list(dev);
	netif_addr_unlock(dev->ndev);
	netif_tx_unlock_bh(dev->ndev);

	netif_wake_queue(dev->ndev);

	/* NOTE: unconditional netif_wake_queue is only appropriate
	 * so long as all callers are assured to have free tx slots
	 * (taken from tg3... though the case where that is wrong is
	 *  not terribly harmful)
	 */
	mal_poll_enable(dev->mal, &dev->commac);
}