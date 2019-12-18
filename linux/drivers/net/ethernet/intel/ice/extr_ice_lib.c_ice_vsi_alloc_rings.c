#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {int alloc_txq; int alloc_rxq; struct ice_ring** rx_rings; int /*<<< orphan*/  num_rx_desc; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * rxq_map; struct ice_ring** tx_rings; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/ * txq_map; struct ice_pf* back; } ;
struct ice_ring {int q_index; int ring_active; int /*<<< orphan*/  count; int /*<<< orphan*/ * dev; int /*<<< orphan*/  netdev; struct ice_vsi* vsi; int /*<<< orphan*/  reg_idx; } ;
struct ice_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ice_vsi_clear_rings (struct ice_vsi*) ; 
 struct ice_ring* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_alloc_rings(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	int i;

	/* Allocate Tx rings */
	for (i = 0; i < vsi->alloc_txq; i++) {
		struct ice_ring *ring;

		/* allocate with kzalloc(), free with kfree_rcu() */
		ring = kzalloc(sizeof(*ring), GFP_KERNEL);

		if (!ring)
			goto err_out;

		ring->q_index = i;
		ring->reg_idx = vsi->txq_map[i];
		ring->ring_active = false;
		ring->vsi = vsi;
		ring->dev = &pf->pdev->dev;
		ring->count = vsi->num_tx_desc;
		vsi->tx_rings[i] = ring;
	}

	/* Allocate Rx rings */
	for (i = 0; i < vsi->alloc_rxq; i++) {
		struct ice_ring *ring;

		/* allocate with kzalloc(), free with kfree_rcu() */
		ring = kzalloc(sizeof(*ring), GFP_KERNEL);
		if (!ring)
			goto err_out;

		ring->q_index = i;
		ring->reg_idx = vsi->rxq_map[i];
		ring->ring_active = false;
		ring->vsi = vsi;
		ring->netdev = vsi->netdev;
		ring->dev = &pf->pdev->dev;
		ring->count = vsi->num_rx_desc;
		vsi->rx_rings[i] = ring;
	}

	return 0;

err_out:
	ice_vsi_clear_rings(vsi);
	return -ENOMEM;
}