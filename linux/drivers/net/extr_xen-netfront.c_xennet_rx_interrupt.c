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
struct netfront_queue {int /*<<< orphan*/  napi; int /*<<< orphan*/  rx; TYPE_1__* info; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ RING_HAS_UNCONSUMED_RESPONSES (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static irqreturn_t xennet_rx_interrupt(int irq, void *dev_id)
{
	struct netfront_queue *queue = dev_id;
	struct net_device *dev = queue->info->netdev;

	if (likely(netif_carrier_ok(dev) &&
		   RING_HAS_UNCONSUMED_RESPONSES(&queue->rx)))
		napi_schedule(&queue->napi);

	return IRQ_HANDLED;
}