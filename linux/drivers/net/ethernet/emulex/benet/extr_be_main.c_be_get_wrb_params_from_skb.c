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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ encapsulation; } ;
struct be_wrb_params {int /*<<< orphan*/  features; int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  lso_mss; } ;
struct be_adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_WRB_F_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  CRC ; 
 int /*<<< orphan*/  IPCS ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  LSO ; 
 int /*<<< orphan*/  LSO6 ; 
 int /*<<< orphan*/  TCPCS ; 
 int /*<<< orphan*/  UDPCS ; 
 int /*<<< orphan*/  VLAN ; 
 int /*<<< orphan*/  be_get_tx_vlan_tag (struct be_adapter*,struct sk_buff*) ; 
 int /*<<< orphan*/  lancer_chip (struct be_adapter*) ; 
 scalar_t__ skb_inner_ip_proto (struct sk_buff*) ; 
 scalar_t__ skb_ip_proto (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_is_gso_v6 (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

__attribute__((used)) static void be_get_wrb_params_from_skb(struct be_adapter *adapter,
				       struct sk_buff *skb,
				       struct be_wrb_params *wrb_params)
{
	u16 proto;

	if (skb_is_gso(skb)) {
		BE_WRB_F_SET(wrb_params->features, LSO, 1);
		wrb_params->lso_mss = skb_shinfo(skb)->gso_size;
		if (skb_is_gso_v6(skb) && !lancer_chip(adapter))
			BE_WRB_F_SET(wrb_params->features, LSO6, 1);
	} else if (skb->ip_summed == CHECKSUM_PARTIAL) {
		if (skb->encapsulation) {
			BE_WRB_F_SET(wrb_params->features, IPCS, 1);
			proto = skb_inner_ip_proto(skb);
		} else {
			proto = skb_ip_proto(skb);
		}
		if (proto == IPPROTO_TCP)
			BE_WRB_F_SET(wrb_params->features, TCPCS, 1);
		else if (proto == IPPROTO_UDP)
			BE_WRB_F_SET(wrb_params->features, UDPCS, 1);
	}

	if (skb_vlan_tag_present(skb)) {
		BE_WRB_F_SET(wrb_params->features, VLAN, 1);
		wrb_params->vlan_tag = be_get_tx_vlan_tag(adapter, skb);
	}

	BE_WRB_F_SET(wrb_params->features, CRC, 1);
}