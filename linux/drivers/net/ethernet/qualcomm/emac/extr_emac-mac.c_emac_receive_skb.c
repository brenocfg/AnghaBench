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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct emac_rx_queue {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_TAG_TO_VLAN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void emac_receive_skb(struct emac_rx_queue *rx_q,
			     struct sk_buff *skb,
			     u16 vlan_tag, bool vlan_flag)
{
	if (vlan_flag) {
		u16 vlan;

		EMAC_TAG_TO_VLAN(vlan_tag, vlan);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan);
	}

	napi_gro_receive(&rx_q->napi, skb);
}