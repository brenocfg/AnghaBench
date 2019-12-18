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
struct nfp_net_r_vector {int /*<<< orphan*/  nfp_net; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ nfp_ctrl_tx_one (int /*<<< orphan*/ ,struct nfp_net_r_vector*,struct sk_buff*,int) ; 

__attribute__((used)) static void __nfp_ctrl_tx_queued(struct nfp_net_r_vector *r_vec)
{
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(&r_vec->queue)))
		if (nfp_ctrl_tx_one(r_vec->nfp_net, r_vec, skb, true))
			return;
}