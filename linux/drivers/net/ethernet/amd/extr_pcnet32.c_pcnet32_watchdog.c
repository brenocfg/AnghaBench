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
struct pcnet32_private {int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  lock; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCNET32_WATCHDOG_TIMEOUT ; 
 struct pcnet32_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct pcnet32_private* lp ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcnet32_check_media (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  watchdog_timer ; 

__attribute__((used)) static void pcnet32_watchdog(struct timer_list *t)
{
	struct pcnet32_private *lp = from_timer(lp, t, watchdog_timer);
	struct net_device *dev = lp->dev;
	unsigned long flags;

	/* Print the link status if it has changed */
	spin_lock_irqsave(&lp->lock, flags);
	pcnet32_check_media(dev, 0);
	spin_unlock_irqrestore(&lp->lock, flags);

	mod_timer(&lp->watchdog_timer, round_jiffies(PCNET32_WATCHDOG_TIMEOUT));
}