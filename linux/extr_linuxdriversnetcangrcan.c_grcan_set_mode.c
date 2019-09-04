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
struct net_device {int dummy; } ;
struct TYPE_2__ {int ctrlmode; } ;
struct grcan_priv {int /*<<< orphan*/  lock; TYPE_1__ can; scalar_t__ resetting; scalar_t__ closing; } ;
typedef  enum can_mode { ____Placeholder_can_mode } can_mode ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_MODE_START ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  grcan_start (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct grcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int grcan_set_mode(struct net_device *dev, enum can_mode mode)
{
	struct grcan_priv *priv = netdev_priv(dev);
	unsigned long flags;
	int err = 0;

	if (mode == CAN_MODE_START) {
		/* This might be called to restart the device to recover from
		 * bus off errors
		 */
		spin_lock_irqsave(&priv->lock, flags);
		if (priv->closing || priv->resetting) {
			err = -EBUSY;
		} else {
			netdev_info(dev, "Restarting device\n");
			grcan_start(dev);
			if (!(priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
				netif_wake_queue(dev);
		}
		spin_unlock_irqrestore(&priv->lock, flags);
		return err;
	}
	return -EOPNOTSUPP;
}