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
struct sk_buff {int /*<<< orphan*/  ip_summed; TYPE_3__* dev; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct sge_rspq {scalar_t__ polling; } ;
struct sge_qset {int /*<<< orphan*/  napi; int /*<<< orphan*/ * port_stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct port_info {size_t first_qset; TYPE_2__ iscsic; } ;
struct cpl_rx_pkt {size_t iff; scalar_t__ csum; int /*<<< orphan*/  vlan; scalar_t__ vlan_valid; int /*<<< orphan*/  fragment; scalar_t__ csum_valid; } ;
struct TYPE_4__ {struct sge_qset* qs; } ;
struct adapter {TYPE_1__ sge; int /*<<< orphan*/ * port; } ;
struct TYPE_6__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int ETH_P_8021Q ; 
 int NETIF_F_RXCSUM ; 
 size_t SGE_PSTAT_RX_CSUM_GOOD ; 
 size_t SGE_PSTAT_VLANEX ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb3_process_iscsi_prov_pack (struct port_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct port_info* netdev_priv (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 struct sge_qset* rspq_to_qset (struct sge_rspq*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_eth(struct adapter *adap, struct sge_rspq *rq,
		   struct sk_buff *skb, int pad, int lro)
{
	struct cpl_rx_pkt *p = (struct cpl_rx_pkt *)(skb->data + pad);
	struct sge_qset *qs = rspq_to_qset(rq);
	struct port_info *pi;

	skb_pull(skb, sizeof(*p) + pad);
	skb->protocol = eth_type_trans(skb, adap->port[p->iff]);
	pi = netdev_priv(skb->dev);
	if ((skb->dev->features & NETIF_F_RXCSUM) && p->csum_valid &&
	    p->csum == htons(0xffff) && !p->fragment) {
		qs->port_stats[SGE_PSTAT_RX_CSUM_GOOD]++;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	} else
		skb_checksum_none_assert(skb);
	skb_record_rx_queue(skb, qs - &adap->sge.qs[pi->first_qset]);

	if (p->vlan_valid) {
		qs->port_stats[SGE_PSTAT_VLANEX]++;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(p->vlan));
	}
	if (rq->polling) {
		if (lro)
			napi_gro_receive(&qs->napi, skb);
		else {
			if (unlikely(pi->iscsic.flags))
				cxgb3_process_iscsi_prov_pack(pi, skb);
			netif_receive_skb(skb);
		}
	} else
		netif_rx(skb);
}