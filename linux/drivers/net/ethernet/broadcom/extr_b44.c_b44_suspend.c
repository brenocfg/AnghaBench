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
struct ssb_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; } ;
struct b44 {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int B44_FLAG_WOL_ENABLE ; 
 int /*<<< orphan*/  B44_PARTIAL_RESET ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  b44_free_rings (struct b44*) ; 
 int /*<<< orphan*/  b44_halt (struct b44*) ; 
 int /*<<< orphan*/  b44_init_hw (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_setup_wol (struct b44*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct net_device* ssb_get_drvdata (struct ssb_device*) ; 
 int /*<<< orphan*/  ssb_pcihost_set_power_state (struct ssb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b44_suspend(struct ssb_device *sdev, pm_message_t state)
{
	struct net_device *dev = ssb_get_drvdata(sdev);
	struct b44 *bp = netdev_priv(dev);

	if (!netif_running(dev))
		return 0;

	del_timer_sync(&bp->timer);

	spin_lock_irq(&bp->lock);

	b44_halt(bp);
	netif_carrier_off(bp->dev);
	netif_device_detach(bp->dev);
	b44_free_rings(bp);

	spin_unlock_irq(&bp->lock);

	free_irq(dev->irq, dev);
	if (bp->flags & B44_FLAG_WOL_ENABLE) {
		b44_init_hw(bp, B44_PARTIAL_RESET);
		b44_setup_wol(bp);
	}

	ssb_pcihost_set_power_state(sdev, PCI_D3hot);
	return 0;
}