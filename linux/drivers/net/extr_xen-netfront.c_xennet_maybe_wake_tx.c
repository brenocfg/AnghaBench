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
struct netfront_queue {int /*<<< orphan*/  id; TYPE_1__* info; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ netfront_tx_slot_available (struct netfront_queue*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xennet_maybe_wake_tx(struct netfront_queue *queue)
{
	struct net_device *dev = queue->info->netdev;
	struct netdev_queue *dev_queue = netdev_get_tx_queue(dev, queue->id);

	if (unlikely(netif_tx_queue_stopped(dev_queue)) &&
	    netfront_tx_slot_available(queue) &&
	    likely(netif_running(dev)))
		netif_tx_wake_queue(netdev_get_tx_queue(dev, queue->id));
}