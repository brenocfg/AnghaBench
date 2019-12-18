#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct cp_private {int /*<<< orphan*/  napi; TYPE_2__* dev; } ;
struct cp_desc {int /*<<< orphan*/  opts2; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int RxVlanTagged ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  swab16 (int) ; 

__attribute__((used)) static inline void cp_rx_skb (struct cp_private *cp, struct sk_buff *skb,
			      struct cp_desc *desc)
{
	u32 opts2 = le32_to_cpu(desc->opts2);

	skb->protocol = eth_type_trans (skb, cp->dev);

	cp->dev->stats.rx_packets++;
	cp->dev->stats.rx_bytes += skb->len;

	if (opts2 & RxVlanTagged)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), swab16(opts2 & 0xffff));

	napi_gro_receive(&cp->napi, skb);
}