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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct vnic_rq_buf {struct sk_buff* os_buf; int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; } ;
struct vnic_rq {size_t index; int /*<<< orphan*/  vdev; } ;
struct vnic_cq {int /*<<< orphan*/  pkt_size_counter; } ;
struct sk_buff {int csum_level; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct net_device {int features; } ;
struct TYPE_4__ {scalar_t__ use_adaptive_rx_coalesce; } ;
struct TYPE_3__ {int patch_level; scalar_t__ vxlan_udp_port_number; } ;
struct enic {int /*<<< orphan*/  pdev; TYPE_2__ rx_coalesce_setting; int /*<<< orphan*/ * napi; TYPE_1__ vxlan; int /*<<< orphan*/  rq_truncated_pkts; int /*<<< orphan*/  rq_bad_fcs; struct vnic_cq* cq; struct net_device* netdev; } ;
struct cq_enet_rq_desc {int dummy; } ;
struct cq_desc {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
#define  CQ_ENET_RQ_DESC_RSS_TYPE_IPv4 133 
#define  CQ_ENET_RQ_DESC_RSS_TYPE_IPv6 132 
#define  CQ_ENET_RQ_DESC_RSS_TYPE_IPv6_EX 131 
#define  CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv4 130 
#define  CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv6 129 
#define  CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv6_EX 128 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int NETIF_F_GRO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L4 ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cq_enet_rq_desc_dec (struct cq_enet_rq_desc*,int*,int*,scalar_t__*,scalar_t__*,int*,int*,int*,int*,int*,int*,int*,scalar_t__*,int*,int*,scalar_t__*,scalar_t__*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 size_t enic_cq_rq (struct enic*,size_t) ; 
 int /*<<< orphan*/  enic_intr_update_pkt_size (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  enic_rxcopybreak (struct net_device*,struct sk_buff**,struct vnic_rq_buf*,scalar_t__) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (scalar_t__) ; 
 int /*<<< orphan*/  skb_mark_napi_id (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 struct enic* vnic_dev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enic_rq_indicate_buf(struct vnic_rq *rq,
	struct cq_desc *cq_desc, struct vnic_rq_buf *buf,
	int skipped, void *opaque)
{
	struct enic *enic = vnic_dev_priv(rq->vdev);
	struct net_device *netdev = enic->netdev;
	struct sk_buff *skb;
	struct vnic_cq *cq = &enic->cq[enic_cq_rq(enic, rq->index)];

	u8 type, color, eop, sop, ingress_port, vlan_stripped;
	u8 fcoe, fcoe_sof, fcoe_fc_crc_ok, fcoe_enc_error, fcoe_eof;
	u8 tcp_udp_csum_ok, udp, tcp, ipv4_csum_ok;
	u8 ipv6, ipv4, ipv4_fragment, fcs_ok, rss_type, csum_not_calc;
	u8 packet_error;
	u16 q_number, completed_index, bytes_written, vlan_tci, checksum;
	u32 rss_hash;
	bool outer_csum_ok = true, encap = false;

	if (skipped)
		return;

	skb = buf->os_buf;

	cq_enet_rq_desc_dec((struct cq_enet_rq_desc *)cq_desc,
		&type, &color, &q_number, &completed_index,
		&ingress_port, &fcoe, &eop, &sop, &rss_type,
		&csum_not_calc, &rss_hash, &bytes_written,
		&packet_error, &vlan_stripped, &vlan_tci, &checksum,
		&fcoe_sof, &fcoe_fc_crc_ok, &fcoe_enc_error,
		&fcoe_eof, &tcp_udp_csum_ok, &udp, &tcp,
		&ipv4_csum_ok, &ipv6, &ipv4, &ipv4_fragment,
		&fcs_ok);

	if (packet_error) {

		if (!fcs_ok) {
			if (bytes_written > 0)
				enic->rq_bad_fcs++;
			else if (bytes_written == 0)
				enic->rq_truncated_pkts++;
		}

		pci_unmap_single(enic->pdev, buf->dma_addr, buf->len,
				 PCI_DMA_FROMDEVICE);
		dev_kfree_skb_any(skb);
		buf->os_buf = NULL;

		return;
	}

	if (eop && bytes_written > 0) {

		/* Good receive
		 */

		if (!enic_rxcopybreak(netdev, &skb, buf, bytes_written)) {
			buf->os_buf = NULL;
			pci_unmap_single(enic->pdev, buf->dma_addr, buf->len,
					 PCI_DMA_FROMDEVICE);
		}
		prefetch(skb->data - NET_IP_ALIGN);

		skb_put(skb, bytes_written);
		skb->protocol = eth_type_trans(skb, netdev);
		skb_record_rx_queue(skb, q_number);
		if ((netdev->features & NETIF_F_RXHASH) && rss_hash &&
		    (type == 3)) {
			switch (rss_type) {
			case CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv4:
			case CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv6:
			case CQ_ENET_RQ_DESC_RSS_TYPE_TCP_IPv6_EX:
				skb_set_hash(skb, rss_hash, PKT_HASH_TYPE_L4);
				break;
			case CQ_ENET_RQ_DESC_RSS_TYPE_IPv4:
			case CQ_ENET_RQ_DESC_RSS_TYPE_IPv6:
			case CQ_ENET_RQ_DESC_RSS_TYPE_IPv6_EX:
				skb_set_hash(skb, rss_hash, PKT_HASH_TYPE_L3);
				break;
			}
		}
		if (enic->vxlan.vxlan_udp_port_number) {
			switch (enic->vxlan.patch_level) {
			case 0:
				if (fcoe) {
					encap = true;
					outer_csum_ok = fcoe_fc_crc_ok;
				}
				break;
			case 2:
				if ((type == 7) &&
				    (rss_hash & BIT(0))) {
					encap = true;
					outer_csum_ok = (rss_hash & BIT(1)) &&
							(rss_hash & BIT(2));
				}
				break;
			}
		}

		/* Hardware does not provide whole packet checksum. It only
		 * provides pseudo checksum. Since hw validates the packet
		 * checksum but not provide us the checksum value. use
		 * CHECSUM_UNNECESSARY.
		 *
		 * In case of encap pkt tcp_udp_csum_ok/tcp_udp_csum_ok is
		 * inner csum_ok. outer_csum_ok is set by hw when outer udp
		 * csum is correct or is zero.
		 */
		if ((netdev->features & NETIF_F_RXCSUM) && !csum_not_calc &&
		    tcp_udp_csum_ok && outer_csum_ok &&
		    (ipv4_csum_ok || ipv6)) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			skb->csum_level = encap;
		}

		if (vlan_stripped)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tci);

		skb_mark_napi_id(skb, &enic->napi[rq->index]);
		if (!(netdev->features & NETIF_F_GRO))
			netif_receive_skb(skb);
		else
			napi_gro_receive(&enic->napi[q_number], skb);
		if (enic->rx_coalesce_setting.use_adaptive_rx_coalesce)
			enic_intr_update_pkt_size(&cq->pkt_size_counter,
						  bytes_written);
	} else {

		/* Buffer overflow
		 */

		pci_unmap_single(enic->pdev, buf->dma_addr, buf->len,
				 PCI_DMA_FROMDEVICE);
		dev_kfree_skb_any(skb);
		buf->os_buf = NULL;
	}
}