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
struct net_device {int dummy; } ;
struct au1000_private {int mac_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int MAC_EN_CLOCK_ENABLE ; 
 int MAC_EN_RESET0 ; 
 int MAC_EN_RESET1 ; 
 int MAC_EN_RESET2 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct au1000_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1000_enable_mac(struct net_device *dev, int force_reset)
{
	unsigned long flags;
	struct au1000_private *aup = netdev_priv(dev);

	spin_lock_irqsave(&aup->lock, flags);

	if (force_reset || (!aup->mac_enabled)) {
		writel(MAC_EN_CLOCK_ENABLE, aup->enable);
		wmb(); /* drain writebuffer */
		mdelay(2);
		writel((MAC_EN_RESET0 | MAC_EN_RESET1 | MAC_EN_RESET2
				| MAC_EN_CLOCK_ENABLE), aup->enable);
		wmb(); /* drain writebuffer */
		mdelay(2);

		aup->mac_enabled = 1;
	}

	spin_unlock_irqrestore(&aup->lock, flags);
}