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
struct nfp_net_dp {unsigned int num_tx_rings; int /*<<< orphan*/ * tx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_tx_ring_bufs_free (struct nfp_net_dp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_tx_ring_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_tx_rings_free(struct nfp_net_dp *dp)
{
	unsigned int r;

	for (r = 0; r < dp->num_tx_rings; r++) {
		nfp_net_tx_ring_bufs_free(dp, &dp->tx_rings[r]);
		nfp_net_tx_ring_free(&dp->tx_rings[r]);
	}

	kfree(dp->tx_rings);
}