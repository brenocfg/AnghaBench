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
struct netfront_queue {char* name; int tx_irq; int rx_irq; scalar_t__ tx_evtchn; TYPE_1__* info; scalar_t__ rx_evtchn; int /*<<< orphan*/  rx_irq_name; int /*<<< orphan*/  tx_irq_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  xbdev; } ;

/* Variables and functions */
 int bind_evtchn_to_irqhandler (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netfront_queue*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct netfront_queue*) ; 
 int xenbus_alloc_evtchn (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  xenbus_free_evtchn (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xennet_rx_interrupt ; 
 int /*<<< orphan*/  xennet_tx_interrupt ; 

__attribute__((used)) static int setup_netfront_split(struct netfront_queue *queue)
{
	int err;

	err = xenbus_alloc_evtchn(queue->info->xbdev, &queue->tx_evtchn);
	if (err < 0)
		goto fail;
	err = xenbus_alloc_evtchn(queue->info->xbdev, &queue->rx_evtchn);
	if (err < 0)
		goto alloc_rx_evtchn_fail;

	snprintf(queue->tx_irq_name, sizeof(queue->tx_irq_name),
		 "%s-tx", queue->name);
	err = bind_evtchn_to_irqhandler(queue->tx_evtchn,
					xennet_tx_interrupt,
					0, queue->tx_irq_name, queue);
	if (err < 0)
		goto bind_tx_fail;
	queue->tx_irq = err;

	snprintf(queue->rx_irq_name, sizeof(queue->rx_irq_name),
		 "%s-rx", queue->name);
	err = bind_evtchn_to_irqhandler(queue->rx_evtchn,
					xennet_rx_interrupt,
					0, queue->rx_irq_name, queue);
	if (err < 0)
		goto bind_rx_fail;
	queue->rx_irq = err;

	return 0;

bind_rx_fail:
	unbind_from_irqhandler(queue->tx_irq, queue);
	queue->tx_irq = 0;
bind_tx_fail:
	xenbus_free_evtchn(queue->info->xbdev, queue->rx_evtchn);
	queue->rx_evtchn = 0;
alloc_rx_evtchn_fail:
	xenbus_free_evtchn(queue->info->xbdev, queue->tx_evtchn);
	queue->tx_evtchn = 0;
fail:
	return err;
}