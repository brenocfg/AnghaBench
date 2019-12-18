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
struct nfp_net_r_vector {int /*<<< orphan*/  lock; } ;
struct nfp_net {struct nfp_net_r_vector* r_vecs; } ;

/* Variables and functions */
 int nfp_ctrl_tx_one (struct nfp_net*,struct nfp_net_r_vector*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool nfp_ctrl_tx(struct nfp_net *nn, struct sk_buff *skb)
{
	struct nfp_net_r_vector *r_vec = &nn->r_vecs[0];
	bool ret;

	spin_lock_bh(&r_vec->lock);
	ret = nfp_ctrl_tx_one(nn, r_vec, skb, false);
	spin_unlock_bh(&r_vec->lock);

	return ret;
}