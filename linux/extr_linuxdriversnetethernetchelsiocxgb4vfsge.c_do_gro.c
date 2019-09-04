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
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  ip_summed; scalar_t__ data_len; int /*<<< orphan*/  truesize; scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_cso; int /*<<< orphan*/  pkts; int /*<<< orphan*/  lro_merged; int /*<<< orphan*/  lro_pkts; int /*<<< orphan*/  vlan_ex; int /*<<< orphan*/  rx_drops; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; int /*<<< orphan*/  idx; struct adapter* adapter; } ;
struct sge_eth_rxq {TYPE_2__ stats; TYPE_1__ rspq; } ;
struct sge {scalar_t__ pktshift; } ;
struct port_info {int /*<<< orphan*/  vlan_id; } ;
struct pkt_gl {scalar_t__ tot_len; } ;
struct cpl_rx_pkt {int /*<<< orphan*/  vlan; scalar_t__ vlan_ex; } ;
struct adapter {struct sge sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int GRO_HELD ; 
 int GRO_MERGED ; 
 int GRO_MERGED_FREE ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_frags (struct sk_buff*,struct pkt_gl const*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* napi_get_frags (int /*<<< orphan*/ *) ; 
 int napi_gro_frags (int /*<<< orphan*/ *) ; 
 struct port_info* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4vf_pktgl_free (struct pkt_gl const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void do_gro(struct sge_eth_rxq *rxq, const struct pkt_gl *gl,
		   const struct cpl_rx_pkt *pkt)
{
	struct adapter *adapter = rxq->rspq.adapter;
	struct sge *s = &adapter->sge;
	struct port_info *pi;
	int ret;
	struct sk_buff *skb;

	skb = napi_get_frags(&rxq->rspq.napi);
	if (unlikely(!skb)) {
		t4vf_pktgl_free(gl);
		rxq->stats.rx_drops++;
		return;
	}

	copy_frags(skb, gl, s->pktshift);
	skb->len = gl->tot_len - s->pktshift;
	skb->data_len = skb->len;
	skb->truesize += skb->data_len;
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb_record_rx_queue(skb, rxq->rspq.idx);
	pi = netdev_priv(skb->dev);

	if (pkt->vlan_ex && !pi->vlan_id) {
		__vlan_hwaccel_put_tag(skb, cpu_to_be16(ETH_P_8021Q),
					be16_to_cpu(pkt->vlan));
		rxq->stats.vlan_ex++;
	}
	ret = napi_gro_frags(&rxq->rspq.napi);

	if (ret == GRO_HELD)
		rxq->stats.lro_pkts++;
	else if (ret == GRO_MERGED || ret == GRO_MERGED_FREE)
		rxq->stats.lro_merged++;
	rxq->stats.pkts++;
	rxq->stats.rx_cso++;
}