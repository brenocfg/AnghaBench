#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct can_frame {scalar_t__ can_dlc; } ;
struct TYPE_4__ {int state; } ;
struct at91_priv {TYPE_2__ can; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int AT91_IRQ_BOFF ; 
 int AT91_IRQ_ERRA ; 
 int AT91_IRQ_ERRP ; 
 int AT91_IRQ_WARN ; 
 int /*<<< orphan*/  AT91_SR ; 
 int CAN_STATE_BUS_OFF ; 
 int CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_PASSIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int at91_get_state_by_bec (struct net_device*,int*) ; 
 int /*<<< orphan*/  at91_irq_err_state (struct net_device*,struct can_frame*,int) ; 
 scalar_t__ at91_is_sam9263 (struct at91_priv*) ; 
 int at91_read (struct at91_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct at91_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void at91_irq_err(struct net_device *dev)
{
	struct at91_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	struct can_frame *cf;
	enum can_state new_state;
	u32 reg_sr;
	int err;

	if (at91_is_sam9263(priv)) {
		reg_sr = at91_read(priv, AT91_SR);

		/* we need to look at the unmasked reg_sr */
		if (unlikely(reg_sr & AT91_IRQ_BOFF))
			new_state = CAN_STATE_BUS_OFF;
		else if (unlikely(reg_sr & AT91_IRQ_ERRP))
			new_state = CAN_STATE_ERROR_PASSIVE;
		else if (unlikely(reg_sr & AT91_IRQ_WARN))
			new_state = CAN_STATE_ERROR_WARNING;
		else if (likely(reg_sr & AT91_IRQ_ERRA))
			new_state = CAN_STATE_ERROR_ACTIVE;
		else {
			netdev_err(dev, "BUG! hardware in undefined state\n");
			return;
		}
	} else {
		err = at91_get_state_by_bec(dev, &new_state);
		if (err)
			return;
	}

	/* state hasn't changed */
	if (likely(new_state == priv->can.state))
		return;

	skb = alloc_can_err_skb(dev, &cf);
	if (unlikely(!skb))
		return;

	at91_irq_err_state(dev, cf, new_state);

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += cf->can_dlc;
	netif_rx(skb);

	priv->can.state = new_state;
}