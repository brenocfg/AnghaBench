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
struct nfp_net_dp {scalar_t__ num_r_vecs; scalar_t__ num_rx_rings; scalar_t__ num_tx_rings; scalar_t__ num_stack_tx_rings; int /*<<< orphan*/  dev; } ;
struct nfp_net {scalar_t__ max_r_vecs; struct nfp_net_dp dp; int /*<<< orphan*/  irq_entries; } ;
struct msix_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFP_NET_NON_Q_VECTORS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct msix_entry*,int) ; 
 void* min (scalar_t__,scalar_t__) ; 

void
nfp_net_irqs_assign(struct nfp_net *nn, struct msix_entry *irq_entries,
		    unsigned int n)
{
	struct nfp_net_dp *dp = &nn->dp;

	nn->max_r_vecs = n - NFP_NET_NON_Q_VECTORS;
	dp->num_r_vecs = nn->max_r_vecs;

	memcpy(nn->irq_entries, irq_entries, sizeof(*irq_entries) * n);

	if (dp->num_rx_rings > dp->num_r_vecs ||
	    dp->num_tx_rings > dp->num_r_vecs)
		dev_warn(nn->dp.dev, "More rings (%d,%d) than vectors (%d).\n",
			 dp->num_rx_rings, dp->num_tx_rings,
			 dp->num_r_vecs);

	dp->num_rx_rings = min(dp->num_r_vecs, dp->num_rx_rings);
	dp->num_tx_rings = min(dp->num_r_vecs, dp->num_tx_rings);
	dp->num_stack_tx_rings = dp->num_tx_rings;
}