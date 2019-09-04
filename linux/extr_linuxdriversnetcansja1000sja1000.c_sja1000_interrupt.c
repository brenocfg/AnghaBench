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
typedef  int uint8_t ;
struct TYPE_2__ {int ctrlmode; } ;
struct sja1000_priv {int (* read_reg ) (struct sja1000_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* post_irq ) (struct sja1000_priv*) ;TYPE_1__ can; int /*<<< orphan*/  (* pre_irq ) (struct sja1000_priv*) ;} ;
struct net_device_stats {int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CAN_CTRLMODE_ONE_SHOT ; 
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int IRQ_ALI ; 
 int IRQ_BEI ; 
 int IRQ_DOI ; 
 int IRQ_EI ; 
 int IRQ_EPI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IRQ_OFF ; 
 int IRQ_RI ; 
 int IRQ_TI ; 
 int IRQ_WUI ; 
 int /*<<< orphan*/  SJA1000_FI ; 
 int /*<<< orphan*/  SJA1000_IER ; 
 int /*<<< orphan*/  SJA1000_IR ; 
 int SJA1000_MAX_IRQ ; 
 int /*<<< orphan*/  SJA1000_SR ; 
 int SR_RBS ; 
 int SR_TCS ; 
 int /*<<< orphan*/  can_free_echo_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 struct sja1000_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ sja1000_err (struct net_device*,int,int) ; 
 scalar_t__ sja1000_is_absent (struct sja1000_priv*) ; 
 int /*<<< orphan*/  sja1000_rx (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct sja1000_priv*) ; 
 int stub2 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int stub3 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int stub4 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int stub5 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int stub6 (struct sja1000_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct sja1000_priv*) ; 

irqreturn_t sja1000_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct sja1000_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	uint8_t isrc, status;
	int n = 0;

	if (priv->pre_irq)
		priv->pre_irq(priv);

	/* Shared interrupts and IRQ off? */
	if (priv->read_reg(priv, SJA1000_IER) == IRQ_OFF)
		goto out;

	while ((isrc = priv->read_reg(priv, SJA1000_IR)) &&
	       (n < SJA1000_MAX_IRQ)) {

		status = priv->read_reg(priv, SJA1000_SR);
		/* check for absent controller due to hw unplug */
		if (status == 0xFF && sja1000_is_absent(priv))
			goto out;

		if (isrc & IRQ_WUI)
			netdev_warn(dev, "wakeup interrupt\n");

		if (isrc & IRQ_TI) {
			/* transmission buffer released */
			if (priv->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT &&
			    !(status & SR_TCS)) {
				stats->tx_errors++;
				can_free_echo_skb(dev, 0);
			} else {
				/* transmission complete */
				stats->tx_bytes +=
					priv->read_reg(priv, SJA1000_FI) & 0xf;
				stats->tx_packets++;
				can_get_echo_skb(dev, 0);
			}
			netif_wake_queue(dev);
			can_led_event(dev, CAN_LED_EVENT_TX);
		}
		if (isrc & IRQ_RI) {
			/* receive interrupt */
			while (status & SR_RBS) {
				sja1000_rx(dev);
				status = priv->read_reg(priv, SJA1000_SR);
				/* check for absent controller */
				if (status == 0xFF && sja1000_is_absent(priv))
					goto out;
			}
		}
		if (isrc & (IRQ_DOI | IRQ_EI | IRQ_BEI | IRQ_EPI | IRQ_ALI)) {
			/* error interrupt */
			if (sja1000_err(dev, isrc, status))
				break;
		}
		n++;
	}
out:
	if (priv->post_irq)
		priv->post_irq(priv);

	if (n >= SJA1000_MAX_IRQ)
		netdev_dbg(dev, "%d messages handled in ISR", n);

	return (n) ? IRQ_HANDLED : IRQ_NONE;
}