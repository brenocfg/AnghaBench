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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct txbd8 {int /*<<< orphan*/  length; int /*<<< orphan*/  bufPtr; int /*<<< orphan*/  lstatus; } ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {scalar_t__ data; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct gfar_private {int /*<<< orphan*/  ndev; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
struct gfar_priv_tx_q {int tx_ring_size; int qindex; int skb_dirtytx; struct txbd8* dirty_tx; scalar_t__ num_txbdfree; int /*<<< orphan*/  txlock; struct sk_buff** tx_skbuff; struct txbd8* tx_bd_base; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  shhwtstamps ;
struct TYPE_4__ {scalar_t__ bytes_sent; } ;
struct TYPE_3__ {int nr_frags; int tx_flags; } ;

/* Variables and functions */
 int BD_LENGTH_MASK ; 
 int BD_LFLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 TYPE_2__* GFAR_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  GFAR_DOWN ; 
 size_t GMAC_FCB_LEN ; 
 size_t GMAC_TXPAL_LEN ; 
 int SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  TXBD_READY ; 
 int TX_RING_MOD_MASK (int) ; 
 size_t be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfar_clear_txbd_status (struct txbd8*) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,int,unsigned int) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int) ; 
 struct txbd8* next_txbd (struct txbd8*,struct txbd8*,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,size_t) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 struct txbd8* skip_txbd (struct txbd8*,int,struct txbd8*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void gfar_clean_tx_ring(struct gfar_priv_tx_q *tx_queue)
{
	struct net_device *dev = tx_queue->dev;
	struct netdev_queue *txq;
	struct gfar_private *priv = netdev_priv(dev);
	struct txbd8 *bdp, *next = NULL;
	struct txbd8 *lbdp = NULL;
	struct txbd8 *base = tx_queue->tx_bd_base;
	struct sk_buff *skb;
	int skb_dirtytx;
	int tx_ring_size = tx_queue->tx_ring_size;
	int frags = 0, nr_txbds = 0;
	int i;
	int howmany = 0;
	int tqi = tx_queue->qindex;
	unsigned int bytes_sent = 0;
	u32 lstatus;
	size_t buflen;

	txq = netdev_get_tx_queue(dev, tqi);
	bdp = tx_queue->dirty_tx;
	skb_dirtytx = tx_queue->skb_dirtytx;

	while ((skb = tx_queue->tx_skbuff[skb_dirtytx])) {

		frags = skb_shinfo(skb)->nr_frags;

		/* When time stamping, one additional TxBD must be freed.
		 * Also, we need to dma_unmap_single() the TxPAL.
		 */
		if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS))
			nr_txbds = frags + 2;
		else
			nr_txbds = frags + 1;

		lbdp = skip_txbd(bdp, nr_txbds - 1, base, tx_ring_size);

		lstatus = be32_to_cpu(lbdp->lstatus);

		/* Only clean completed frames */
		if ((lstatus & BD_LFLAG(TXBD_READY)) &&
		    (lstatus & BD_LENGTH_MASK))
			break;

		if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS)) {
			next = next_txbd(bdp, base, tx_ring_size);
			buflen = be16_to_cpu(next->length) +
				 GMAC_FCB_LEN + GMAC_TXPAL_LEN;
		} else
			buflen = be16_to_cpu(bdp->length);

		dma_unmap_single(priv->dev, be32_to_cpu(bdp->bufPtr),
				 buflen, DMA_TO_DEVICE);

		if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_IN_PROGRESS)) {
			struct skb_shared_hwtstamps shhwtstamps;
			u64 *ns = (u64 *)(((uintptr_t)skb->data + 0x10) &
					  ~0x7UL);

			memset(&shhwtstamps, 0, sizeof(shhwtstamps));
			shhwtstamps.hwtstamp = ns_to_ktime(be64_to_cpu(*ns));
			skb_pull(skb, GMAC_FCB_LEN + GMAC_TXPAL_LEN);
			skb_tstamp_tx(skb, &shhwtstamps);
			gfar_clear_txbd_status(bdp);
			bdp = next;
		}

		gfar_clear_txbd_status(bdp);
		bdp = next_txbd(bdp, base, tx_ring_size);

		for (i = 0; i < frags; i++) {
			dma_unmap_page(priv->dev, be32_to_cpu(bdp->bufPtr),
				       be16_to_cpu(bdp->length),
				       DMA_TO_DEVICE);
			gfar_clear_txbd_status(bdp);
			bdp = next_txbd(bdp, base, tx_ring_size);
		}

		bytes_sent += GFAR_CB(skb)->bytes_sent;

		dev_kfree_skb_any(skb);

		tx_queue->tx_skbuff[skb_dirtytx] = NULL;

		skb_dirtytx = (skb_dirtytx + 1) &
			      TX_RING_MOD_MASK(tx_ring_size);

		howmany++;
		spin_lock(&tx_queue->txlock);
		tx_queue->num_txbdfree += nr_txbds;
		spin_unlock(&tx_queue->txlock);
	}

	/* If we freed a buffer, we can restart transmission, if necessary */
	if (tx_queue->num_txbdfree &&
	    netif_tx_queue_stopped(txq) &&
	    !(test_bit(GFAR_DOWN, &priv->state)))
		netif_wake_subqueue(priv->ndev, tqi);

	/* Update dirty indicators */
	tx_queue->skb_dirtytx = skb_dirtytx;
	tx_queue->dirty_tx = bdp;

	netdev_tx_completed_queue(txq, howmany, bytes_sent);
}