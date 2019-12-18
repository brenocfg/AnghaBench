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
struct ice_vsi {int alloc_txq; int alloc_rxq; int /*<<< orphan*/ ** rx_rings; int /*<<< orphan*/ ** tx_rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void ice_vsi_clear_rings(struct ice_vsi *vsi)
{
	int i;

	if (vsi->tx_rings) {
		for (i = 0; i < vsi->alloc_txq; i++) {
			if (vsi->tx_rings[i]) {
				kfree_rcu(vsi->tx_rings[i], rcu);
				vsi->tx_rings[i] = NULL;
			}
		}
	}
	if (vsi->rx_rings) {
		for (i = 0; i < vsi->alloc_rxq; i++) {
			if (vsi->rx_rings[i]) {
				kfree_rcu(vsi->rx_rings[i], rcu);
				vsi->rx_rings[i] = NULL;
			}
		}
	}
}