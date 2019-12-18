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
struct nfp_net_dp {unsigned int num_rx_rings; int /*<<< orphan*/ * rx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_rx_ring_bufs_free (struct nfp_net_dp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_rx_ring_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_rx_rings_free(struct nfp_net_dp *dp)
{
	unsigned int r;

	for (r = 0; r < dp->num_rx_rings; r++) {
		nfp_net_rx_ring_bufs_free(dp, &dp->rx_rings[r]);
		nfp_net_rx_ring_free(&dp->rx_rings[r]);
	}

	kfree(dp->rx_rings);
}