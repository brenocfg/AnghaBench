#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {int /*<<< orphan*/  enabled_tc; } ;
struct i40e_vsi {scalar_t__ seid; scalar_t__ uplink_seid; int flags; int type; int alloc_queue_pairs; int base_queue; int netdev_registered; int /*<<< orphan*/ * netdev; int /*<<< orphan*/  idx; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  veb_idx; TYPE_3__* back; TYPE_1__ tc_config; } ;
struct i40e_veb {scalar_t__ seid; int /*<<< orphan*/  idx; int /*<<< orphan*/  bridge_mode; } ;
struct i40e_pf {scalar_t__ mac_seid; int num_alloc_vsi; size_t lan_vsi; int flags; int hw_features; int /*<<< orphan*/  hw; TYPE_4__* pdev; int /*<<< orphan*/  qp_pile; struct i40e_vsi** vsi; struct i40e_veb** veb; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_2__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_MODE_VEPA ; 
 int I40E_FLAG_VEB_MODE_ENABLED ; 
 int I40E_HW_RSS_AQ_CAPABLE ; 
 int I40E_MAX_VEB ; 
 int /*<<< orphan*/  I40E_NO_VEB ; 
#define  I40E_VSI_FDIR 130 
 int I40E_VSI_FLAG_VEB_OWNER ; 
#define  I40E_VSI_MAIN 129 
 scalar_t__ I40E_VSI_SRIOV ; 
#define  I40E_VSI_VMDQ2 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 
 int i40e_add_vsi (struct i40e_vsi*) ; 
 int i40e_alloc_rings (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_aq_delete_element (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_config_bridge_mode (struct i40e_veb*) ; 
 int i40e_config_netdev (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_dcbnl_setup (struct i40e_vsi*) ; 
 scalar_t__ i40e_enabled_xdp_vsi (struct i40e_vsi*) ; 
 int i40e_get_lump (struct i40e_pf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct i40e_veb* i40e_veb_setup (struct i40e_pf*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_vsi_clear (struct i40e_vsi*) ; 
 int i40e_vsi_config_rss (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_free_q_vectors (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_map_rings_to_vectors (struct i40e_vsi*) ; 
 int i40e_vsi_mem_alloc (struct i40e_pf*,scalar_t__) ; 
 int /*<<< orphan*/  i40e_vsi_reset_stats (struct i40e_vsi*) ; 
 int i40e_vsi_setup_vectors (struct i40e_vsi*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ *) ; 
 int register_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ *) ; 

struct i40e_vsi *i40e_vsi_setup(struct i40e_pf *pf, u8 type,
				u16 uplink_seid, u32 param1)
{
	struct i40e_vsi *vsi = NULL;
	struct i40e_veb *veb = NULL;
	u16 alloc_queue_pairs;
	int ret, i;
	int v_idx;

	/* The requested uplink_seid must be either
	 *     - the PF's port seid
	 *              no VEB is needed because this is the PF
	 *              or this is a Flow Director special case VSI
	 *     - seid of an existing VEB
	 *     - seid of a VSI that owns an existing VEB
	 *     - seid of a VSI that doesn't own a VEB
	 *              a new VEB is created and the VSI becomes the owner
	 *     - seid of the PF VSI, which is what creates the first VEB
	 *              this is a special case of the previous
	 *
	 * Find which uplink_seid we were given and create a new VEB if needed
	 */
	for (i = 0; i < I40E_MAX_VEB; i++) {
		if (pf->veb[i] && pf->veb[i]->seid == uplink_seid) {
			veb = pf->veb[i];
			break;
		}
	}

	if (!veb && uplink_seid != pf->mac_seid) {

		for (i = 0; i < pf->num_alloc_vsi; i++) {
			if (pf->vsi[i] && pf->vsi[i]->seid == uplink_seid) {
				vsi = pf->vsi[i];
				break;
			}
		}
		if (!vsi) {
			dev_info(&pf->pdev->dev, "no such uplink_seid %d\n",
				 uplink_seid);
			return NULL;
		}

		if (vsi->uplink_seid == pf->mac_seid)
			veb = i40e_veb_setup(pf, 0, pf->mac_seid, vsi->seid,
					     vsi->tc_config.enabled_tc);
		else if ((vsi->flags & I40E_VSI_FLAG_VEB_OWNER) == 0)
			veb = i40e_veb_setup(pf, 0, vsi->uplink_seid, vsi->seid,
					     vsi->tc_config.enabled_tc);
		if (veb) {
			if (vsi->seid != pf->vsi[pf->lan_vsi]->seid) {
				dev_info(&vsi->back->pdev->dev,
					 "New VSI creation error, uplink seid of LAN VSI expected.\n");
				return NULL;
			}
			/* We come up by default in VEPA mode if SRIOV is not
			 * already enabled, in which case we can't force VEPA
			 * mode.
			 */
			if (!(pf->flags & I40E_FLAG_VEB_MODE_ENABLED)) {
				veb->bridge_mode = BRIDGE_MODE_VEPA;
				pf->flags &= ~I40E_FLAG_VEB_MODE_ENABLED;
			}
			i40e_config_bridge_mode(veb);
		}
		for (i = 0; i < I40E_MAX_VEB && !veb; i++) {
			if (pf->veb[i] && pf->veb[i]->seid == vsi->uplink_seid)
				veb = pf->veb[i];
		}
		if (!veb) {
			dev_info(&pf->pdev->dev, "couldn't add VEB\n");
			return NULL;
		}

		vsi->flags |= I40E_VSI_FLAG_VEB_OWNER;
		uplink_seid = veb->seid;
	}

	/* get vsi sw struct */
	v_idx = i40e_vsi_mem_alloc(pf, type);
	if (v_idx < 0)
		goto err_alloc;
	vsi = pf->vsi[v_idx];
	if (!vsi)
		goto err_alloc;
	vsi->type = type;
	vsi->veb_idx = (veb ? veb->idx : I40E_NO_VEB);

	if (type == I40E_VSI_MAIN)
		pf->lan_vsi = v_idx;
	else if (type == I40E_VSI_SRIOV)
		vsi->vf_id = param1;
	/* assign it some queues */
	alloc_queue_pairs = vsi->alloc_queue_pairs *
			    (i40e_enabled_xdp_vsi(vsi) ? 2 : 1);

	ret = i40e_get_lump(pf, pf->qp_pile, alloc_queue_pairs, vsi->idx);
	if (ret < 0) {
		dev_info(&pf->pdev->dev,
			 "failed to get tracking for %d queues for VSI %d err=%d\n",
			 alloc_queue_pairs, vsi->seid, ret);
		goto err_vsi;
	}
	vsi->base_queue = ret;

	/* get a VSI from the hardware */
	vsi->uplink_seid = uplink_seid;
	ret = i40e_add_vsi(vsi);
	if (ret)
		goto err_vsi;

	switch (vsi->type) {
	/* setup the netdev if needed */
	case I40E_VSI_MAIN:
	case I40E_VSI_VMDQ2:
		ret = i40e_config_netdev(vsi);
		if (ret)
			goto err_netdev;
		ret = register_netdev(vsi->netdev);
		if (ret)
			goto err_netdev;
		vsi->netdev_registered = true;
		netif_carrier_off(vsi->netdev);
#ifdef CONFIG_I40E_DCB
		/* Setup DCB netlink interface */
		i40e_dcbnl_setup(vsi);
#endif /* CONFIG_I40E_DCB */
		/* fall through */

	case I40E_VSI_FDIR:
		/* set up vectors and rings if needed */
		ret = i40e_vsi_setup_vectors(vsi);
		if (ret)
			goto err_msix;

		ret = i40e_alloc_rings(vsi);
		if (ret)
			goto err_rings;

		/* map all of the rings to the q_vectors */
		i40e_vsi_map_rings_to_vectors(vsi);

		i40e_vsi_reset_stats(vsi);
		break;

	default:
		/* no netdev or rings for the other VSI types */
		break;
	}

	if ((pf->hw_features & I40E_HW_RSS_AQ_CAPABLE) &&
	    (vsi->type == I40E_VSI_VMDQ2)) {
		ret = i40e_vsi_config_rss(vsi);
	}
	return vsi;

err_rings:
	i40e_vsi_free_q_vectors(vsi);
err_msix:
	if (vsi->netdev_registered) {
		vsi->netdev_registered = false;
		unregister_netdev(vsi->netdev);
		free_netdev(vsi->netdev);
		vsi->netdev = NULL;
	}
err_netdev:
	i40e_aq_delete_element(&pf->hw, vsi->seid, NULL);
err_vsi:
	i40e_vsi_clear(vsi);
err_alloc:
	return NULL;
}