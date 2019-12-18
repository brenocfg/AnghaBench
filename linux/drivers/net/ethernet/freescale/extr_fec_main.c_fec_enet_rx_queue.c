#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
typedef  size_t u16 ;
struct vlan_hdr {int /*<<< orphan*/  h_vlan_TCI; } ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int features; TYPE_1__ stats; } ;
struct fec_enet_private {int quirks; int csum_flags; scalar_t__ bufdesc_ex; scalar_t__ rx_align; TYPE_2__* pdev; int /*<<< orphan*/  napi; scalar_t__ hwts_rx_en; scalar_t__ hwp; struct fec_enet_priv_rx_q** rx_queue; } ;
struct TYPE_7__ {struct bufdesc* cur; scalar_t__ reg_desc_active; } ;
struct fec_enet_priv_rx_q {TYPE_3__ bd; struct sk_buff** rx_skbuff; } ;
struct bufdesc_ex {int cbd_esc; scalar_t__ cbd_bdu; scalar_t__ cbd_prot; int /*<<< orphan*/  ts; } ;
struct bufdesc {int /*<<< orphan*/  cbd_sc; int /*<<< orphan*/  cbd_bufaddr; int /*<<< orphan*/  cbd_datlen; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short BD_ENET_RX_CL ; 
 unsigned short BD_ENET_RX_CR ; 
 unsigned short BD_ENET_RX_EMPTY ; 
 int /*<<< orphan*/  BD_ENET_RX_INT ; 
 unsigned short BD_ENET_RX_LAST ; 
 unsigned short BD_ENET_RX_LG ; 
 unsigned short BD_ENET_RX_NO ; 
 unsigned short BD_ENET_RX_OV ; 
 unsigned short BD_ENET_RX_SH ; 
 unsigned short BD_ENET_RX_STATS ; 
 int /*<<< orphan*/  BD_ENET_RX_VLAN ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ETH_ALEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 size_t FEC_ENET_GET_QUQUE (size_t) ; 
 int /*<<< orphan*/  FEC_ENET_RXF ; 
 scalar_t__ FEC_ENET_RX_FRSIZE ; 
 scalar_t__ FEC_IEVENT ; 
 int FEC_QUIRK_HAS_RACC ; 
 int FEC_QUIRK_SWAP_FRAME ; 
 int FLAG_RX_CSUM_ENABLED ; 
 int /*<<< orphan*/  FLAG_RX_CSUM_ERROR ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NET_IP_ALIGN ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cpu_to_fec16 (unsigned short) ; 
 int cpu_to_fec32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 void* fec16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec32_to_cpu (int /*<<< orphan*/ ) ; 
 int fec_enet_copybreak (struct net_device*,struct sk_buff**,struct bufdesc*,int,int) ; 
 int fec_enet_get_bd_index (struct bufdesc*,TYPE_3__*) ; 
 struct bufdesc* fec_enet_get_nextdesc (struct bufdesc*,TYPE_3__*) ; 
 int /*<<< orphan*/  fec_enet_hwtstamp (struct fec_enet_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec_enet_new_rxbdp (struct net_device*,struct bufdesc*,struct sk_buff*) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * skb_pull_inline (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  swap_buffer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
fec_enet_rx_queue(struct net_device *ndev, int budget, u16 queue_id)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	struct fec_enet_priv_rx_q *rxq;
	struct bufdesc *bdp;
	unsigned short status;
	struct  sk_buff *skb_new = NULL;
	struct  sk_buff *skb;
	ushort	pkt_len;
	__u8 *data;
	int	pkt_received = 0;
	struct	bufdesc_ex *ebdp = NULL;
	bool	vlan_packet_rcvd = false;
	u16	vlan_tag;
	int	index = 0;
	bool	is_copybreak;
	bool	need_swap = fep->quirks & FEC_QUIRK_SWAP_FRAME;

#ifdef CONFIG_M532x
	flush_cache_all();
#endif
	queue_id = FEC_ENET_GET_QUQUE(queue_id);
	rxq = fep->rx_queue[queue_id];

	/* First, grab all of the stats for the incoming packet.
	 * These get messed up if we get called due to a busy condition.
	 */
	bdp = rxq->bd.cur;

	while (!((status = fec16_to_cpu(bdp->cbd_sc)) & BD_ENET_RX_EMPTY)) {

		if (pkt_received >= budget)
			break;
		pkt_received++;

		writel(FEC_ENET_RXF, fep->hwp + FEC_IEVENT);

		/* Check for errors. */
		status ^= BD_ENET_RX_LAST;
		if (status & (BD_ENET_RX_LG | BD_ENET_RX_SH | BD_ENET_RX_NO |
			   BD_ENET_RX_CR | BD_ENET_RX_OV | BD_ENET_RX_LAST |
			   BD_ENET_RX_CL)) {
			ndev->stats.rx_errors++;
			if (status & BD_ENET_RX_OV) {
				/* FIFO overrun */
				ndev->stats.rx_fifo_errors++;
				goto rx_processing_done;
			}
			if (status & (BD_ENET_RX_LG | BD_ENET_RX_SH
						| BD_ENET_RX_LAST)) {
				/* Frame too long or too short. */
				ndev->stats.rx_length_errors++;
				if (status & BD_ENET_RX_LAST)
					netdev_err(ndev, "rcv is not +last\n");
			}
			if (status & BD_ENET_RX_CR)	/* CRC Error */
				ndev->stats.rx_crc_errors++;
			/* Report late collisions as a frame error. */
			if (status & (BD_ENET_RX_NO | BD_ENET_RX_CL))
				ndev->stats.rx_frame_errors++;
			goto rx_processing_done;
		}

		/* Process the incoming frame. */
		ndev->stats.rx_packets++;
		pkt_len = fec16_to_cpu(bdp->cbd_datlen);
		ndev->stats.rx_bytes += pkt_len;

		index = fec_enet_get_bd_index(bdp, &rxq->bd);
		skb = rxq->rx_skbuff[index];

		/* The packet length includes FCS, but we don't want to
		 * include that when passing upstream as it messes up
		 * bridging applications.
		 */
		is_copybreak = fec_enet_copybreak(ndev, &skb, bdp, pkt_len - 4,
						  need_swap);
		if (!is_copybreak) {
			skb_new = netdev_alloc_skb(ndev, FEC_ENET_RX_FRSIZE);
			if (unlikely(!skb_new)) {
				ndev->stats.rx_dropped++;
				goto rx_processing_done;
			}
			dma_unmap_single(&fep->pdev->dev,
					 fec32_to_cpu(bdp->cbd_bufaddr),
					 FEC_ENET_RX_FRSIZE - fep->rx_align,
					 DMA_FROM_DEVICE);
		}

		prefetch(skb->data - NET_IP_ALIGN);
		skb_put(skb, pkt_len - 4);
		data = skb->data;

		if (!is_copybreak && need_swap)
			swap_buffer(data, pkt_len);

#if !defined(CONFIG_M5272)
		if (fep->quirks & FEC_QUIRK_HAS_RACC)
			data = skb_pull_inline(skb, 2);
#endif

		/* Extract the enhanced buffer descriptor */
		ebdp = NULL;
		if (fep->bufdesc_ex)
			ebdp = (struct bufdesc_ex *)bdp;

		/* If this is a VLAN packet remove the VLAN Tag */
		vlan_packet_rcvd = false;
		if ((ndev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
		    fep->bufdesc_ex &&
		    (ebdp->cbd_esc & cpu_to_fec32(BD_ENET_RX_VLAN))) {
			/* Push and remove the vlan tag */
			struct vlan_hdr *vlan_header =
					(struct vlan_hdr *) (data + ETH_HLEN);
			vlan_tag = ntohs(vlan_header->h_vlan_TCI);

			vlan_packet_rcvd = true;

			memmove(skb->data + VLAN_HLEN, data, ETH_ALEN * 2);
			skb_pull(skb, VLAN_HLEN);
		}

		skb->protocol = eth_type_trans(skb, ndev);

		/* Get receive timestamp from the skb */
		if (fep->hwts_rx_en && fep->bufdesc_ex)
			fec_enet_hwtstamp(fep, fec32_to_cpu(ebdp->ts),
					  skb_hwtstamps(skb));

		if (fep->bufdesc_ex &&
		    (fep->csum_flags & FLAG_RX_CSUM_ENABLED)) {
			if (!(ebdp->cbd_esc & cpu_to_fec32(FLAG_RX_CSUM_ERROR))) {
				/* don't check it */
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			} else {
				skb_checksum_none_assert(skb);
			}
		}

		/* Handle received VLAN packets */
		if (vlan_packet_rcvd)
			__vlan_hwaccel_put_tag(skb,
					       htons(ETH_P_8021Q),
					       vlan_tag);

		napi_gro_receive(&fep->napi, skb);

		if (is_copybreak) {
			dma_sync_single_for_device(&fep->pdev->dev,
						   fec32_to_cpu(bdp->cbd_bufaddr),
						   FEC_ENET_RX_FRSIZE - fep->rx_align,
						   DMA_FROM_DEVICE);
		} else {
			rxq->rx_skbuff[index] = skb_new;
			fec_enet_new_rxbdp(ndev, bdp, skb_new);
		}

rx_processing_done:
		/* Clear the status flags for this buffer */
		status &= ~BD_ENET_RX_STATS;

		/* Mark the buffer empty */
		status |= BD_ENET_RX_EMPTY;

		if (fep->bufdesc_ex) {
			struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;

			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_RX_INT);
			ebdp->cbd_prot = 0;
			ebdp->cbd_bdu = 0;
		}
		/* Make sure the updates to rest of the descriptor are
		 * performed before transferring ownership.
		 */
		wmb();
		bdp->cbd_sc = cpu_to_fec16(status);

		/* Update BD pointer to next entry */
		bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);

		/* Doing this here will keep the FEC running while we process
		 * incoming frames.  On a heavily loaded network, we should be
		 * able to keep up at the expense of system resources.
		 */
		writel(0, rxq->bd.reg_desc_active);
	}
	rxq->bd.cur = bdp;
	return pkt_received;
}