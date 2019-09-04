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
struct i40e_vsi {scalar_t__ uplink_seid; int /*<<< orphan*/  veb_idx; int /*<<< orphan*/  flags; } ;
struct i40e_veb {scalar_t__ seid; scalar_t__ uplink_seid; int /*<<< orphan*/  veb_idx; struct i40e_pf* pf; } ;
struct i40e_pf {int num_alloc_vsi; scalar_t__ mac_seid; size_t lan_vsi; int /*<<< orphan*/  hw; struct i40e_vsi** vsi; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_NO_VEB ; 
 int /*<<< orphan*/  I40E_VSI_FLAG_VEB_OWNER ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  i40e_aq_delete_element (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_veb_clear (struct i40e_veb*) ; 

void i40e_veb_release(struct i40e_veb *veb)
{
	struct i40e_vsi *vsi = NULL;
	struct i40e_pf *pf;
	int i, n = 0;

	pf = veb->pf;

	/* find the remaining VSI and check for extras */
	for (i = 0; i < pf->num_alloc_vsi; i++) {
		if (pf->vsi[i] && pf->vsi[i]->uplink_seid == veb->seid) {
			n++;
			vsi = pf->vsi[i];
		}
	}
	if (n != 1) {
		dev_info(&pf->pdev->dev,
			 "can't remove VEB %d with %d VSIs left\n",
			 veb->seid, n);
		return;
	}

	/* move the remaining VSI to uplink veb */
	vsi->flags &= ~I40E_VSI_FLAG_VEB_OWNER;
	if (veb->uplink_seid) {
		vsi->uplink_seid = veb->uplink_seid;
		if (veb->uplink_seid == pf->mac_seid)
			vsi->veb_idx = I40E_NO_VEB;
		else
			vsi->veb_idx = veb->veb_idx;
	} else {
		/* floating VEB */
		vsi->uplink_seid = pf->vsi[pf->lan_vsi]->uplink_seid;
		vsi->veb_idx = pf->vsi[pf->lan_vsi]->veb_idx;
	}

	i40e_aq_delete_element(&pf->hw, veb->seid, NULL);
	i40e_veb_clear(veb);
}