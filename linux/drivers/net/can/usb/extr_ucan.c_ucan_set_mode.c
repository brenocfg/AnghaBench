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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct ucan_priv {int /*<<< orphan*/  context_lock; int /*<<< orphan*/  netdev; int /*<<< orphan*/  available_tx_urbs; TYPE_1__ can; } ;
struct net_device {int dummy; } ;
typedef  enum can_mode { ____Placeholder_can_mode } can_mode ;

/* Variables and functions */
#define  CAN_MODE_START 128 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  UCAN_COMMAND_RESTART ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct ucan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int ucan_ctrl_command_out (struct ucan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucan_set_mode(struct net_device *netdev, enum can_mode mode)
{
	int ret;
	unsigned long flags;
	struct ucan_priv *up = netdev_priv(netdev);

	switch (mode) {
	case CAN_MODE_START:
		netdev_dbg(up->netdev, "restarting device\n");

		ret = ucan_ctrl_command_out(up, UCAN_COMMAND_RESTART, 0, 0);
		up->can.state = CAN_STATE_ERROR_ACTIVE;

		/* check if queue can be restarted,
		 * up->available_tx_urbs must be protected by the
		 * lock
		 */
		spin_lock_irqsave(&up->context_lock, flags);

		if (up->available_tx_urbs > 0)
			netif_wake_queue(up->netdev);

		spin_unlock_irqrestore(&up->context_lock, flags);

		return ret;
	default:
		return -EOPNOTSUPP;
	}
}