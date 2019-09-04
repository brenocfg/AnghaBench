#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fwnet_packet_task {int enqueued; scalar_t__ outstanding_pkts; struct fwnet_device* dev; } ;
struct fwnet_device {int /*<<< orphan*/  lock; TYPE_2__* netdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dec_queued_datagrams (struct fwnet_device*) ; 
 int /*<<< orphan*/  fwnet_free_ptask (struct fwnet_packet_task*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fwnet_transmit_packet_failed(struct fwnet_packet_task *ptask)
{
	struct fwnet_device *dev = ptask->dev;
	unsigned long flags;
	bool free;

	spin_lock_irqsave(&dev->lock, flags);

	/* One fragment failed; don't try to send remaining fragments. */
	ptask->outstanding_pkts = 0;

	/* Check whether we or the networking TX soft-IRQ is last user. */
	free = ptask->enqueued;
	if (free)
		dec_queued_datagrams(dev);

	dev->netdev->stats.tx_dropped++;
	dev->netdev->stats.tx_errors++;

	spin_unlock_irqrestore(&dev->lock, flags);

	if (free)
		fwnet_free_ptask(ptask);
}