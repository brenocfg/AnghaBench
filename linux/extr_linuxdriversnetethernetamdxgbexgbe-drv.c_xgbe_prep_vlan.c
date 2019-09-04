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
struct xgbe_packet_data {int /*<<< orphan*/  vlan_ctag; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static void xgbe_prep_vlan(struct sk_buff *skb, struct xgbe_packet_data *packet)
{
	if (skb_vlan_tag_present(skb))
		packet->vlan_ctag = skb_vlan_tag_get(skb);
}