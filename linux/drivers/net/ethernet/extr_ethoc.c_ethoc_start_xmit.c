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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {int /*<<< orphan*/  dev; TYPE_1__ stats; } ;
struct ethoc_bd {int stat; } ;
struct ethoc {unsigned int cur_tx; unsigned int num_tx; unsigned int dty_tx; int /*<<< orphan*/  lock; void** vma; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ ETHOC_BUFSIZ ; 
 scalar_t__ ETHOC_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int TX_BD_LEN (scalar_t__) ; 
 int TX_BD_LEN_MASK ; 
 int TX_BD_PAD ; 
 int TX_BD_READY ; 
 int TX_BD_STATS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ethoc_read_bd (struct ethoc*,unsigned int,struct ethoc_bd*) ; 
 int /*<<< orphan*/  ethoc_write_bd (struct ethoc*,unsigned int,struct ethoc_bd*) ; 
 int /*<<< orphan*/  memcpy_toio (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ skb_put_padto (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t ethoc_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);
	struct ethoc_bd bd;
	unsigned int entry;
	void *dest;

	if (skb_put_padto(skb, ETHOC_ZLEN)) {
		dev->stats.tx_errors++;
		goto out_no_free;
	}

	if (unlikely(skb->len > ETHOC_BUFSIZ)) {
		dev->stats.tx_errors++;
		goto out;
	}

	entry = priv->cur_tx % priv->num_tx;
	spin_lock_irq(&priv->lock);
	priv->cur_tx++;

	ethoc_read_bd(priv, entry, &bd);
	if (unlikely(skb->len < ETHOC_ZLEN))
		bd.stat |=  TX_BD_PAD;
	else
		bd.stat &= ~TX_BD_PAD;

	dest = priv->vma[entry];
	memcpy_toio(dest, skb->data, skb->len);

	bd.stat &= ~(TX_BD_STATS | TX_BD_LEN_MASK);
	bd.stat |= TX_BD_LEN(skb->len);
	ethoc_write_bd(priv, entry, &bd);

	bd.stat |= TX_BD_READY;
	ethoc_write_bd(priv, entry, &bd);

	if (priv->cur_tx == (priv->dty_tx + priv->num_tx)) {
		dev_dbg(&dev->dev, "stopping queue\n");
		netif_stop_queue(dev);
	}

	spin_unlock_irq(&priv->lock);
	skb_tx_timestamp(skb);
out:
	dev_kfree_skb(skb);
out_no_free:
	return NETDEV_TX_OK;
}