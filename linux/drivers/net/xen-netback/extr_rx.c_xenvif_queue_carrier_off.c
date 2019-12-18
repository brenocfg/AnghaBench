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
struct xenvif_queue {int stalled; struct xenvif* vif; } ;
struct xenvif {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  stalled_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xenvif_queue_carrier_off(struct xenvif_queue *queue)
{
	struct xenvif *vif = queue->vif;

	queue->stalled = true;

	/* At least one queue has stalled? Disable the carrier. */
	spin_lock(&vif->lock);
	if (vif->stalled_queues++ == 0) {
		netdev_info(vif->dev, "Guest Rx stalled");
		netif_carrier_off(vif->dev);
	}
	spin_unlock(&vif->lock);
}