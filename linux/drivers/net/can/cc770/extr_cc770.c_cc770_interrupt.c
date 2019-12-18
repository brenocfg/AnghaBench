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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; } ;
struct cc770_priv {int* obj_flags; int /*<<< orphan*/  (* post_irq ) (struct cc770_priv*) ;int /*<<< orphan*/  (* pre_irq ) (struct cc770_priv*) ;TYPE_1__ can; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CAN_STATE_STOPPED ; 
 int CC770_MAX_IRQ ; 
 int CC770_OBJ_FLAG_RTR ; 
 int CC770_OBJ_FLAG_RX ; 
 int CC770_OBJ_MAX ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int cc770_read_reg (struct cc770_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc770_rtr_interrupt (struct net_device*,int) ; 
 int /*<<< orphan*/  cc770_rx_interrupt (struct net_device*,int) ; 
 scalar_t__ cc770_status_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  cc770_tx_interrupt (struct net_device*,int) ; 
 int /*<<< orphan*/  interrupt ; 
 int intid2obj (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct cc770_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct cc770_priv*) ; 
 int /*<<< orphan*/  stub2 (struct cc770_priv*) ; 

__attribute__((used)) static irqreturn_t cc770_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct cc770_priv *priv = netdev_priv(dev);
	u8 intid;
	int o, n = 0;

	/* Shared interrupts and IRQ off? */
	if (priv->can.state == CAN_STATE_STOPPED)
		return IRQ_NONE;

	if (priv->pre_irq)
		priv->pre_irq(priv);

	while (n < CC770_MAX_IRQ) {
		/* Read the highest pending interrupt request */
		intid = cc770_read_reg(priv, interrupt);
		if (!intid)
			break;
		n++;

		if (intid == 1) {
			/* Exit in case of bus-off */
			if (cc770_status_interrupt(dev))
				break;
		} else {
			o = intid2obj(intid);

			if (o >= CC770_OBJ_MAX) {
				netdev_err(dev, "Unexpected interrupt id %d\n",
					   intid);
				continue;
			}

			if (priv->obj_flags[o] & CC770_OBJ_FLAG_RTR)
				cc770_rtr_interrupt(dev, o);
			else if (priv->obj_flags[o] & CC770_OBJ_FLAG_RX)
				cc770_rx_interrupt(dev, o);
			else
				cc770_tx_interrupt(dev, o);
		}
	}

	if (priv->post_irq)
		priv->post_irq(priv);

	if (n >= CC770_MAX_IRQ)
		netdev_dbg(dev, "%d messages handled in ISR", n);

	return (n) ? IRQ_HANDLED : IRQ_NONE;
}