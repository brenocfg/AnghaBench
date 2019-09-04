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
struct sk_buff {scalar_t__ dev; } ;
struct bnxt_napi {int /*<<< orphan*/  napi; int /*<<< orphan*/  index; } ;
struct bnxt {scalar_t__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_vf_rep_rx (struct bnxt*,struct sk_buff*) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnxt_deliver_skb(struct bnxt *bp, struct bnxt_napi *bnapi,
			     struct sk_buff *skb)
{
	if (skb->dev != bp->dev) {
		/* this packet belongs to a vf-rep */
		bnxt_vf_rep_rx(bp, skb);
		return;
	}
	skb_record_rx_queue(skb, bnapi->index);
	napi_gro_receive(&bnapi->napi, skb);
}