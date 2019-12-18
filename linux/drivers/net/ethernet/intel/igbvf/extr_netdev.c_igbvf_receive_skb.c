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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct igbvf_adapter {int flags; TYPE_1__* rx_ring; int /*<<< orphan*/  active_vlans; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int E1000_RXDEXT_STATERR_LB ; 
 int E1000_RXD_SPC_VLAN_MASK ; 
 int E1000_RXD_STAT_VP ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int IGBVF_FLAG_RX_LB_VLAN_BSWAP ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int be16_to_cpu (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igbvf_receive_skb(struct igbvf_adapter *adapter,
			      struct net_device *netdev,
			      struct sk_buff *skb,
			      u32 status, u16 vlan)
{
	u16 vid;

	if (status & E1000_RXD_STAT_VP) {
		if ((adapter->flags & IGBVF_FLAG_RX_LB_VLAN_BSWAP) &&
		    (status & E1000_RXDEXT_STATERR_LB))
			vid = be16_to_cpu(vlan) & E1000_RXD_SPC_VLAN_MASK;
		else
			vid = le16_to_cpu(vlan) & E1000_RXD_SPC_VLAN_MASK;
		if (test_bit(vid, adapter->active_vlans))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	}

	napi_gro_receive(&adapter->rx_ring->napi, skb);
}