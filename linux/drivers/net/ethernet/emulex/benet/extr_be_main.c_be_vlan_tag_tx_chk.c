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
struct sk_buff {int dummy; } ;
struct be_adapter {scalar_t__ qnq_vid; scalar_t__ pvid; } ;

/* Variables and functions */
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static int be_vlan_tag_tx_chk(struct be_adapter *adapter, struct sk_buff *skb)
{
	return skb_vlan_tag_present(skb) || adapter->pvid || adapter->qnq_vid;
}