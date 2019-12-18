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
struct netdev_queue {int /*<<< orphan*/  qdisc; } ;
struct net_device {int num_tx_queues; } ;
struct Qdisc {int /*<<< orphan*/  enqueue; } ;

/* Variables and functions */
 struct netdev_queue* netdev_get_tx_queue (struct net_device const*,int /*<<< orphan*/ ) ; 
 struct Qdisc* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool qdisc_tx_is_default(const struct net_device *dev)
{
	struct netdev_queue *txq;
	struct Qdisc *qdisc;

	if (dev->num_tx_queues > 1)
		return false;

	txq = netdev_get_tx_queue(dev, 0);
	qdisc = rcu_access_pointer(txq->qdisc);

	return !qdisc->enqueue;
}