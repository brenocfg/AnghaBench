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
struct emac_instance {int no_mcast; int /*<<< orphan*/  ndev; int /*<<< orphan*/  commac; int /*<<< orphan*/  mal; } ;

/* Variables and functions */
 int /*<<< orphan*/  mal_poll_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_addr_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_addr_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void emac_netif_stop(struct emac_instance *dev)
{
	netif_tx_lock_bh(dev->ndev);
	netif_addr_lock(dev->ndev);
	dev->no_mcast = 1;
	netif_addr_unlock(dev->ndev);
	netif_tx_unlock_bh(dev->ndev);
	netif_trans_update(dev->ndev);	/* prevent tx timeout */
	mal_poll_disable(dev->mal, &dev->commac);
	netif_tx_disable(dev->ndev);
}