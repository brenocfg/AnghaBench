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
struct nfp_net_rx_ring {int dummy; } ;
struct nfp_net_r_vector {struct nfp_net* nfp_net; struct nfp_net_rx_ring* rx_ring; } ;
struct nfp_net_dp {int dummy; } ;
struct nfp_net {struct nfp_net_dp dp; } ;

/* Variables and functions */
 scalar_t__ nfp_ctrl_rx_one (struct nfp_net*,struct nfp_net_dp*,struct nfp_net_r_vector*,struct nfp_net_rx_ring*) ; 

__attribute__((used)) static bool nfp_ctrl_rx(struct nfp_net_r_vector *r_vec)
{
	struct nfp_net_rx_ring *rx_ring = r_vec->rx_ring;
	struct nfp_net *nn = r_vec->nfp_net;
	struct nfp_net_dp *dp = &nn->dp;
	unsigned int budget = 512;

	while (nfp_ctrl_rx_one(nn, dp, r_vec, rx_ring) && budget--)
		continue;

	return budget;
}