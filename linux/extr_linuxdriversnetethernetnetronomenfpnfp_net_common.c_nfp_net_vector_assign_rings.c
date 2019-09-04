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
struct nfp_net_r_vector {int /*<<< orphan*/ * xdp_ring; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; } ;
struct nfp_net_dp {int num_rx_rings; int num_stack_tx_rings; int num_tx_rings; int /*<<< orphan*/ * tx_rings; int /*<<< orphan*/ * rx_rings; } ;

/* Variables and functions */

__attribute__((used)) static void
nfp_net_vector_assign_rings(struct nfp_net_dp *dp,
			    struct nfp_net_r_vector *r_vec, int idx)
{
	r_vec->rx_ring = idx < dp->num_rx_rings ? &dp->rx_rings[idx] : NULL;
	r_vec->tx_ring =
		idx < dp->num_stack_tx_rings ? &dp->tx_rings[idx] : NULL;

	r_vec->xdp_ring = idx < dp->num_tx_rings - dp->num_stack_tx_rings ?
		&dp->tx_rings[dp->num_stack_tx_rings + idx] : NULL;
}