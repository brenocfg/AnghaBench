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
struct timer_list {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  base_addr; } ;
struct dev_priv {int /*<<< orphan*/  timer; int /*<<< orphan*/  chip_lock; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISALED0 ; 
 unsigned int ISALED0_LNKST ; 
 struct dev_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 unsigned int netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 struct dev_priv* priv ; 
 unsigned int read_ireg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void am79c961_timer(struct timer_list *t)
{
	struct dev_priv *priv = from_timer(priv, t, timer);
	struct net_device *dev = priv->dev;
	unsigned int lnkstat, carrier;
	unsigned long flags;

	spin_lock_irqsave(&priv->chip_lock, flags);
	lnkstat = read_ireg(dev->base_addr, ISALED0) & ISALED0_LNKST;
	spin_unlock_irqrestore(&priv->chip_lock, flags);
	carrier = netif_carrier_ok(dev);

	if (lnkstat && !carrier) {
		netif_carrier_on(dev);
		printk("%s: link up\n", dev->name);
	} else if (!lnkstat && carrier) {
		netif_carrier_off(dev);
		printk("%s: link down\n", dev->name);
	}

	mod_timer(&priv->timer, jiffies + msecs_to_jiffies(500));
}