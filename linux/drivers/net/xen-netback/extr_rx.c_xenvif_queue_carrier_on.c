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
struct xenvif_queue {int stalled; int /*<<< orphan*/  last_rx_time; struct xenvif* vif; } ;
struct xenvif {scalar_t__ stalled_queues; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xenvif_queue_carrier_on(struct xenvif_queue *queue)
{
	struct xenvif *vif = queue->vif;

	queue->last_rx_time = jiffies; /* Reset Rx stall detection. */
	queue->stalled = false;

	/* All queues are ready? Enable the carrier. */
	spin_lock(&vif->lock);
	if (--vif->stalled_queues == 0) {
		netdev_info(vif->dev, "Guest Rx ready");
		netif_carrier_on(vif->dev);
	}
	spin_unlock(&vif->lock);
}