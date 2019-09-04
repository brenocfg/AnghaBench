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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct pch_gbe_rx_ring {unsigned int next_to_clean; unsigned int count; struct pch_gbe_buffer* buffer_info; } ;
struct pch_gbe_rx_desc {scalar_t__ gbec_status; int tcp_ip_status; int rx_words_eob; int /*<<< orphan*/  dma_status; } ;
struct pch_gbe_buffer {int mapped; int /*<<< orphan*/  rx_buffer; int /*<<< orphan*/  length; int /*<<< orphan*/  dma; struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  napi; TYPE_1__ stats; struct pci_dev* pdev; struct net_device* netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ DSC_INIT16 ; 
 int ETH_FCS_LEN ; 
 int PCH_GBE_RXD_ACC_STAT_TCPIPOK ; 
 int PCH_GBE_RXD_GMAC_STAT_CRCERR ; 
 int PCH_GBE_RXD_GMAC_STAT_MARMLT ; 
 int PCH_GBE_RXD_GMAC_STAT_NBLERR ; 
 int PCH_GBE_RXD_GMAC_STAT_NOTOCTAL ; 
 unsigned int PCH_GBE_RX_BUFFER_WRITE ; 
 struct pch_gbe_rx_desc* PCH_GBE_RX_DESC (struct pch_gbe_rx_ring,unsigned int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,unsigned int,int,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  pch_gbe_alloc_rx_buffers (struct pch_gbe_adapter*,struct pch_gbe_rx_ring*,unsigned int) ; 
 int /*<<< orphan*/  pch_rx_timestamp (struct pch_gbe_adapter*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
pch_gbe_clean_rx(struct pch_gbe_adapter *adapter,
		 struct pch_gbe_rx_ring *rx_ring,
		 int *work_done, int work_to_do)
{
	struct net_device *netdev = adapter->netdev;
	struct pci_dev *pdev = adapter->pdev;
	struct pch_gbe_buffer *buffer_info;
	struct pch_gbe_rx_desc *rx_desc;
	u32 length;
	unsigned int i;
	unsigned int cleaned_count = 0;
	bool cleaned = false;
	struct sk_buff *skb;
	u8 dma_status;
	u16 gbec_status;
	u32 tcp_ip_status;

	i = rx_ring->next_to_clean;

	while (*work_done < work_to_do) {
		/* Check Rx descriptor status */
		rx_desc = PCH_GBE_RX_DESC(*rx_ring, i);
		if (rx_desc->gbec_status == DSC_INIT16)
			break;
		cleaned = true;
		cleaned_count++;

		dma_status = rx_desc->dma_status;
		gbec_status = rx_desc->gbec_status;
		tcp_ip_status = rx_desc->tcp_ip_status;
		rx_desc->gbec_status = DSC_INIT16;
		buffer_info = &rx_ring->buffer_info[i];
		skb = buffer_info->skb;
		buffer_info->skb = NULL;

		/* unmap dma */
		dma_unmap_single(&pdev->dev, buffer_info->dma,
				   buffer_info->length, DMA_FROM_DEVICE);
		buffer_info->mapped = false;

		netdev_dbg(netdev,
			   "RxDecNo = 0x%04x  Status[DMA:0x%02x GBE:0x%04x TCP:0x%08x]  BufInf = 0x%p\n",
			   i, dma_status, gbec_status, tcp_ip_status,
			   buffer_info);
		/* Error check */
		if (unlikely(gbec_status & PCH_GBE_RXD_GMAC_STAT_NOTOCTAL)) {
			adapter->stats.rx_frame_errors++;
			netdev_err(netdev, "Receive Not Octal Error\n");
		} else if (unlikely(gbec_status &
				PCH_GBE_RXD_GMAC_STAT_NBLERR)) {
			adapter->stats.rx_frame_errors++;
			netdev_err(netdev, "Receive Nibble Error\n");
		} else if (unlikely(gbec_status &
				PCH_GBE_RXD_GMAC_STAT_CRCERR)) {
			adapter->stats.rx_crc_errors++;
			netdev_err(netdev, "Receive CRC Error\n");
		} else {
			/* get receive length */
			/* length convert[-3], length includes FCS length */
			length = (rx_desc->rx_words_eob) - 3 - ETH_FCS_LEN;
			if (rx_desc->rx_words_eob & 0x02)
				length = length - 4;
			/*
			 * buffer_info->rx_buffer: [Header:14][payload]
			 * skb->data: [Reserve:2][Header:14][payload]
			 */
			memcpy(skb->data, buffer_info->rx_buffer, length);

			/* update status of driver */
			adapter->stats.rx_bytes += length;
			adapter->stats.rx_packets++;
			if ((gbec_status & PCH_GBE_RXD_GMAC_STAT_MARMLT))
				adapter->stats.multicast++;
			/* Write meta date of skb */
			skb_put(skb, length);

			pch_rx_timestamp(adapter, skb);

			skb->protocol = eth_type_trans(skb, netdev);
			if (tcp_ip_status & PCH_GBE_RXD_ACC_STAT_TCPIPOK)
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			else
				skb->ip_summed = CHECKSUM_NONE;

			napi_gro_receive(&adapter->napi, skb);
			(*work_done)++;
			netdev_dbg(netdev,
				   "Receive skb->ip_summed: %d length: %d\n",
				   skb->ip_summed, length);
		}
		/* return some buffers to hardware, one at a time is too slow */
		if (unlikely(cleaned_count >= PCH_GBE_RX_BUFFER_WRITE)) {
			pch_gbe_alloc_rx_buffers(adapter, rx_ring,
						 cleaned_count);
			cleaned_count = 0;
		}
		if (++i == rx_ring->count)
			i = 0;
	}
	rx_ring->next_to_clean = i;
	if (cleaned_count)
		pch_gbe_alloc_rx_buffers(adapter, rx_ring, cleaned_count);
	return cleaned;
}