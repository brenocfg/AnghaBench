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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qlcnic_adapter {int rx_pvid; int flags; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 int QLCNIC_TAGGING_ENABLED ; 
 scalar_t__ VLAN_HLEN ; 
 int /*<<< orphan*/  __vlan_get_tag (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,struct ethhdr*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static inline int qlcnic_check_rx_tagging(struct qlcnic_adapter *adapter,
					  struct sk_buff *skb, u16 *vlan_tag)
{
	struct ethhdr *eth_hdr;

	if (!__vlan_get_tag(skb, vlan_tag)) {
		eth_hdr = (struct ethhdr *)skb->data;
		memmove(skb->data + VLAN_HLEN, eth_hdr, ETH_ALEN * 2);
		skb_pull(skb, VLAN_HLEN);
	}
	if (!adapter->rx_pvid)
		return 0;

	if (*vlan_tag == adapter->rx_pvid) {
		/* Outer vlan tag. Packet should follow non-vlan path */
		*vlan_tag = 0xffff;
		return 0;
	}
	if (adapter->flags & QLCNIC_TAGGING_ENABLED)
		return 0;

	return -EINVAL;
}