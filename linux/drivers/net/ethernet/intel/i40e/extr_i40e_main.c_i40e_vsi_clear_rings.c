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
struct i40e_vsi {int alloc_queue_pairs; int /*<<< orphan*/ ** xdp_rings; int /*<<< orphan*/ ** rx_rings; int /*<<< orphan*/ ** tx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void i40e_vsi_clear_rings(struct i40e_vsi *vsi)
{
	int i;

	if (vsi->tx_rings && vsi->tx_rings[0]) {
		for (i = 0; i < vsi->alloc_queue_pairs; i++) {
			kfree_rcu(vsi->tx_rings[i], rcu);
			vsi->tx_rings[i] = NULL;
			vsi->rx_rings[i] = NULL;
			if (vsi->xdp_rings)
				vsi->xdp_rings[i] = NULL;
		}
	}
}