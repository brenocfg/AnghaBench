#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct spi_device {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_3__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_error; } ;
struct TYPE_5__ {int state; scalar_t__ restart_ms; int ctrlmode; TYPE_1__ can_stats; } ;
struct hi3110_priv {int force_quit; int tx_len; int /*<<< orphan*/  hi3110_lock; struct net_device* net; TYPE_2__ can; struct spi_device* spi; } ;
struct can_frame {int* data; int can_id; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_PROT ; 
 int CAN_ERR_PROT_BIT ; 
 int CAN_ERR_PROT_FORM ; 
 int CAN_ERR_PROT_LOC_ACK ; 
 int CAN_ERR_PROT_LOC_CRC_SEQ ; 
 int CAN_ERR_PROT_STUFF ; 
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int CAN_STATE_BUS_OFF ; 
 int CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_PASSIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
 int HI3110_ERR_ACKERR ; 
 int HI3110_ERR_BITERR ; 
 int HI3110_ERR_BUSOFF ; 
 int HI3110_ERR_CRCERR ; 
 int HI3110_ERR_FRMERR ; 
 int HI3110_ERR_PASSIVE_MASK ; 
 int HI3110_ERR_PROTOCOL_MASK ; 
 int HI3110_ERR_STUFERR ; 
 int HI3110_INT_BUSERR ; 
 int /*<<< orphan*/  HI3110_READ_ERR ; 
 int /*<<< orphan*/  HI3110_READ_INTF ; 
 int /*<<< orphan*/  HI3110_READ_REC ; 
 int /*<<< orphan*/  HI3110_READ_STATF ; 
 int /*<<< orphan*/  HI3110_READ_TEC ; 
 int HI3110_STAT_ERRW ; 
 int HI3110_STAT_RXFMTY ; 
 int HI3110_STAT_TXMTY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int /*<<< orphan*/  can_change_state (struct net_device*,struct can_frame*,int,int) ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi3110_hw_rx (struct spi_device*) ; 
 int /*<<< orphan*/  hi3110_hw_sleep (struct spi_device*) ; 
 void* hi3110_read (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static irqreturn_t hi3110_can_ist(int irq, void *dev_id)
{
	struct hi3110_priv *priv = dev_id;
	struct spi_device *spi = priv->spi;
	struct net_device *net = priv->net;

	mutex_lock(&priv->hi3110_lock);

	while (!priv->force_quit) {
		enum can_state new_state;
		u8 intf, eflag, statf;

		while (!(HI3110_STAT_RXFMTY &
			 (statf = hi3110_read(spi, HI3110_READ_STATF)))) {
			hi3110_hw_rx(spi);
		}

		intf = hi3110_read(spi, HI3110_READ_INTF);
		eflag = hi3110_read(spi, HI3110_READ_ERR);
		/* Update can state */
		if (eflag & HI3110_ERR_BUSOFF)
			new_state = CAN_STATE_BUS_OFF;
		else if (eflag & HI3110_ERR_PASSIVE_MASK)
			new_state = CAN_STATE_ERROR_PASSIVE;
		else if (statf & HI3110_STAT_ERRW)
			new_state = CAN_STATE_ERROR_WARNING;
		else
			new_state = CAN_STATE_ERROR_ACTIVE;

		if (new_state != priv->can.state) {
			struct can_frame *cf;
			struct sk_buff *skb;
			enum can_state rx_state, tx_state;
			u8 rxerr, txerr;

			skb = alloc_can_err_skb(net, &cf);
			if (!skb)
				break;

			txerr = hi3110_read(spi, HI3110_READ_TEC);
			rxerr = hi3110_read(spi, HI3110_READ_REC);
			cf->data[6] = txerr;
			cf->data[7] = rxerr;
			tx_state = txerr >= rxerr ? new_state : 0;
			rx_state = txerr <= rxerr ? new_state : 0;
			can_change_state(net, cf, tx_state, rx_state);
			netif_rx_ni(skb);

			if (new_state == CAN_STATE_BUS_OFF) {
				can_bus_off(net);
				if (priv->can.restart_ms == 0) {
					priv->force_quit = 1;
					hi3110_hw_sleep(spi);
					break;
				}
			}
		}

		/* Update bus errors */
		if ((intf & HI3110_INT_BUSERR) &&
		    (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)) {
			struct can_frame *cf;
			struct sk_buff *skb;

			/* Check for protocol errors */
			if (eflag & HI3110_ERR_PROTOCOL_MASK) {
				skb = alloc_can_err_skb(net, &cf);
				if (!skb)
					break;

				cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
				priv->can.can_stats.bus_error++;
				priv->net->stats.rx_errors++;
				if (eflag & HI3110_ERR_BITERR)
					cf->data[2] |= CAN_ERR_PROT_BIT;
				else if (eflag & HI3110_ERR_FRMERR)
					cf->data[2] |= CAN_ERR_PROT_FORM;
				else if (eflag & HI3110_ERR_STUFERR)
					cf->data[2] |= CAN_ERR_PROT_STUFF;
				else if (eflag & HI3110_ERR_CRCERR)
					cf->data[3] |= CAN_ERR_PROT_LOC_CRC_SEQ;
				else if (eflag & HI3110_ERR_ACKERR)
					cf->data[3] |= CAN_ERR_PROT_LOC_ACK;

				cf->data[6] = hi3110_read(spi, HI3110_READ_TEC);
				cf->data[7] = hi3110_read(spi, HI3110_READ_REC);
				netdev_dbg(priv->net, "Bus Error\n");
				netif_rx_ni(skb);
			}
		}

		if (priv->tx_len && statf & HI3110_STAT_TXMTY) {
			net->stats.tx_packets++;
			net->stats.tx_bytes += priv->tx_len - 1;
			can_led_event(net, CAN_LED_EVENT_TX);
			if (priv->tx_len) {
				can_get_echo_skb(net, 0);
				priv->tx_len = 0;
			}
			netif_wake_queue(net);
		}

		if (intf == 0)
			break;
	}
	mutex_unlock(&priv->hi3110_lock);
	return IRQ_HANDLED;
}