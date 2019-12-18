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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; scalar_t__ data; int /*<<< orphan*/  protocol; } ;
struct rx_ring {int /*<<< orphan*/  napi; int /*<<< orphan*/  cq_id; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct ql_adapter {struct net_device* ndev; int /*<<< orphan*/  flags; int /*<<< orphan*/  pdev; } ;
struct net_device {scalar_t__ mtu; int features; } ;
struct iphdr {int frag_off; } ;
struct ib_mac_iocb_rsp {int flags2; int flags1; int flags3; } ;
struct TYPE_2__ {struct sk_buff* skb; } ;
struct bq_desc {TYPE_1__ p; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 scalar_t__ ETH_HLEN ; 
 int ETH_P_8021Q ; 
 int IB_MAC_CSUM_ERR_MASK ; 
 int IB_MAC_IOCB_RSP_ERR_MASK ; 
 int IB_MAC_IOCB_RSP_M_HASH ; 
 int IB_MAC_IOCB_RSP_M_MASK ; 
 int IB_MAC_IOCB_RSP_M_PROM ; 
 int IB_MAC_IOCB_RSP_M_REG ; 
 int IB_MAC_IOCB_RSP_P ; 
 int IB_MAC_IOCB_RSP_T ; 
 int IB_MAC_IOCB_RSP_U ; 
 int IB_MAC_IOCB_RSP_V4 ; 
 int IP_MF ; 
 int IP_OFFSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int NETIF_F_RXCSUM ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  QL_SELFTEST ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct bq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int htons (int) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (scalar_t__) ; 
 int /*<<< orphan*/  ql_categorize_rx_err (struct ql_adapter*,int,struct rx_ring*) ; 
 int /*<<< orphan*/  ql_check_lb_frame (struct ql_adapter*,struct sk_buff*) ; 
 struct bq_desc* ql_get_curr_sbuf (struct rx_ring*) ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_process_mac_rx_skb(struct ql_adapter *qdev,
					struct rx_ring *rx_ring,
					struct ib_mac_iocb_rsp *ib_mac_rsp,
					u32 length,
					u16 vlan_id)
{
	struct net_device *ndev = qdev->ndev;
	struct sk_buff *skb = NULL;
	struct sk_buff *new_skb = NULL;
	struct bq_desc *sbq_desc = ql_get_curr_sbuf(rx_ring);

	skb = sbq_desc->p.skb;
	/* Allocate new_skb and copy */
	new_skb = netdev_alloc_skb(qdev->ndev, length + NET_IP_ALIGN);
	if (new_skb == NULL) {
		rx_ring->rx_dropped++;
		return;
	}
	skb_reserve(new_skb, NET_IP_ALIGN);

	pci_dma_sync_single_for_cpu(qdev->pdev,
				    dma_unmap_addr(sbq_desc, mapaddr),
				    dma_unmap_len(sbq_desc, maplen),
				    PCI_DMA_FROMDEVICE);

	skb_put_data(new_skb, skb->data, length);

	pci_dma_sync_single_for_device(qdev->pdev,
				       dma_unmap_addr(sbq_desc, mapaddr),
				       dma_unmap_len(sbq_desc, maplen),
				       PCI_DMA_FROMDEVICE);
	skb = new_skb;

	/* Frame error, so drop the packet. */
	if (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_ERR_MASK) {
		ql_categorize_rx_err(qdev, ib_mac_rsp->flags2, rx_ring);
		dev_kfree_skb_any(skb);
		return;
	}

	/* loopback self test for ethtool */
	if (test_bit(QL_SELFTEST, &qdev->flags)) {
		ql_check_lb_frame(qdev, skb);
		dev_kfree_skb_any(skb);
		return;
	}

	/* The max framesize filter on this chip is set higher than
	 * MTU since FCoE uses 2k frames.
	 */
	if (skb->len > ndev->mtu + ETH_HLEN) {
		dev_kfree_skb_any(skb);
		rx_ring->rx_dropped++;
		return;
	}

	prefetch(skb->data);
	if (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) {
		netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "%s Multicast.\n",
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_HASH ? "Hash" :
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_REG ? "Registered" :
			     (ib_mac_rsp->flags1 & IB_MAC_IOCB_RSP_M_MASK) ==
			     IB_MAC_IOCB_RSP_M_PROM ? "Promiscuous" : "");
	}
	if (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_P)
		netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
			     "Promiscuous Packet.\n");

	rx_ring->rx_packets++;
	rx_ring->rx_bytes += skb->len;
	skb->protocol = eth_type_trans(skb, ndev);
	skb_checksum_none_assert(skb);

	/* If rx checksum is on, and there are no
	 * csum or frame errors.
	 */
	if ((ndev->features & NETIF_F_RXCSUM) &&
		!(ib_mac_rsp->flags1 & IB_MAC_CSUM_ERR_MASK)) {
		/* TCP frame. */
		if (ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_T) {
			netif_printk(qdev, rx_status, KERN_DEBUG, qdev->ndev,
				     "TCP checksum done!\n");
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		} else if ((ib_mac_rsp->flags2 & IB_MAC_IOCB_RSP_U) &&
				(ib_mac_rsp->flags3 & IB_MAC_IOCB_RSP_V4)) {
			/* Unfragmented ipv4 UDP frame. */
			struct iphdr *iph = (struct iphdr *) skb->data;
			if (!(iph->frag_off &
				htons(IP_MF|IP_OFFSET))) {
				skb->ip_summed = CHECKSUM_UNNECESSARY;
				netif_printk(qdev, rx_status, KERN_DEBUG,
					     qdev->ndev,
					     "UDP checksum done!\n");
			}
		}
	}

	skb_record_rx_queue(skb, rx_ring->cq_id);
	if (vlan_id != 0xffff)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_id);
	if (skb->ip_summed == CHECKSUM_UNNECESSARY)
		napi_gro_receive(&rx_ring->napi, skb);
	else
		netif_receive_skb(skb);
}