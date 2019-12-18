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
typedef  size_t u8 ;
typedef  int u32 ;
struct rcar_canfd_channel {int channel; size_t tx_tail; size_t tx_head; int /*<<< orphan*/  base; int /*<<< orphan*/  tx_lock; scalar_t__* tx_len; } ;
struct net_device_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_LED_EVENT_TX ; 
 int /*<<< orphan*/  RCANFD_CFFIFO_IDX ; 
 int /*<<< orphan*/  RCANFD_CFSTS (int,int /*<<< orphan*/ ) ; 
 size_t RCANFD_CFSTS_CFMC (int) ; 
 int RCANFD_CFSTS_CFTXIF ; 
 size_t RCANFD_FIFO_DEPTH ; 
 int /*<<< orphan*/  can_get_echo_skb (struct net_device*,size_t) ; 
 int /*<<< orphan*/  can_led_event (struct net_device*,int /*<<< orphan*/ ) ; 
 struct rcar_canfd_channel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int rcar_canfd_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_canfd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rcar_canfd_tx_done(struct net_device *ndev)
{
	struct rcar_canfd_channel *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	u32 sts;
	unsigned long flags;
	u32 ch = priv->channel;

	do {
		u8 unsent, sent;

		sent = priv->tx_tail % RCANFD_FIFO_DEPTH;
		stats->tx_packets++;
		stats->tx_bytes += priv->tx_len[sent];
		priv->tx_len[sent] = 0;
		can_get_echo_skb(ndev, sent);

		spin_lock_irqsave(&priv->tx_lock, flags);
		priv->tx_tail++;
		sts = rcar_canfd_read(priv->base,
				      RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX));
		unsent = RCANFD_CFSTS_CFMC(sts);

		/* Wake producer only when there is room */
		if (unsent != RCANFD_FIFO_DEPTH)
			netif_wake_queue(ndev);

		if (priv->tx_head - priv->tx_tail <= unsent) {
			spin_unlock_irqrestore(&priv->tx_lock, flags);
			break;
		}
		spin_unlock_irqrestore(&priv->tx_lock, flags);

	} while (1);

	/* Clear interrupt */
	rcar_canfd_write(priv->base, RCANFD_CFSTS(ch, RCANFD_CFFIFO_IDX),
			 sts & ~RCANFD_CFSTS_CFTXIF);
	can_led_event(ndev, CAN_LED_EVENT_TX);
}