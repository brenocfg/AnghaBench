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
struct w5300_priv {int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int S0_IR_RECV ; 
 int S0_IR_SENDOK ; 
 int /*<<< orphan*/  W5300_IMR ; 
 int /*<<< orphan*/  W5300_S0_IR ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct w5300_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct w5300_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  tx_done ; 
 int w5300_read (struct w5300_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5300_write (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t w5300_interrupt(int irq, void *ndev_instance)
{
	struct net_device *ndev = ndev_instance;
	struct w5300_priv *priv = netdev_priv(ndev);

	int ir = w5300_read(priv, W5300_S0_IR);
	if (!ir)
		return IRQ_NONE;
	w5300_write(priv, W5300_S0_IR, ir);

	if (ir & S0_IR_SENDOK) {
		netif_dbg(priv, tx_done, ndev, "tx done\n");
		netif_wake_queue(ndev);
	}

	if (ir & S0_IR_RECV) {
		if (napi_schedule_prep(&priv->napi)) {
			w5300_write(priv, W5300_IMR, 0);
			__napi_schedule(&priv->napi);
		}
	}

	return IRQ_HANDLED;
}