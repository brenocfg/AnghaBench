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
struct nfp_net {int /*<<< orphan*/ * r_vecs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ nfp_net_rx_ring_alloc (struct nfp_net_dp*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfp_net_rx_ring_bufs_alloc (struct nfp_net_dp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_rx_ring_bufs_free (struct nfp_net_dp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_rx_ring_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_rx_ring_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int nfp_net_rx_rings_prepare(struct nfp_net *nn, struct nfp_net_dp *dp)
{
	unsigned int r;

	dp->rx_rings = kcalloc(dp->num_rx_rings, sizeof(*dp->rx_rings),
			       GFP_KERNEL);
	if (!dp->rx_rings)
		return -ENOMEM;

	for (r = 0; r < dp->num_rx_rings; r++) {
		nfp_net_rx_ring_init(&dp->rx_rings[r], &nn->r_vecs[r], r);

		if (nfp_net_rx_ring_alloc(dp, &dp->rx_rings[r]))
			goto err_free_prev;

		if (nfp_net_rx_ring_bufs_alloc(dp, &dp->rx_rings[r]))
			goto err_free_ring;
	}

	return 0;

err_free_prev:
	while (r--) {
		nfp_net_rx_ring_bufs_free(dp, &dp->rx_rings[r]);
err_free_ring:
		nfp_net_rx_ring_free(&dp->rx_rings[r]);
	}
	kfree(dp->rx_rings);
	return -ENOMEM;
}