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
struct sk_buff {scalar_t__* data; scalar_t__ protocol; int /*<<< orphan*/  ip_summed; } ;
struct sge_port_stats {int /*<<< orphan*/  vlan_xtract; int /*<<< orphan*/  rx_cso_good; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_drops; } ;
struct sge {int /*<<< orphan*/ * port_stats; TYPE_1__ stats; scalar_t__ rx_pkt_pad; struct adapter* adapter; } ;
struct net_device {int features; } ;
struct freelQ {int dummy; } ;
struct cpl_rx_pkt {size_t iff; int csum; int /*<<< orphan*/  vlan; scalar_t__ vlan_valid; } ;
struct TYPE_5__ {size_t nports; } ;
struct adapter {TYPE_3__* port; TYPE_2__ params; } ;
struct TYPE_6__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* get_packet (struct adapter*,struct freelQ*,scalar_t__) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 struct sge_port_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void sge_rx(struct sge *sge, struct freelQ *fl, unsigned int len)
{
	struct sk_buff *skb;
	const struct cpl_rx_pkt *p;
	struct adapter *adapter = sge->adapter;
	struct sge_port_stats *st;
	struct net_device *dev;

	skb = get_packet(adapter, fl, len - sge->rx_pkt_pad);
	if (unlikely(!skb)) {
		sge->stats.rx_drops++;
		return;
	}

	p = (const struct cpl_rx_pkt *) skb->data;
	if (p->iff >= adapter->params.nports) {
		kfree_skb(skb);
		return;
	}
	__skb_pull(skb, sizeof(*p));

	st = this_cpu_ptr(sge->port_stats[p->iff]);
	dev = adapter->port[p->iff].dev;

	skb->protocol = eth_type_trans(skb, dev);
	if ((dev->features & NETIF_F_RXCSUM) && p->csum == 0xffff &&
	    skb->protocol == htons(ETH_P_IP) &&
	    (skb->data[9] == IPPROTO_TCP || skb->data[9] == IPPROTO_UDP)) {
		++st->rx_cso_good;
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	} else
		skb_checksum_none_assert(skb);

	if (p->vlan_valid) {
		st->vlan_xtract++;
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(p->vlan));
	}
	netif_receive_skb(skb);
}