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
typedef  int /*<<< orphan*/  u16 ;
struct sky2_port {size_t rx_next; TYPE_1__* rx_ring; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_rx_tag(struct sky2_port *sky2, u16 length)
{
	struct sk_buff *skb;

	skb = sky2->rx_ring[sky2->rx_next].skb;
	__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), be16_to_cpu(length));
}