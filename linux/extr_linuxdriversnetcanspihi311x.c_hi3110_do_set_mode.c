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
struct TYPE_2__ {int /*<<< orphan*/  restart_ms; int /*<<< orphan*/  state; } ;
struct hi3110_priv {int restart_tx; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  after_suspend; TYPE_1__ can; } ;
typedef  enum can_mode { ____Placeholder_can_mode } can_mode ;

/* Variables and functions */
#define  CAN_MODE_START 128 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HI3110_AFTER_SUSPEND_RESTART ; 
 int /*<<< orphan*/  hi3110_clean (struct net_device*) ; 
 struct hi3110_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hi3110_do_set_mode(struct net_device *net, enum can_mode mode)
{
	struct hi3110_priv *priv = netdev_priv(net);

	switch (mode) {
	case CAN_MODE_START:
		hi3110_clean(net);
		/* We have to delay work since SPI I/O may sleep */
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		priv->restart_tx = 1;
		if (priv->can.restart_ms == 0)
			priv->after_suspend = HI3110_AFTER_SUSPEND_RESTART;
		queue_work(priv->wq, &priv->restart_work);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}