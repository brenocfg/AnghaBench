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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ cb; struct net_device* dev; scalar_t__ len; scalar_t__ data; } ;
struct rx_desc {int OWN; int EOR; int /*<<< orphan*/  Length; int /*<<< orphan*/  BufferAddress; } ;
struct rtllib_rx_stats {scalar_t__ bCRC; scalar_t__ RxBufShift; scalar_t__ RxDrvInfoSize; int /*<<< orphan*/  nic_type; int /*<<< orphan*/  freq; int /*<<< orphan*/  rate; int /*<<< orphan*/  noise; int /*<<< orphan*/  signal; } ;
struct rtllib_hdr_1addr {int /*<<< orphan*/  frame_ctl; int /*<<< orphan*/  addr1; } ;
struct TYPE_5__ {int /*<<< orphan*/  rxbytesunicast; int /*<<< orphan*/  rxok; int /*<<< orphan*/  rxmgmtcrcerr; int /*<<< orphan*/  rxdatacrcerr; } ;
struct r8192_priv {unsigned int rxringcount; size_t* rx_idx; int /*<<< orphan*/  rxbuffersize; int /*<<< orphan*/  pdev; struct sk_buff*** rx_buf; TYPE_2__ stats; TYPE_3__* rtllib; TYPE_1__* ops; struct rx_desc** rx_ring; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* LedControlHandler ) (struct net_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* rx_query_status_descriptor ) (struct net_device*,struct rtllib_rx_stats*,struct rx_desc*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_RX ; 
 int /*<<< orphan*/  NIC_8192E ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RTLLIB_24GHZ_BAND ; 
 scalar_t__ RTLLIB_FTYPE_MGMT ; 
 int RX_MPDU_QUEUE ; 
 scalar_t__ WLAN_FC_GET_TYPE (scalar_t__) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtllib_rx (TYPE_3__*,struct sk_buff*,struct rtllib_rx_stats*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_tail_pointer_rsl (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct rtllib_rx_stats*,struct rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void _rtl92e_rx_normal(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rtllib_hdr_1addr *rtllib_hdr = NULL;
	bool unicast_packet = false;
	bool bLedBlinking = true;
	u16 fc = 0, type = 0;
	u32 skb_len = 0;
	int rx_queue_idx = RX_MPDU_QUEUE;

	struct rtllib_rx_stats stats = {
		.signal = 0,
		.noise = (u8)-98,
		.rate = 0,
		.freq = RTLLIB_24GHZ_BAND,
	};
	unsigned int count = priv->rxringcount;

	stats.nic_type = NIC_8192E;

	while (count--) {
		struct rx_desc *pdesc = &priv->rx_ring[rx_queue_idx]
					[priv->rx_idx[rx_queue_idx]];
		struct sk_buff *skb = priv->rx_buf[rx_queue_idx]
				      [priv->rx_idx[rx_queue_idx]];
		struct sk_buff *new_skb;

		if (pdesc->OWN)
			return;
		if (!priv->ops->rx_query_status_descriptor(dev, &stats,
		pdesc, skb))
			goto done;
		new_skb = dev_alloc_skb(priv->rxbuffersize);
		/* if allocation of new skb failed - drop current packet
		 * and reuse skb
		 */
		if (unlikely(!new_skb))
			goto done;

		pci_unmap_single(priv->pdev,
				*((dma_addr_t *)skb->cb),
				priv->rxbuffersize,
				PCI_DMA_FROMDEVICE);

		skb_put(skb, pdesc->Length);
		skb_reserve(skb, stats.RxDrvInfoSize +
			stats.RxBufShift);
		skb_trim(skb, skb->len - 4/*sCrcLng*/);
		rtllib_hdr = (struct rtllib_hdr_1addr *)skb->data;
		if (!is_multicast_ether_addr(rtllib_hdr->addr1)) {
			/* unicast packet */
			unicast_packet = true;
		}
		fc = le16_to_cpu(rtllib_hdr->frame_ctl);
		type = WLAN_FC_GET_TYPE(fc);
		if (type == RTLLIB_FTYPE_MGMT)
			bLedBlinking = false;

		if (bLedBlinking)
			if (priv->rtllib->LedControlHandler)
				priv->rtllib->LedControlHandler(dev,
							LED_CTL_RX);

		if (stats.bCRC) {
			if (type != RTLLIB_FTYPE_MGMT)
				priv->stats.rxdatacrcerr++;
			else
				priv->stats.rxmgmtcrcerr++;
		}

		skb_len = skb->len;

		if (!rtllib_rx(priv->rtllib, skb, &stats)) {
			dev_kfree_skb_any(skb);
		} else {
			priv->stats.rxok++;
			if (unicast_packet)
				priv->stats.rxbytesunicast += skb_len;
		}

		skb = new_skb;
		skb->dev = dev;

		priv->rx_buf[rx_queue_idx][priv->rx_idx[rx_queue_idx]] =
								 skb;
		*((dma_addr_t *)skb->cb) = pci_map_single(priv->pdev,
					    skb_tail_pointer_rsl(skb),
					    priv->rxbuffersize,
					    PCI_DMA_FROMDEVICE);
		if (pci_dma_mapping_error(priv->pdev,
					  *((dma_addr_t *)skb->cb))) {
			dev_kfree_skb_any(skb);
			return;
		}
done:
		pdesc->BufferAddress = *((dma_addr_t *)skb->cb);
		pdesc->OWN = 1;
		pdesc->Length = priv->rxbuffersize;
		if (priv->rx_idx[rx_queue_idx] == priv->rxringcount - 1)
			pdesc->EOR = 1;
		priv->rx_idx[rx_queue_idx] = (priv->rx_idx[rx_queue_idx] + 1) %
					      priv->rxringcount;
	}

}