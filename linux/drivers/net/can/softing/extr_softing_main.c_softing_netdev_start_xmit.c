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
typedef  int uint8_t ;
struct TYPE_5__ {scalar_t__ pending; scalar_t__ echo_put; } ;
struct softing_priv {TYPE_2__ tx; scalar_t__ index; struct softing* card; } ;
struct TYPE_6__ {scalar_t__ pending; scalar_t__ last_bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  up; } ;
struct softing {struct net_device** net; TYPE_3__ tx; int /*<<< orphan*/  spin; int /*<<< orphan*/ * dpram; TYPE_1__ fw; } ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct can_frame {int can_id; int /*<<< orphan*/  can_dlc; int /*<<< orphan*/ * data; } ;
typedef  int netdev_tx_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ARRAY_SIZE (struct net_device**) ; 
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int CMD_BUS2 ; 
 int CMD_RTR ; 
 int CMD_TX ; 
 int CMD_XTD ; 
 int DPRAM_TX ; 
 int DPRAM_TX_CNT ; 
 size_t DPRAM_TX_RD ; 
 int DPRAM_TX_SIZE ; 
 size_t DPRAM_TX_WR ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ TXMAX ; 
 scalar_t__ TX_ECHO_SKB_MAX ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,scalar_t__) ; 
 int ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 struct softing_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t softing_netdev_start_xmit(struct sk_buff *skb,
		struct net_device *dev)
{
	struct softing_priv *priv = netdev_priv(dev);
	struct softing *card = priv->card;
	int ret;
	uint8_t *ptr;
	uint8_t fifo_wr, fifo_rd;
	struct can_frame *cf = (struct can_frame *)skb->data;
	uint8_t buf[DPRAM_TX_SIZE];

	if (can_dropped_invalid_skb(dev, skb))
		return NETDEV_TX_OK;

	spin_lock(&card->spin);

	ret = NETDEV_TX_BUSY;
	if (!card->fw.up ||
			(card->tx.pending >= TXMAX) ||
			(priv->tx.pending >= TX_ECHO_SKB_MAX))
		goto xmit_done;
	fifo_wr = ioread8(&card->dpram[DPRAM_TX_WR]);
	fifo_rd = ioread8(&card->dpram[DPRAM_TX_RD]);
	if (fifo_wr == fifo_rd)
		/* fifo full */
		goto xmit_done;
	memset(buf, 0, sizeof(buf));
	ptr = buf;
	*ptr = CMD_TX;
	if (cf->can_id & CAN_RTR_FLAG)
		*ptr |= CMD_RTR;
	if (cf->can_id & CAN_EFF_FLAG)
		*ptr |= CMD_XTD;
	if (priv->index)
		*ptr |= CMD_BUS2;
	++ptr;
	*ptr++ = cf->can_dlc;
	*ptr++ = (cf->can_id >> 0);
	*ptr++ = (cf->can_id >> 8);
	if (cf->can_id & CAN_EFF_FLAG) {
		*ptr++ = (cf->can_id >> 16);
		*ptr++ = (cf->can_id >> 24);
	} else {
		/* increment 1, not 2 as you might think */
		ptr += 1;
	}
	if (!(cf->can_id & CAN_RTR_FLAG))
		memcpy(ptr, &cf->data[0], cf->can_dlc);
	memcpy_toio(&card->dpram[DPRAM_TX + DPRAM_TX_SIZE * fifo_wr],
			buf, DPRAM_TX_SIZE);
	if (++fifo_wr >= DPRAM_TX_CNT)
		fifo_wr = 0;
	iowrite8(fifo_wr, &card->dpram[DPRAM_TX_WR]);
	card->tx.last_bus = priv->index;
	++card->tx.pending;
	++priv->tx.pending;
	can_put_echo_skb(skb, dev, priv->tx.echo_put);
	++priv->tx.echo_put;
	if (priv->tx.echo_put >= TX_ECHO_SKB_MAX)
		priv->tx.echo_put = 0;
	/* can_put_echo_skb() saves the skb, safe to return TX_OK */
	ret = NETDEV_TX_OK;
xmit_done:
	spin_unlock(&card->spin);
	if (card->tx.pending >= TXMAX) {
		int j;
		for (j = 0; j < ARRAY_SIZE(card->net); ++j) {
			if (card->net[j])
				netif_stop_queue(card->net[j]);
		}
	}
	if (ret != NETDEV_TX_OK)
		netif_stop_queue(dev);

	return ret;
}