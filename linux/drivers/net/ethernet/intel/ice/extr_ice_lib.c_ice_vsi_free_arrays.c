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
struct ice_vsi {int /*<<< orphan*/ * rxq_map; int /*<<< orphan*/ * txq_map; int /*<<< orphan*/ * rx_rings; int /*<<< orphan*/ * tx_rings; int /*<<< orphan*/ * q_vectors; struct ice_pf* back; } ;
struct ice_pf {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ice_vsi_free_arrays(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;

	/* free the ring and vector containers */
	if (vsi->q_vectors) {
		devm_kfree(&pf->pdev->dev, vsi->q_vectors);
		vsi->q_vectors = NULL;
	}
	if (vsi->tx_rings) {
		devm_kfree(&pf->pdev->dev, vsi->tx_rings);
		vsi->tx_rings = NULL;
	}
	if (vsi->rx_rings) {
		devm_kfree(&pf->pdev->dev, vsi->rx_rings);
		vsi->rx_rings = NULL;
	}
	if (vsi->txq_map) {
		devm_kfree(&pf->pdev->dev, vsi->txq_map);
		vsi->txq_map = NULL;
	}
	if (vsi->rxq_map) {
		devm_kfree(&pf->pdev->dev, vsi->rxq_map);
		vsi->rxq_map = NULL;
	}
}