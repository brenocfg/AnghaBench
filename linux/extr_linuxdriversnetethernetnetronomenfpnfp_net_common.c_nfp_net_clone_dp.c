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
struct nfp_net_dp {scalar_t__ num_stack_tx_rings; scalar_t__ num_r_vecs; int /*<<< orphan*/ * rx_rings; int /*<<< orphan*/ * tx_rings; scalar_t__ fl_bufsz; } ;
struct nfp_net {struct nfp_net_dp dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct nfp_net_dp* kmalloc (int,int /*<<< orphan*/ ) ; 

struct nfp_net_dp *nfp_net_clone_dp(struct nfp_net *nn)
{
	struct nfp_net_dp *new;

	new = kmalloc(sizeof(*new), GFP_KERNEL);
	if (!new)
		return NULL;

	*new = nn->dp;

	/* Clear things which need to be recomputed */
	new->fl_bufsz = 0;
	new->tx_rings = NULL;
	new->rx_rings = NULL;
	new->num_r_vecs = 0;
	new->num_stack_tx_rings = 0;

	return new;
}