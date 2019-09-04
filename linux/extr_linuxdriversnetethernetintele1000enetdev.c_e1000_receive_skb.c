#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int E1000_RXD_STAT_VP ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000e_rx_hwtstamp (struct e1000_adapter*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void e1000_receive_skb(struct e1000_adapter *adapter,
			      struct net_device *netdev, struct sk_buff *skb,
			      u32 staterr, __le16 vlan)
{
	u16 tag = le16_to_cpu(vlan);

	e1000e_rx_hwtstamp(adapter, staterr, skb);

	skb->protocol = eth_type_trans(skb, netdev);

	if (staterr & E1000_RXD_STAT_VP)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tag);

	napi_gro_receive(&adapter->napi, skb);
}