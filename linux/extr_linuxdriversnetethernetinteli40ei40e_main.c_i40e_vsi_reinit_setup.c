#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct i40e_vsi {int base_queue; int alloc_queue_pairs; scalar_t__ type; int netdev_registered; int /*<<< orphan*/  seid; int /*<<< orphan*/ * netdev; int /*<<< orphan*/  idx; struct i40e_pf* back; } ;
struct TYPE_8__ {int /*<<< orphan*/  perm_addr; } ;
struct TYPE_10__ {TYPE_3__ mac; } ;
struct i40e_pf {size_t lan_vsi; TYPE_5__ hw; TYPE_4__** vsi; int /*<<< orphan*/  main_vsi_seid; TYPE_1__* pdev; int /*<<< orphan*/  qp_pile; } ;
struct TYPE_7__ {scalar_t__ enabled_tc; } ;
struct TYPE_9__ {int /*<<< orphan*/  seid; TYPE_2__ tc_config; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 
 int i40e_alloc_rings (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_aq_delete_element (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int i40e_get_lump (struct i40e_pf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_put_lump (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_rm_default_mac_filter (struct i40e_vsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_set_num_rings_in_vsi (struct i40e_vsi*) ; 
 int i40e_vsi_alloc_arrays (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_vsi_clear (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_clear_rings (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_config_tc (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  i40e_vsi_free_arrays (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_vsi_free_q_vectors (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_map_rings_to_vectors (struct i40e_vsi*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i40e_vsi *i40e_vsi_reinit_setup(struct i40e_vsi *vsi)
{
	u16 alloc_queue_pairs;
	struct i40e_pf *pf;
	u8 enabled_tc;
	int ret;

	if (!vsi)
		return NULL;

	pf = vsi->back;

	i40e_put_lump(pf->qp_pile, vsi->base_queue, vsi->idx);
	i40e_vsi_clear_rings(vsi);

	i40e_vsi_free_arrays(vsi, false);
	i40e_set_num_rings_in_vsi(vsi);
	ret = i40e_vsi_alloc_arrays(vsi, false);
	if (ret)
		goto err_vsi;

	alloc_queue_pairs = vsi->alloc_queue_pairs *
			    (i40e_enabled_xdp_vsi(vsi) ? 2 : 1);

	ret = i40e_get_lump(pf, pf->qp_pile, alloc_queue_pairs, vsi->idx);
	if (ret < 0) {
		dev_info(&pf->pdev->dev,
			 "failed to get tracking for %d queues for VSI %d err %d\n",
			 alloc_queue_pairs, vsi->seid, ret);
		goto err_vsi;
	}
	vsi->base_queue = ret;

	/* Update the FW view of the VSI. Force a reset of TC and queue
	 * layout configurations.
	 */
	enabled_tc = pf->vsi[pf->lan_vsi]->tc_config.enabled_tc;
	pf->vsi[pf->lan_vsi]->tc_config.enabled_tc = 0;
	pf->vsi[pf->lan_vsi]->seid = pf->main_vsi_seid;
	i40e_vsi_config_tc(pf->vsi[pf->lan_vsi], enabled_tc);
	if (vsi->type == I40E_VSI_MAIN)
		i40e_rm_default_mac_filter(vsi, pf->hw.mac.perm_addr);

	/* assign it some queues */
	ret = i40e_alloc_rings(vsi);
	if (ret)
		goto err_rings;

	/* map all of the rings to the q_vectors */
	i40e_vsi_map_rings_to_vectors(vsi);
	return vsi;

err_rings:
	i40e_vsi_free_q_vectors(vsi);
	if (vsi->netdev_registered) {
		vsi->netdev_registered = false;
		unregister_netdev(vsi->netdev);
		free_netdev(vsi->netdev);
		vsi->netdev = NULL;
	}
	i40e_aq_delete_element(&pf->hw, vsi->seid, NULL);
err_vsi:
	i40e_vsi_clear(vsi);
	return NULL;
}