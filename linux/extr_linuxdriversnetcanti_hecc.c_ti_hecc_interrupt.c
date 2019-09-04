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
typedef  int u32 ;
struct ti_hecc_priv {scalar_t__ tx_tail; scalar_t__ tx_head; scalar_t__ use_hecc1int; int /*<<< orphan*/  napi; int /*<<< orphan*/  mbx_lock; } ;
struct net_device_stats {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int HECC_BUS_ERROR ; 
 int /*<<< orphan*/  HECC_CANES ; 
 int HECC_CANES_BO ; 
 int HECC_CANES_EP ; 
 int HECC_CANES_EW ; 
 int /*<<< orphan*/  HECC_CANGIF0 ; 
 int /*<<< orphan*/  HECC_CANGIF1 ; 
 int HECC_CANGIF_GMIF ; 
 int /*<<< orphan*/  HECC_CANMCF ; 
 int /*<<< orphan*/  HECC_CANME ; 
 int /*<<< orphan*/  HECC_CANMIM ; 
 int /*<<< orphan*/  HECC_CANRMP ; 
 int /*<<< orphan*/  HECC_CANTA ; 
 int HECC_MAX_TX_MBOX ; 
 unsigned long HECC_SET_REG ; 
 int HECC_TX_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 int get_tx_tail_mb (struct ti_hecc_priv*) ; 
 int /*<<< orphan*/  hecc_clear_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 long hecc_read (struct ti_hecc_priv*,int /*<<< orphan*/ ) ; 
 int hecc_read_mbx (struct ti_hecc_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ti_hecc_error (struct net_device*,int,int) ; 

__attribute__((used)) static irqreturn_t ti_hecc_interrupt(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct ti_hecc_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	u32 mbxno, mbx_mask, int_status, err_status;
	unsigned long ack, flags;

	int_status = hecc_read(priv,
		(priv->use_hecc1int) ? HECC_CANGIF1 : HECC_CANGIF0);

	if (!int_status)
		return IRQ_NONE;

	err_status = hecc_read(priv, HECC_CANES);
	if (err_status & (HECC_BUS_ERROR | HECC_CANES_BO |
		HECC_CANES_EP | HECC_CANES_EW))
			ti_hecc_error(ndev, int_status, err_status);

	if (int_status & HECC_CANGIF_GMIF) {
		while (priv->tx_tail - priv->tx_head > 0) {
			mbxno = get_tx_tail_mb(priv);
			mbx_mask = BIT(mbxno);
			if (!(mbx_mask & hecc_read(priv, HECC_CANTA)))
				break;
			hecc_clear_bit(priv, HECC_CANMIM, mbx_mask);
			hecc_write(priv, HECC_CANTA, mbx_mask);
			spin_lock_irqsave(&priv->mbx_lock, flags);
			hecc_clear_bit(priv, HECC_CANME, mbx_mask);
			spin_unlock_irqrestore(&priv->mbx_lock, flags);
			stats->tx_bytes += hecc_read_mbx(priv, mbxno,
						HECC_CANMCF) & 0xF;
			stats->tx_packets++;
			can_led_event(ndev, CAN_LED_EVENT_TX);
			can_get_echo_skb(ndev, mbxno);
			--priv->tx_tail;
		}

		/* restart queue if wrap-up or if queue stalled on last pkt */
		if (((priv->tx_head == priv->tx_tail) &&
		((priv->tx_head & HECC_TX_MASK) != HECC_TX_MASK)) ||
		(((priv->tx_tail & HECC_TX_MASK) == HECC_TX_MASK) &&
		((priv->tx_head & HECC_TX_MASK) == HECC_TX_MASK)))
			netif_wake_queue(ndev);

		/* Disable RX mailbox interrupts and let NAPI reenable them */
		if (hecc_read(priv, HECC_CANRMP)) {
			ack = hecc_read(priv, HECC_CANMIM);
			ack &= BIT(HECC_MAX_TX_MBOX) - 1;
			hecc_write(priv, HECC_CANMIM, ack);
			napi_schedule(&priv->napi);
		}
	}

	/* clear all interrupt conditions - read back to avoid spurious ints */
	if (priv->use_hecc1int) {
		hecc_write(priv, HECC_CANGIF1, HECC_SET_REG);
		int_status = hecc_read(priv, HECC_CANGIF1);
	} else {
		hecc_write(priv, HECC_CANGIF0, HECC_SET_REG);
		int_status = hecc_read(priv, HECC_CANGIF0);
	}

	return IRQ_HANDLED;
}