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
struct b43legacy_wldev {TYPE_1__* dev; int /*<<< orphan*/  periodic_work; struct b43legacy_wl* wl; } ;
struct b43legacy_wl {int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_GEN_IRQ_MASK ; 
 int B43legacy_QOS_QUEUE_NUM ; 
 int /*<<< orphan*/  B43legacy_STAT_INITIALIZED ; 
 scalar_t__ B43legacy_STAT_STARTED ; 
 int /*<<< orphan*/  b43legacy_mac_suspend (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_set_status (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_synchronize_irq (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacydbg (struct b43legacy_wl*,char*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void b43legacy_wireless_core_stop(struct b43legacy_wldev *dev)
{
	struct b43legacy_wl *wl = dev->wl;
	unsigned long flags;
	int queue_num;

	if (b43legacy_status(dev) < B43legacy_STAT_STARTED)
		return;

	/* Disable and sync interrupts. We must do this before than
	 * setting the status to INITIALIZED, as the interrupt handler
	 * won't care about IRQs then. */
	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);
	b43legacy_read32(dev, B43legacy_MMIO_GEN_IRQ_MASK); /* flush */
	spin_unlock_irqrestore(&wl->irq_lock, flags);
	b43legacy_synchronize_irq(dev);

	b43legacy_set_status(dev, B43legacy_STAT_INITIALIZED);

	mutex_unlock(&wl->mutex);
	/* Must unlock as it would otherwise deadlock. No races here.
	 * Cancel the possibly running self-rearming periodic work. */
	cancel_delayed_work_sync(&dev->periodic_work);
	cancel_work_sync(&wl->tx_work);
	mutex_lock(&wl->mutex);

	/* Drain all TX queues. */
	for (queue_num = 0; queue_num < B43legacy_QOS_QUEUE_NUM; queue_num++) {
		while (skb_queue_len(&wl->tx_queue[queue_num]))
			dev_kfree_skb(skb_dequeue(&wl->tx_queue[queue_num]));
	}

b43legacy_mac_suspend(dev);
	free_irq(dev->dev->irq, dev);
	b43legacydbg(wl, "Wireless interface stopped\n");
}