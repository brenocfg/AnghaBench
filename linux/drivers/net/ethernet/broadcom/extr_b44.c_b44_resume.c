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
struct ssb_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct b44 {int /*<<< orphan*/  timer; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_FULL_RESET ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  b44_enable_ints (struct b44*) ; 
 int /*<<< orphan*/  b44_free_rings (struct b44*) ; 
 int /*<<< orphan*/  b44_halt (struct b44*) ; 
 int /*<<< orphan*/  b44_init_hw (struct b44*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_init_rings (struct b44*) ; 
 int /*<<< orphan*/  b44_interrupt ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int ssb_bus_powerup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* ssb_get_drvdata (struct ssb_device*) ; 

__attribute__((used)) static int b44_resume(struct ssb_device *sdev)
{
	struct net_device *dev = ssb_get_drvdata(sdev);
	struct b44 *bp = netdev_priv(dev);
	int rc = 0;

	rc = ssb_bus_powerup(sdev->bus, 0);
	if (rc) {
		dev_err(sdev->dev,
			"Failed to powerup the bus\n");
		return rc;
	}

	if (!netif_running(dev))
		return 0;

	spin_lock_irq(&bp->lock);
	b44_init_rings(bp);
	b44_init_hw(bp, B44_FULL_RESET);
	spin_unlock_irq(&bp->lock);

	/*
	 * As a shared interrupt, the handler can be called immediately. To be
	 * able to check the interrupt status the hardware must already be
	 * powered back on (b44_init_hw).
	 */
	rc = request_irq(dev->irq, b44_interrupt, IRQF_SHARED, dev->name, dev);
	if (rc) {
		netdev_err(dev, "request_irq failed\n");
		spin_lock_irq(&bp->lock);
		b44_halt(bp);
		b44_free_rings(bp);
		spin_unlock_irq(&bp->lock);
		return rc;
	}

	netif_device_attach(bp->dev);

	b44_enable_ints(bp);
	netif_wake_queue(dev);

	mod_timer(&bp->timer, jiffies + 1);

	return 0;
}