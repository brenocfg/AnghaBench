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
struct alx_tx_queue {int /*<<< orphan*/  queue_idx; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netdev_queue *alx_get_tx_queue(const struct alx_tx_queue *txq)
{
	return netdev_get_tx_queue(txq->netdev, txq->queue_idx);
}