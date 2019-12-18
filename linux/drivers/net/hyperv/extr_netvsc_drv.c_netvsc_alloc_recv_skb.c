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
typedef  int u16 ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_3__ {int cnt; int /*<<< orphan*/ * len; int /*<<< orphan*/ * data; int /*<<< orphan*/  pktlen; struct ndis_tcp_ip_checksum_info* csum_info; struct ndis_pkt_8021q_info* vlan; } ;
struct napi_struct {int dummy; } ;
struct netvsc_channel {TYPE_1__ rsc; struct napi_struct napi; } ;
struct net_device {int features; } ;
struct TYPE_4__ {scalar_t__ udp_checksum_succeeded; scalar_t__ tcp_checksum_succeeded; scalar_t__ ip_checksum_succeeded; scalar_t__ ip_checksum_value_invalid; } ;
struct ndis_tcp_ip_checksum_info {TYPE_2__ receive; } ;
struct ndis_pkt_8021q_info {int vlanid; int pri; scalar_t__ cfi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int NETIF_F_RXCSUM ; 
 int VLAN_CFI_MASK ; 
 int VLAN_PRIO_SHIFT ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int) ; 
 scalar_t__ eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct sk_buff* napi_alloc_skb (struct napi_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netvsc_comp_ipcsum (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *netvsc_alloc_recv_skb(struct net_device *net,
					     struct netvsc_channel *nvchan)
{
	struct napi_struct *napi = &nvchan->napi;
	const struct ndis_pkt_8021q_info *vlan = nvchan->rsc.vlan;
	const struct ndis_tcp_ip_checksum_info *csum_info =
						nvchan->rsc.csum_info;
	struct sk_buff *skb;
	int i;

	skb = napi_alloc_skb(napi, nvchan->rsc.pktlen);
	if (!skb)
		return skb;

	/*
	 * Copy to skb. This copy is needed here since the memory pointed by
	 * hv_netvsc_packet cannot be deallocated
	 */
	for (i = 0; i < nvchan->rsc.cnt; i++)
		skb_put_data(skb, nvchan->rsc.data[i], nvchan->rsc.len[i]);

	skb->protocol = eth_type_trans(skb, net);

	/* skb is already created with CHECKSUM_NONE */
	skb_checksum_none_assert(skb);

	/* Incoming packets may have IP header checksum verified by the host.
	 * They may not have IP header checksum computed after coalescing.
	 * We compute it here if the flags are set, because on Linux, the IP
	 * checksum is always checked.
	 */
	if (csum_info && csum_info->receive.ip_checksum_value_invalid &&
	    csum_info->receive.ip_checksum_succeeded &&
	    skb->protocol == htons(ETH_P_IP))
		netvsc_comp_ipcsum(skb);

	/* Do L4 checksum offload if enabled and present.
	 */
	if (csum_info && (net->features & NETIF_F_RXCSUM)) {
		if (csum_info->receive.tcp_checksum_succeeded ||
		    csum_info->receive.udp_checksum_succeeded)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	}

	if (vlan) {
		u16 vlan_tci = vlan->vlanid | (vlan->pri << VLAN_PRIO_SHIFT) |
			(vlan->cfi ? VLAN_CFI_MASK : 0);

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       vlan_tci);
	}

	return skb;
}