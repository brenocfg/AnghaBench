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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct board_info {int wake_state; int /*<<< orphan*/  irq_wake; int /*<<< orphan*/  addr_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  wake_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_WCR ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int WAKE_MAGIC ; 
 int WCR_MAGICEN ; 
 int /*<<< orphan*/  iow (struct board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_set_irq_wake (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct board_info* to_dm9000_board (struct net_device*) ; 

__attribute__((used)) static int dm9000_set_wol(struct net_device *dev, struct ethtool_wolinfo *w)
{
	struct board_info *dm = to_dm9000_board(dev);
	unsigned long flags;
	u32 opts = w->wolopts;
	u32 wcr = 0;

	if (!dm->wake_supported)
		return -EOPNOTSUPP;

	if (opts & ~WAKE_MAGIC)
		return -EINVAL;

	if (opts & WAKE_MAGIC)
		wcr |= WCR_MAGICEN;

	mutex_lock(&dm->addr_lock);

	spin_lock_irqsave(&dm->lock, flags);
	iow(dm, DM9000_WCR, wcr);
	spin_unlock_irqrestore(&dm->lock, flags);

	mutex_unlock(&dm->addr_lock);

	if (dm->wake_state != opts) {
		/* change in wol state, update IRQ state */

		if (!dm->wake_state)
			irq_set_irq_wake(dm->irq_wake, 1);
		else if (dm->wake_state && !opts)
			irq_set_irq_wake(dm->irq_wake, 0);
	}

	dm->wake_state = opts;
	return 0;
}