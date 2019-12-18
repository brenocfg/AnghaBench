#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct tg3_rx_prodring_set {size_t rx_std_prod_idx; size_t rx_jmb_prod_idx; struct ring_info* rx_jmb_buffers; struct ring_info* rx_std_buffers; } ;
struct tg3_rx_buffer_desc {size_t opaque; int err_vlan; unsigned int idx_len; int type_flags; int ip_tcp_csum; } ;
struct tg3_napi {size_t rx_rcb_ptr; size_t* rx_rcb_prod_idx; int /*<<< orphan*/  napi; int /*<<< orphan*/  consmbox; struct tg3_rx_prodring_set prodring; struct tg3_rx_buffer_desc* rx_rcb; struct tg3* tp; } ;
struct tg3 {int rx_mode; size_t rx_std_max_post; size_t rx_std_ring_mask; size_t rx_ret_ring_mask; size_t rx_jmb_ring_mask; int rx_refill; struct tg3_napi* napi; TYPE_1__* dev; int /*<<< orphan*/  pdev; int /*<<< orphan*/  rx_dropped; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data; } ;
struct ring_info {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int features; unsigned int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ENABLE_RSS ; 
 unsigned int ETH_FCS_LEN ; 
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RXD_ERR_MASK ; 
 int RXD_FLAG_PTPSTAT_MASK ; 
 int RXD_FLAG_PTPSTAT_PTPV1 ; 
 int RXD_FLAG_PTPSTAT_PTPV2 ; 
 int RXD_FLAG_TCPUDP_CSUM ; 
 int RXD_FLAG_VLAN ; 
 unsigned int RXD_LEN_MASK ; 
 unsigned int RXD_LEN_SHIFT ; 
 size_t RXD_OPAQUE_INDEX_MASK ; 
 size_t RXD_OPAQUE_RING_JUMBO ; 
 size_t RXD_OPAQUE_RING_MASK ; 
 size_t RXD_OPAQUE_RING_STD ; 
 int RXD_TCPCSUM_MASK ; 
 int RXD_TCPCSUM_SHIFT ; 
 int RXD_VLAN_MASK ; 
 int RX_MODE_KEEP_VLAN_TAG ; 
 int TG3_RAW_IP_ALIGN ; 
 unsigned int TG3_RX_COPY_THRESH (struct tg3*) ; 
 int /*<<< orphan*/  TG3_RX_JMB_PROD_IDX_REG ; 
 int TG3_RX_OFFSET (struct tg3*) ; 
 int /*<<< orphan*/  TG3_RX_STD_PROD_IDX_REG ; 
 int /*<<< orphan*/  TG3_RX_TSTAMP_LSB ; 
 int /*<<< orphan*/  TG3_RX_TSTAMP_MSB ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int) ; 
 struct sk_buff* build_skb (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct ring_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_type_trans (struct sk_buff*,TYPE_1__*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct sk_buff* netdev_alloc_skb (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int tg3_alloc_rx_data (struct tg3*,struct tg3_rx_prodring_set*,size_t,size_t,unsigned int*) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_frag_free (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_hwclock_to_timestamp (struct tg3*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_recycle_rx (struct tg3_napi*,struct tg3_rx_prodring_set*,size_t,size_t,size_t) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_rx_mbox (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int tg3_rx(struct tg3_napi *tnapi, int budget)
{
	struct tg3 *tp = tnapi->tp;
	u32 work_mask, rx_std_posted = 0;
	u32 std_prod_idx, jmb_prod_idx;
	u32 sw_idx = tnapi->rx_rcb_ptr;
	u16 hw_idx;
	int received;
	struct tg3_rx_prodring_set *tpr = &tnapi->prodring;

	hw_idx = *(tnapi->rx_rcb_prod_idx);
	/*
	 * We need to order the read of hw_idx and the read of
	 * the opaque cookie.
	 */
	rmb();
	work_mask = 0;
	received = 0;
	std_prod_idx = tpr->rx_std_prod_idx;
	jmb_prod_idx = tpr->rx_jmb_prod_idx;
	while (sw_idx != hw_idx && budget > 0) {
		struct ring_info *ri;
		struct tg3_rx_buffer_desc *desc = &tnapi->rx_rcb[sw_idx];
		unsigned int len;
		struct sk_buff *skb;
		dma_addr_t dma_addr;
		u32 opaque_key, desc_idx, *post_ptr;
		u8 *data;
		u64 tstamp = 0;

		desc_idx = desc->opaque & RXD_OPAQUE_INDEX_MASK;
		opaque_key = desc->opaque & RXD_OPAQUE_RING_MASK;
		if (opaque_key == RXD_OPAQUE_RING_STD) {
			ri = &tp->napi[0].prodring.rx_std_buffers[desc_idx];
			dma_addr = dma_unmap_addr(ri, mapping);
			data = ri->data;
			post_ptr = &std_prod_idx;
			rx_std_posted++;
		} else if (opaque_key == RXD_OPAQUE_RING_JUMBO) {
			ri = &tp->napi[0].prodring.rx_jmb_buffers[desc_idx];
			dma_addr = dma_unmap_addr(ri, mapping);
			data = ri->data;
			post_ptr = &jmb_prod_idx;
		} else
			goto next_pkt_nopost;

		work_mask |= opaque_key;

		if (desc->err_vlan & RXD_ERR_MASK) {
		drop_it:
			tg3_recycle_rx(tnapi, tpr, opaque_key,
				       desc_idx, *post_ptr);
		drop_it_no_recycle:
			/* Other statistics kept track of by card. */
			tp->rx_dropped++;
			goto next_pkt;
		}

		prefetch(data + TG3_RX_OFFSET(tp));
		len = ((desc->idx_len & RXD_LEN_MASK) >> RXD_LEN_SHIFT) -
		      ETH_FCS_LEN;

		if ((desc->type_flags & RXD_FLAG_PTPSTAT_MASK) ==
		     RXD_FLAG_PTPSTAT_PTPV1 ||
		    (desc->type_flags & RXD_FLAG_PTPSTAT_MASK) ==
		     RXD_FLAG_PTPSTAT_PTPV2) {
			tstamp = tr32(TG3_RX_TSTAMP_LSB);
			tstamp |= (u64)tr32(TG3_RX_TSTAMP_MSB) << 32;
		}

		if (len > TG3_RX_COPY_THRESH(tp)) {
			int skb_size;
			unsigned int frag_size;

			skb_size = tg3_alloc_rx_data(tp, tpr, opaque_key,
						    *post_ptr, &frag_size);
			if (skb_size < 0)
				goto drop_it;

			pci_unmap_single(tp->pdev, dma_addr, skb_size,
					 PCI_DMA_FROMDEVICE);

			/* Ensure that the update to the data happens
			 * after the usage of the old DMA mapping.
			 */
			smp_wmb();

			ri->data = NULL;

			skb = build_skb(data, frag_size);
			if (!skb) {
				tg3_frag_free(frag_size != 0, data);
				goto drop_it_no_recycle;
			}
			skb_reserve(skb, TG3_RX_OFFSET(tp));
		} else {
			tg3_recycle_rx(tnapi, tpr, opaque_key,
				       desc_idx, *post_ptr);

			skb = netdev_alloc_skb(tp->dev,
					       len + TG3_RAW_IP_ALIGN);
			if (skb == NULL)
				goto drop_it_no_recycle;

			skb_reserve(skb, TG3_RAW_IP_ALIGN);
			pci_dma_sync_single_for_cpu(tp->pdev, dma_addr, len, PCI_DMA_FROMDEVICE);
			memcpy(skb->data,
			       data + TG3_RX_OFFSET(tp),
			       len);
			pci_dma_sync_single_for_device(tp->pdev, dma_addr, len, PCI_DMA_FROMDEVICE);
		}

		skb_put(skb, len);
		if (tstamp)
			tg3_hwclock_to_timestamp(tp, tstamp,
						 skb_hwtstamps(skb));

		if ((tp->dev->features & NETIF_F_RXCSUM) &&
		    (desc->type_flags & RXD_FLAG_TCPUDP_CSUM) &&
		    (((desc->ip_tcp_csum & RXD_TCPCSUM_MASK)
		      >> RXD_TCPCSUM_SHIFT) == 0xffff))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		else
			skb_checksum_none_assert(skb);

		skb->protocol = eth_type_trans(skb, tp->dev);

		if (len > (tp->dev->mtu + ETH_HLEN) &&
		    skb->protocol != htons(ETH_P_8021Q) &&
		    skb->protocol != htons(ETH_P_8021AD)) {
			dev_kfree_skb_any(skb);
			goto drop_it_no_recycle;
		}

		if (desc->type_flags & RXD_FLAG_VLAN &&
		    !(tp->rx_mode & RX_MODE_KEEP_VLAN_TAG))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       desc->err_vlan & RXD_VLAN_MASK);

		napi_gro_receive(&tnapi->napi, skb);

		received++;
		budget--;

next_pkt:
		(*post_ptr)++;

		if (unlikely(rx_std_posted >= tp->rx_std_max_post)) {
			tpr->rx_std_prod_idx = std_prod_idx &
					       tp->rx_std_ring_mask;
			tw32_rx_mbox(TG3_RX_STD_PROD_IDX_REG,
				     tpr->rx_std_prod_idx);
			work_mask &= ~RXD_OPAQUE_RING_STD;
			rx_std_posted = 0;
		}
next_pkt_nopost:
		sw_idx++;
		sw_idx &= tp->rx_ret_ring_mask;

		/* Refresh hw_idx to see if there is new work */
		if (sw_idx == hw_idx) {
			hw_idx = *(tnapi->rx_rcb_prod_idx);
			rmb();
		}
	}

	/* ACK the status ring. */
	tnapi->rx_rcb_ptr = sw_idx;
	tw32_rx_mbox(tnapi->consmbox, sw_idx);

	/* Refill RX ring(s). */
	if (!tg3_flag(tp, ENABLE_RSS)) {
		/* Sync BD data before updating mailbox */
		wmb();

		if (work_mask & RXD_OPAQUE_RING_STD) {
			tpr->rx_std_prod_idx = std_prod_idx &
					       tp->rx_std_ring_mask;
			tw32_rx_mbox(TG3_RX_STD_PROD_IDX_REG,
				     tpr->rx_std_prod_idx);
		}
		if (work_mask & RXD_OPAQUE_RING_JUMBO) {
			tpr->rx_jmb_prod_idx = jmb_prod_idx &
					       tp->rx_jmb_ring_mask;
			tw32_rx_mbox(TG3_RX_JMB_PROD_IDX_REG,
				     tpr->rx_jmb_prod_idx);
		}
	} else if (work_mask) {
		/* rx_std_buffers[] and rx_jmb_buffers[] entries must be
		 * updated before the producer indices can be updated.
		 */
		smp_wmb();

		tpr->rx_std_prod_idx = std_prod_idx & tp->rx_std_ring_mask;
		tpr->rx_jmb_prod_idx = jmb_prod_idx & tp->rx_jmb_ring_mask;

		if (tnapi != &tp->napi[1]) {
			tp->rx_refill = true;
			napi_schedule(&tp->napi[1].napi);
		}
	}

	return received;
}