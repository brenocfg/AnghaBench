#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct b43legacy_wldev {TYPE_2__* wl; int /*<<< orphan*/  irq_mask; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_GEN_IRQ_MASK ; 
 scalar_t__ B43legacy_STAT_INITIALIZED ; 
 int /*<<< orphan*/  B43legacy_STAT_STARTED ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  b43legacy_interrupt_handler ; 
 int /*<<< orphan*/  b43legacy_mac_enable (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_periodic_tasks_setup (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_set_status (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacydbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  b43legacyerr (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drain_txstatus_queue (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct b43legacy_wldev*) ; 

__attribute__((used)) static int b43legacy_wireless_core_start(struct b43legacy_wldev *dev)
{
	int err;

	B43legacy_WARN_ON(b43legacy_status(dev) != B43legacy_STAT_INITIALIZED);

	drain_txstatus_queue(dev);
	err = request_irq(dev->dev->irq, b43legacy_interrupt_handler,
			  IRQF_SHARED, KBUILD_MODNAME, dev);
	if (err) {
		b43legacyerr(dev->wl, "Cannot request IRQ-%d\n",
		       dev->dev->irq);
		goto out;
	}
	/* We are ready to run. */
	ieee80211_wake_queues(dev->wl->hw);
	b43legacy_set_status(dev, B43legacy_STAT_STARTED);

	/* Start data flow (TX/RX) */
	b43legacy_mac_enable(dev);
	b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_MASK, dev->irq_mask);

	/* Start maintenance work */
	b43legacy_periodic_tasks_setup(dev);

	b43legacydbg(dev->wl, "Wireless interface started\n");
out:
	return err;
}