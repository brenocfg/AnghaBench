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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  queue_mapping; } ;
struct opa_vnic_adapter {TYPE_1__* rn_ops; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_start_xmit ) (struct sk_buff*,struct net_device*) ;} ;

/* Variables and functions */
 scalar_t__ ETH_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  opa_vnic_encap_skb (struct opa_vnic_adapter*,struct sk_buff*) ; 
 struct opa_vnic_adapter* opa_vnic_priv (struct net_device*) ; 
 scalar_t__ skb_padto (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct net_device*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  v_dbg (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t opa_netdev_start_xmit(struct sk_buff *skb,
					 struct net_device *netdev)
{
	struct opa_vnic_adapter *adapter = opa_vnic_priv(netdev);

	v_dbg("xmit: queue %d skb len %d\n", skb->queue_mapping, skb->len);
	/* pad to ensure mininum ethernet packet length */
	if (unlikely(skb->len < ETH_ZLEN)) {
		if (skb_padto(skb, ETH_ZLEN))
			return NETDEV_TX_OK;

		skb_put(skb, ETH_ZLEN - skb->len);
	}

	opa_vnic_encap_skb(adapter, skb);
	return adapter->rn_ops->ndo_start_xmit(skb, netdev);
}