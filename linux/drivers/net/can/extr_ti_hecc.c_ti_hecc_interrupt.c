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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ state; } ;
struct ti_hecc_priv {scalar_t__ tx_tail; scalar_t__ tx_head; scalar_t__ use_hecc1int; int /*<<< orphan*/  offload; int /*<<< orphan*/  mbx_lock; TYPE_1__ can; int /*<<< orphan*/  ndev; } ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int CAN_STATE_BUS_OFF ; 
 scalar_t__ CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_PASSIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
 int /*<<< orphan*/  HECC_CANES ; 
 int HECC_CANES_FLAGS ; 
 int /*<<< orphan*/  HECC_CANGIF0 ; 
 int /*<<< orphan*/  HECC_CANGIF1 ; 
 int HECC_CANGIF_BOIF ; 
 int HECC_CANGIF_EPIF ; 
 int HECC_CANGIF_GMIF ; 
 int HECC_CANGIF_WLIF ; 
 int /*<<< orphan*/  HECC_CANGIM ; 
 int HECC_CANGIM_DEF_MASK ; 
 int /*<<< orphan*/  HECC_CANME ; 
 int /*<<< orphan*/  HECC_CANREC ; 
 int /*<<< orphan*/  HECC_CANRMP ; 
 int /*<<< orphan*/  HECC_CANTA ; 
 int /*<<< orphan*/  HECC_CANTEC ; 
 int HECC_TX_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  can_bus_off (struct net_device*) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ can_rx_offload_get_echo_skb (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  can_rx_offload_irq_offload_timestamp (int /*<<< orphan*/ *,unsigned long) ; 
 int get_tx_tail_mb (struct ti_hecc_priv*) ; 
 int /*<<< orphan*/  hecc_clear_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int hecc_read (struct ti_hecc_priv*,int /*<<< orphan*/ ) ; 
 int hecc_read_stamp (struct ti_hecc_priv*,int) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ti_hecc_change_state (struct net_device*,int,int) ; 
 int /*<<< orphan*/  ti_hecc_error (struct net_device*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t ti_hecc_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct ti_hecc_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	u32 mbxno, mbx_mask, int_status, err_status, stamp;
	unsigned long flags, rx_pending;
	u32 handled = 0;

	int_status = hecc_read(priv,
			       priv->use_hecc1int ?
			       HECC_CANGIF1 : HECC_CANGIF0);

	if (!int_status)
		return IRQ_NONE;

	err_status = hecc_read(priv, HECC_CANES);
	if (unlikely(err_status & HECC_CANES_FLAGS))
		ti_hecc_error(ndev, int_status, err_status);

	if (unlikely(int_status & HECC_CANGIM_DEF_MASK)) {
		enum can_state rx_state, tx_state;
		u32 rec = hecc_read(priv, HECC_CANREC);
		u32 tec = hecc_read(priv, HECC_CANTEC);

		if (int_status & HECC_CANGIF_WLIF) {
			handled |= HECC_CANGIF_WLIF;
			rx_state = rec >= tec ? CAN_STATE_ERROR_WARNING : 0;
			tx_state = rec <= tec ? CAN_STATE_ERROR_WARNING : 0;
			netdev_dbg(priv->ndev, "Error Warning interrupt\n");
			ti_hecc_change_state(ndev, rx_state, tx_state);
		}

		if (int_status & HECC_CANGIF_EPIF) {
			handled |= HECC_CANGIF_EPIF;
			rx_state = rec >= tec ? CAN_STATE_ERROR_PASSIVE : 0;
			tx_state = rec <= tec ? CAN_STATE_ERROR_PASSIVE : 0;
			netdev_dbg(priv->ndev, "Error passive interrupt\n");
			ti_hecc_change_state(ndev, rx_state, tx_state);
		}

		if (int_status & HECC_CANGIF_BOIF) {
			handled |= HECC_CANGIF_BOIF;
			rx_state = CAN_STATE_BUS_OFF;
			tx_state = CAN_STATE_BUS_OFF;
			netdev_dbg(priv->ndev, "Bus off interrupt\n");

			/* Disable all interrupts */
			hecc_write(priv, HECC_CANGIM, 0);
			can_bus_off(ndev);
			ti_hecc_change_state(ndev, rx_state, tx_state);
		}
	} else if (unlikely(priv->can.state != CAN_STATE_ERROR_ACTIVE)) {
		enum can_state new_state, tx_state, rx_state;
		u32 rec = hecc_read(priv, HECC_CANREC);
		u32 tec = hecc_read(priv, HECC_CANTEC);

		if (rec >= 128 || tec >= 128)
			new_state = CAN_STATE_ERROR_PASSIVE;
		else if (rec >= 96 || tec >= 96)
			new_state = CAN_STATE_ERROR_WARNING;
		else
			new_state = CAN_STATE_ERROR_ACTIVE;

		if (new_state < priv->can.state) {
			rx_state = rec >= tec ? new_state : 0;
			tx_state = rec <= tec ? new_state : 0;
			ti_hecc_change_state(ndev, rx_state, tx_state);
		}
	}

	if (int_status & HECC_CANGIF_GMIF) {
		while (priv->tx_tail - priv->tx_head > 0) {
			mbxno = get_tx_tail_mb(priv);
			mbx_mask = BIT(mbxno);
			if (!(mbx_mask & hecc_read(priv, HECC_CANTA)))
				break;
			hecc_write(priv, HECC_CANTA, mbx_mask);
			spin_lock_irqsave(&priv->mbx_lock, flags);
			hecc_clear_bit(priv, HECC_CANME, mbx_mask);
			spin_unlock_irqrestore(&priv->mbx_lock, flags);
			stamp = hecc_read_stamp(priv, mbxno);
			stats->tx_bytes +=
				can_rx_offload_get_echo_skb(&priv->offload,
							    mbxno, stamp);
			stats->tx_packets++;
			can_led_event(ndev, CAN_LED_EVENT_TX);
			--priv->tx_tail;
		}

		/* restart queue if wrap-up or if queue stalled on last pkt */
		if ((priv->tx_head == priv->tx_tail &&
		     ((priv->tx_head & HECC_TX_MASK) != HECC_TX_MASK)) ||
		    (((priv->tx_tail & HECC_TX_MASK) == HECC_TX_MASK) &&
		     ((priv->tx_head & HECC_TX_MASK) == HECC_TX_MASK)))
			netif_wake_queue(ndev);

		/* offload RX mailboxes and let NAPI deliver them */
		while ((rx_pending = hecc_read(priv, HECC_CANRMP))) {
			can_rx_offload_irq_offload_timestamp(&priv->offload,
							     rx_pending);
		}
	}

	/* clear all interrupt conditions - read back to avoid spurious ints */
	if (priv->use_hecc1int) {
		hecc_write(priv, HECC_CANGIF1, handled);
		int_status = hecc_read(priv, HECC_CANGIF1);
	} else {
		hecc_write(priv, HECC_CANGIF0, handled);
		int_status = hecc_read(priv, HECC_CANGIF0);
	}

	return IRQ_HANDLED;
}