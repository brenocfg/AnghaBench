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
struct ql3_adapter {int /*<<< orphan*/  tx_timeout_work; int /*<<< orphan*/  workqueue; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct ql3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql3xxx_tx_timeout(struct net_device *ndev)
{
	struct ql3_adapter *qdev = netdev_priv(ndev);

	netdev_err(ndev, "Resetting...\n");
	/*
	 * Stop the queues, we've got a problem.
	 */
	netif_stop_queue(ndev);

	/*
	 * Wake up the worker to process this event.
	 */
	queue_delayed_work(qdev->workqueue, &qdev->tx_timeout_work, 0);
}