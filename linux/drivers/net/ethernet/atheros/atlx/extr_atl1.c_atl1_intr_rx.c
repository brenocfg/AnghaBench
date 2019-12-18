#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_7__ {int /*<<< orphan*/  pkt_size; } ;
struct TYPE_8__ {int valid; TYPE_2__ xsum_sz; } ;
struct rx_return_desc {int num_buf; int pkt_flg; int err_flg; int vlan_tag; size_t buf_indx; TYPE_3__ xsz; } ;
struct atl1_rrd_ring {scalar_t__ count; int /*<<< orphan*/  next_to_clean; } ;
struct atl1_rfd_ring {scalar_t__ next_to_clean; scalar_t__ count; int /*<<< orphan*/  next_to_use; struct atl1_buffer* buffer_info; } ;
struct atl1_buffer {scalar_t__ alloced; struct sk_buff* skb; scalar_t__ dma; int /*<<< orphan*/  length; } ;
struct TYPE_6__ {scalar_t__ hw_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  next_to_use; } ;
struct atl1_adapter {int /*<<< orphan*/  mb_lock; TYPE_1__ hw; struct atl1_rrd_ring rrd_ring; struct atl1_rfd_ring rfd_ring; TYPE_4__ tpd_ring; int /*<<< orphan*/  netdev; TYPE_5__* pdev; int /*<<< orphan*/  rx_buffer_len; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rx_return_desc* ATL1_RRD_DESC (struct atl1_rrd_ring*,scalar_t__) ; 
 int ERR_FLAG_IP_CHKSUM ; 
 int ERR_FLAG_L4_CHKSUM ; 
 int ERR_FLAG_LEN ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ MB_RFD_PROD_INDX_MASK ; 
 scalar_t__ MB_RFD_PROD_INDX_SHIFT ; 
 scalar_t__ MB_RRD_CONS_INDX_MASK ; 
 scalar_t__ MB_RRD_CONS_INDX_SHIFT ; 
 scalar_t__ MB_TPD_PROD_INDX_MASK ; 
 scalar_t__ MB_TPD_PROD_INDX_SHIFT ; 
 int PACKET_FLAG_ERR ; 
 int PACKET_FLAG_VLAN_INS ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ REG_MAILBOX ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atl1_alloc_rx_buffers (struct atl1_adapter*) ; 
 int /*<<< orphan*/  atl1_clean_alloc_flag (struct atl1_adapter*,struct rx_return_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atl1_rx_checksum (struct atl1_adapter*,struct rx_return_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  atl1_update_rfd_index (struct atl1_adapter*,struct rx_return_desc*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ netif_msg_rx_err (struct atl1_adapter*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_page (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atl1_intr_rx(struct atl1_adapter *adapter, int budget)
{
	int i, count;
	u16 length;
	u16 rrd_next_to_clean;
	u32 value;
	struct atl1_rfd_ring *rfd_ring = &adapter->rfd_ring;
	struct atl1_rrd_ring *rrd_ring = &adapter->rrd_ring;
	struct atl1_buffer *buffer_info;
	struct rx_return_desc *rrd;
	struct sk_buff *skb;

	count = 0;

	rrd_next_to_clean = atomic_read(&rrd_ring->next_to_clean);

	while (count < budget) {
		rrd = ATL1_RRD_DESC(rrd_ring, rrd_next_to_clean);
		i = 1;
		if (likely(rrd->xsz.valid)) {	/* packet valid */
chk_rrd:
			/* check rrd status */
			if (likely(rrd->num_buf == 1))
				goto rrd_ok;
			else if (netif_msg_rx_err(adapter)) {
				dev_printk(KERN_DEBUG, &adapter->pdev->dev,
					"unexpected RRD buffer count\n");
				dev_printk(KERN_DEBUG, &adapter->pdev->dev,
					"rx_buf_len = %d\n",
					adapter->rx_buffer_len);
				dev_printk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD num_buf = %d\n",
					rrd->num_buf);
				dev_printk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD pkt_len = %d\n",
					rrd->xsz.xsum_sz.pkt_size);
				dev_printk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD pkt_flg = 0x%08X\n",
					rrd->pkt_flg);
				dev_printk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD err_flg = 0x%08X\n",
					rrd->err_flg);
				dev_printk(KERN_DEBUG, &adapter->pdev->dev,
					"RRD vlan_tag = 0x%08X\n",
					rrd->vlan_tag);
			}

			/* rrd seems to be bad */
			if (unlikely(i-- > 0)) {
				/* rrd may not be DMAed completely */
				udelay(1);
				goto chk_rrd;
			}
			/* bad rrd */
			if (netif_msg_rx_err(adapter))
				dev_printk(KERN_DEBUG, &adapter->pdev->dev,
					"bad RRD\n");
			/* see if update RFD index */
			if (rrd->num_buf > 1)
				atl1_update_rfd_index(adapter, rrd);

			/* update rrd */
			rrd->xsz.valid = 0;
			if (++rrd_next_to_clean == rrd_ring->count)
				rrd_next_to_clean = 0;
			count++;
			continue;
		} else {	/* current rrd still not be updated */

			break;
		}
rrd_ok:
		/* clean alloc flag for bad rrd */
		atl1_clean_alloc_flag(adapter, rrd, 0);

		buffer_info = &rfd_ring->buffer_info[rrd->buf_indx];
		if (++rfd_ring->next_to_clean == rfd_ring->count)
			rfd_ring->next_to_clean = 0;

		/* update rrd next to clean */
		if (++rrd_next_to_clean == rrd_ring->count)
			rrd_next_to_clean = 0;
		count++;

		if (unlikely(rrd->pkt_flg & PACKET_FLAG_ERR)) {
			if (!(rrd->err_flg &
				(ERR_FLAG_IP_CHKSUM | ERR_FLAG_L4_CHKSUM
				| ERR_FLAG_LEN))) {
				/* packet error, don't need upstream */
				buffer_info->alloced = 0;
				rrd->xsz.valid = 0;
				continue;
			}
		}

		/* Good Receive */
		pci_unmap_page(adapter->pdev, buffer_info->dma,
			       buffer_info->length, PCI_DMA_FROMDEVICE);
		buffer_info->dma = 0;
		skb = buffer_info->skb;
		length = le16_to_cpu(rrd->xsz.xsum_sz.pkt_size);

		skb_put(skb, length - ETH_FCS_LEN);

		/* Receive Checksum Offload */
		atl1_rx_checksum(adapter, rrd, skb);
		skb->protocol = eth_type_trans(skb, adapter->netdev);

		if (rrd->pkt_flg & PACKET_FLAG_VLAN_INS) {
			u16 vlan_tag = (rrd->vlan_tag >> 4) |
					((rrd->vlan_tag & 7) << 13) |
					((rrd->vlan_tag & 8) << 9);

			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
		}
		netif_receive_skb(skb);

		/* let protocol layer free skb */
		buffer_info->skb = NULL;
		buffer_info->alloced = 0;
		rrd->xsz.valid = 0;
	}

	atomic_set(&rrd_ring->next_to_clean, rrd_next_to_clean);

	atl1_alloc_rx_buffers(adapter);

	/* update mailbox ? */
	if (count) {
		u32 tpd_next_to_use;
		u32 rfd_next_to_use;

		spin_lock(&adapter->mb_lock);

		tpd_next_to_use = atomic_read(&adapter->tpd_ring.next_to_use);
		rfd_next_to_use =
		    atomic_read(&adapter->rfd_ring.next_to_use);
		rrd_next_to_clean =
		    atomic_read(&adapter->rrd_ring.next_to_clean);
		value = ((rfd_next_to_use & MB_RFD_PROD_INDX_MASK) <<
			MB_RFD_PROD_INDX_SHIFT) |
                        ((rrd_next_to_clean & MB_RRD_CONS_INDX_MASK) <<
			MB_RRD_CONS_INDX_SHIFT) |
                        ((tpd_next_to_use & MB_TPD_PROD_INDX_MASK) <<
			MB_TPD_PROD_INDX_SHIFT);
		iowrite32(value, adapter->hw.hw_addr + REG_MAILBOX);
		spin_unlock(&adapter->mb_lock);
	}

	return count;
}