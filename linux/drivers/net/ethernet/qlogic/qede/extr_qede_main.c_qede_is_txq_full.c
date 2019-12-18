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
struct qede_tx_queue {int /*<<< orphan*/  ndev_txq_id; } ;
struct qede_dev {int /*<<< orphan*/  ndev; } ;
struct netdev_queue {int dummy; } ;

/* Variables and functions */
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_xmit_stopped (struct netdev_queue*) ; 

__attribute__((used)) static bool qede_is_txq_full(struct qede_dev *edev, struct qede_tx_queue *txq)
{
	struct netdev_queue *netdev_txq;

	netdev_txq = netdev_get_tx_queue(edev->ndev, txq->ndev_txq_id);
	if (netif_xmit_stopped(netdev_txq))
		return true;

	return false;
}