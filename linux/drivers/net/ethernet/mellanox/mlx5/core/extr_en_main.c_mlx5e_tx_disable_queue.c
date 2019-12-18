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
struct netdev_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netif_tx_lock_bh (struct netdev_queue*) ; 
 int /*<<< orphan*/  __netif_tx_unlock_bh (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 

void mlx5e_tx_disable_queue(struct netdev_queue *txq)
{
	__netif_tx_lock_bh(txq);
	netif_tx_stop_queue(txq);
	__netif_tx_unlock_bh(txq);
}