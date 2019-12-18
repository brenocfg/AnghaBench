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
struct w5100_priv {int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_work; int /*<<< orphan*/  xfer_wq; TYPE_1__* ops; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ may_sleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int S0_IR_RECV ; 
 int S0_IR_SENDOK ; 
 int /*<<< orphan*/  W5100_S0_IR (struct w5100_priv*) ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct w5100_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct w5100_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_done ; 
 int /*<<< orphan*/  w5100_disable_intr (struct w5100_priv*) ; 
 int w5100_read (struct w5100_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5100_write (struct w5100_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t w5100_interrupt(int irq, void *ndev_instance)
{
	struct net_device *ndev = ndev_instance;
	struct w5100_priv *priv = netdev_priv(ndev);

	int ir = w5100_read(priv, W5100_S0_IR(priv));
	if (!ir)
		return IRQ_NONE;
	w5100_write(priv, W5100_S0_IR(priv), ir);

	if (ir & S0_IR_SENDOK) {
		netif_dbg(priv, tx_done, ndev, "tx done\n");
		netif_wake_queue(ndev);
	}

	if (ir & S0_IR_RECV) {
		w5100_disable_intr(priv);

		if (priv->ops->may_sleep)
			queue_work(priv->xfer_wq, &priv->rx_work);
		else if (napi_schedule_prep(&priv->napi))
			__napi_schedule(&priv->napi);
	}

	return IRQ_HANDLED;
}