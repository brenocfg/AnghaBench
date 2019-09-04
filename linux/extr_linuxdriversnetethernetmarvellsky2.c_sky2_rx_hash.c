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
typedef  int /*<<< orphan*/  u32 ;
struct sky2_port {size_t rx_next; TYPE_1__* rx_ring; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_rx_hash(struct sky2_port *sky2, u32 status)
{
	struct sk_buff *skb;

	skb = sky2->rx_ring[sky2->rx_next].skb;
	skb_set_hash(skb, le32_to_cpu(status), PKT_HASH_TYPE_L3);
}