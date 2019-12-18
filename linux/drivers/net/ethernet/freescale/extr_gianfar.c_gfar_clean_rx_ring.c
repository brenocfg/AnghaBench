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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ len; } ;
struct rxbd8 {int /*<<< orphan*/  lstatus; } ;
struct net_device {int dummy; } ;
struct gfar_private {int tx_actual_en; } ;
struct TYPE_4__ {unsigned int rx_packets; unsigned int rx_bytes; int /*<<< orphan*/  rx_dropped; } ;
struct gfar_priv_rx_q {int next_to_clean; int rx_ring_size; int /*<<< orphan*/  rfbptr; TYPE_2__ stats; struct sk_buff* skb; TYPE_1__* grp; int /*<<< orphan*/  qindex; struct rxbd8* rx_bd_base; struct net_device* ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi_rx; } ;

/* Variables and functions */
 int BD_LFLAG (int /*<<< orphan*/ ) ; 
 int GFAR_RX_BUFF_ALLOC ; 
 int /*<<< orphan*/  RXBD_EMPTY ; 
 int /*<<< orphan*/  RXBD_ERR ; 
 int /*<<< orphan*/  RXBD_LAST ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_errors (int,struct net_device*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  gfar_alloc_rx_buffs (struct gfar_priv_rx_q*,int) ; 
 struct sk_buff* gfar_get_next_rxbuff (struct gfar_priv_rx_q*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  gfar_process_frame (struct net_device*,struct sk_buff*) ; 
 int gfar_rxbd_dma_lastfree (struct gfar_priv_rx_q*) ; 
 int gfar_rxbd_unused (struct gfar_priv_rx_q*) ; 
 int /*<<< orphan*/  gfar_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int gfar_clean_rx_ring(struct gfar_priv_rx_q *rx_queue,
			      int rx_work_limit)
{
	struct net_device *ndev = rx_queue->ndev;
	struct gfar_private *priv = netdev_priv(ndev);
	struct rxbd8 *bdp;
	int i, howmany = 0;
	struct sk_buff *skb = rx_queue->skb;
	int cleaned_cnt = gfar_rxbd_unused(rx_queue);
	unsigned int total_bytes = 0, total_pkts = 0;

	/* Get the first full descriptor */
	i = rx_queue->next_to_clean;

	while (rx_work_limit--) {
		u32 lstatus;

		if (cleaned_cnt >= GFAR_RX_BUFF_ALLOC) {
			gfar_alloc_rx_buffs(rx_queue, cleaned_cnt);
			cleaned_cnt = 0;
		}

		bdp = &rx_queue->rx_bd_base[i];
		lstatus = be32_to_cpu(bdp->lstatus);
		if (lstatus & BD_LFLAG(RXBD_EMPTY))
			break;

		/* order rx buffer descriptor reads */
		rmb();

		/* fetch next to clean buffer from the ring */
		skb = gfar_get_next_rxbuff(rx_queue, lstatus, skb);
		if (unlikely(!skb))
			break;

		cleaned_cnt++;
		howmany++;

		if (unlikely(++i == rx_queue->rx_ring_size))
			i = 0;

		rx_queue->next_to_clean = i;

		/* fetch next buffer if not the last in frame */
		if (!(lstatus & BD_LFLAG(RXBD_LAST)))
			continue;

		if (unlikely(lstatus & BD_LFLAG(RXBD_ERR))) {
			count_errors(lstatus, ndev);

			/* discard faulty buffer */
			dev_kfree_skb(skb);
			skb = NULL;
			rx_queue->stats.rx_dropped++;
			continue;
		}

		gfar_process_frame(ndev, skb);

		/* Increment the number of packets */
		total_pkts++;
		total_bytes += skb->len;

		skb_record_rx_queue(skb, rx_queue->qindex);

		skb->protocol = eth_type_trans(skb, ndev);

		/* Send the packet up the stack */
		napi_gro_receive(&rx_queue->grp->napi_rx, skb);

		skb = NULL;
	}

	/* Store incomplete frames for completion */
	rx_queue->skb = skb;

	rx_queue->stats.rx_packets += total_pkts;
	rx_queue->stats.rx_bytes += total_bytes;

	if (cleaned_cnt)
		gfar_alloc_rx_buffs(rx_queue, cleaned_cnt);

	/* Update Last Free RxBD pointer for LFC */
	if (unlikely(priv->tx_actual_en)) {
		u32 bdp_dma = gfar_rxbd_dma_lastfree(rx_queue);

		gfar_write(rx_queue->rfbptr, bdp_dma);
	}

	return howmany;
}