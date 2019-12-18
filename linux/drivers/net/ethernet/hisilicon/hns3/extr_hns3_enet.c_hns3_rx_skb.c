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
struct sk_buff {int dummy; } ;
struct hns3_enet_ring {TYPE_1__* tqp_vector; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_gro_flush (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ skb_has_frag_list (struct sk_buff*) ; 

__attribute__((used)) static void hns3_rx_skb(struct hns3_enet_ring *ring, struct sk_buff *skb)
{
	if (skb_has_frag_list(skb))
		napi_gro_flush(&ring->tqp_vector->napi, false);

	napi_gro_receive(&ring->tqp_vector->napi, skb);
}