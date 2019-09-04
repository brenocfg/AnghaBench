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
struct ice_vsi {scalar_t__ alloc_rxq; scalar_t__ alloc_txq; int /*<<< orphan*/  vsi_num; scalar_t__ num_q_vectors; int /*<<< orphan*/  idx; int /*<<< orphan*/  base_vector; struct ice_pf* back; int /*<<< orphan*/ * netdev; } ;
struct ice_pf {int /*<<< orphan*/  q_left_rx; int /*<<< orphan*/  q_left_tx; int /*<<< orphan*/  hw; int /*<<< orphan*/  num_avail_msix; int /*<<< orphan*/  irq_tracker; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ICE_FLAG_RSS_ENA ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_free_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_remove_vsi_fltr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_rss_clean (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_clear (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_clear_rings (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_close (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_delete (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_dis_irq (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_free_q_vectors (struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_put_qs (struct ice_vsi*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ice_vsi_release(struct ice_vsi *vsi)
{
	struct ice_pf *pf;

	if (!vsi->back)
		return -ENODEV;
	pf = vsi->back;

	if (vsi->netdev) {
		unregister_netdev(vsi->netdev);
		free_netdev(vsi->netdev);
		vsi->netdev = NULL;
	}

	if (test_bit(ICE_FLAG_RSS_ENA, pf->flags))
		ice_rss_clean(vsi);

	/* Disable VSI and free resources */
	ice_vsi_dis_irq(vsi);
	ice_vsi_close(vsi);

	/* reclaim interrupt vectors back to PF */
	ice_free_res(vsi->back->irq_tracker, vsi->base_vector, vsi->idx);
	pf->num_avail_msix += vsi->num_q_vectors;

	ice_remove_vsi_fltr(&pf->hw, vsi->vsi_num);
	ice_vsi_delete(vsi);
	ice_vsi_free_q_vectors(vsi);
	ice_vsi_clear_rings(vsi);

	ice_vsi_put_qs(vsi);
	pf->q_left_tx += vsi->alloc_txq;
	pf->q_left_rx += vsi->alloc_rxq;

	ice_vsi_clear(vsi);

	return 0;
}