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
typedef  size_t u32 ;
struct txrx_desc_t {size_t control; } ;
struct sk_buff {size_t len; int /*<<< orphan*/  data; } ;
struct netdata_local {int num_used_tx_buffs; size_t* tx_stat_v; size_t* skblen; int /*<<< orphan*/  lock; int /*<<< orphan*/  net_base; scalar_t__ tx_buff_v; struct txrx_desc_t* tx_desc_v; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t ENET_MAXF_SIZE ; 
 int ENET_TX_DESC ; 
 int /*<<< orphan*/  LPC_ENET_TXPRODUCEINDEX (int /*<<< orphan*/ ) ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 size_t TXDESC_CONTROL_INT ; 
 size_t TXDESC_CONTROL_LAST ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 struct netdata_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 size_t readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc_eth_hard_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct netdata_local *pldat = netdev_priv(ndev);
	u32 len, txidx;
	u32 *ptxstat;
	struct txrx_desc_t *ptxrxdesc;

	len = skb->len;

	spin_lock_irq(&pldat->lock);

	if (pldat->num_used_tx_buffs >= (ENET_TX_DESC - 1)) {
		/* This function should never be called when there are no
		   buffers */
		netif_stop_queue(ndev);
		spin_unlock_irq(&pldat->lock);
		WARN(1, "BUG! TX request when no free TX buffers!\n");
		return NETDEV_TX_BUSY;
	}

	/* Get the next TX descriptor index */
	txidx = readl(LPC_ENET_TXPRODUCEINDEX(pldat->net_base));

	/* Setup control for the transfer */
	ptxstat = &pldat->tx_stat_v[txidx];
	*ptxstat = 0;
	ptxrxdesc = &pldat->tx_desc_v[txidx];
	ptxrxdesc->control =
		(len - 1) | TXDESC_CONTROL_LAST | TXDESC_CONTROL_INT;

	/* Copy data to the DMA buffer */
	memcpy(pldat->tx_buff_v + txidx * ENET_MAXF_SIZE, skb->data, len);

	/* Save the buffer and increment the buffer counter */
	pldat->skblen[txidx] = len;
	pldat->num_used_tx_buffs++;

	/* Start transmit */
	txidx++;
	if (txidx >= ENET_TX_DESC)
		txidx = 0;
	writel(txidx, LPC_ENET_TXPRODUCEINDEX(pldat->net_base));

	/* Stop queue if no more TX buffers */
	if (pldat->num_used_tx_buffs >= (ENET_TX_DESC - 1))
		netif_stop_queue(ndev);

	spin_unlock_irq(&pldat->lock);

	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}