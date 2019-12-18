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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int TxVlanTag ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int swab16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 cp_tx_vlan_tag(struct sk_buff *skb)
{
	return skb_vlan_tag_present(skb) ?
		TxVlanTag | swab16(skb_vlan_tag_get(skb)) : 0x00;
}