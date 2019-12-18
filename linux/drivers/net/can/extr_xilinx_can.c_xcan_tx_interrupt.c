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
struct xcan_priv {unsigned int tx_head; int tx_tail; unsigned int tx_max; int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int) ;} ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  XCAN_ICR_OFFSET ; 
 int /*<<< orphan*/  XCAN_ISR_OFFSET ; 
 int XCAN_IXR_TXFEMP_MASK ; 
 int XCAN_IXR_TXOK_MASK ; 
 scalar_t__ can_get_echo_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xcan_update_error_state_after_rxtx (struct net_device*) ; 

__attribute__((used)) static void xcan_tx_interrupt(struct net_device *ndev, u32 isr)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	unsigned int frames_in_fifo;
	int frames_sent = 1; /* TXOK => at least 1 frame was sent */
	unsigned long flags;
	int retries = 0;

	/* Synchronize with xmit as we need to know the exact number
	 * of frames in the FIFO to stay in sync due to the TXFEMP
	 * handling.
	 * This also prevents a race between netif_wake_queue() and
	 * netif_stop_queue().
	 */
	spin_lock_irqsave(&priv->tx_lock, flags);

	frames_in_fifo = priv->tx_head - priv->tx_tail;

	if (WARN_ON_ONCE(frames_in_fifo == 0)) {
		/* clear TXOK anyway to avoid getting back here */
		priv->write_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_TXOK_MASK);
		spin_unlock_irqrestore(&priv->tx_lock, flags);
		return;
	}

	/* Check if 2 frames were sent (TXOK only means that at least 1
	 * frame was sent).
	 */
	if (frames_in_fifo > 1) {
		WARN_ON(frames_in_fifo > priv->tx_max);

		/* Synchronize TXOK and isr so that after the loop:
		 * (1) isr variable is up-to-date at least up to TXOK clear
		 *     time. This avoids us clearing a TXOK of a second frame
		 *     but not noticing that the FIFO is now empty and thus
		 *     marking only a single frame as sent.
		 * (2) No TXOK is left. Having one could mean leaving a
		 *     stray TXOK as we might process the associated frame
		 *     via TXFEMP handling as we read TXFEMP *after* TXOK
		 *     clear to satisfy (1).
		 */
		while ((isr & XCAN_IXR_TXOK_MASK) &&
		       !WARN_ON(++retries == 100)) {
			priv->write_reg(priv, XCAN_ICR_OFFSET,
					XCAN_IXR_TXOK_MASK);
			isr = priv->read_reg(priv, XCAN_ISR_OFFSET);
		}

		if (isr & XCAN_IXR_TXFEMP_MASK) {
			/* nothing in FIFO anymore */
			frames_sent = frames_in_fifo;
		}
	} else {
		/* single frame in fifo, just clear TXOK */
		priv->write_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_TXOK_MASK);
	}

	while (frames_sent--) {
		stats->tx_bytes += can_get_echo_skb(ndev, priv->tx_tail %
						    priv->tx_max);
		priv->tx_tail++;
		stats->tx_packets++;
	}

	netif_wake_queue(ndev);

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	can_led_event(ndev, CAN_LED_EVENT_TX);
	xcan_update_error_state_after_rxtx(ndev);
}