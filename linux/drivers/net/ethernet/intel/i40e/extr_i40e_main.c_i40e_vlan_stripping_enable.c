#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int valid_sections; int port_vlan_flags; scalar_t__ pvid; } ;
struct i40e_vsi_context {TYPE_1__ info; int /*<<< orphan*/  seid; } ;
struct i40e_vsi {TYPE_4__* back; TYPE_1__ info; int /*<<< orphan*/  seid; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_10__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_12__ {TYPE_3__ aq; } ;
struct TYPE_11__ {TYPE_5__ hw; TYPE_2__* pdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_AQ_VSI_PROP_VLAN_VALID ; 
 int I40E_AQ_VSI_PVLAN_EMOD_STR_BOTH ; 
 int I40E_AQ_VSI_PVLAN_MODE_ALL ; 
 int I40E_AQ_VSI_PVLAN_MODE_MASK ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aq_str (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_update_vsi_params (TYPE_5__*,struct i40e_vsi_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_stat_str (TYPE_5__*,scalar_t__) ; 

void i40e_vlan_stripping_enable(struct i40e_vsi *vsi)
{
	struct i40e_vsi_context ctxt;
	i40e_status ret;

	/* Don't modify stripping options if a port VLAN is active */
	if (vsi->info.pvid)
		return;

	if ((vsi->info.valid_sections &
	     cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID)) &&
	    ((vsi->info.port_vlan_flags & I40E_AQ_VSI_PVLAN_MODE_MASK) == 0))
		return;  /* already enabled */

	vsi->info.valid_sections = cpu_to_le16(I40E_AQ_VSI_PROP_VLAN_VALID);
	vsi->info.port_vlan_flags = I40E_AQ_VSI_PVLAN_MODE_ALL |
				    I40E_AQ_VSI_PVLAN_EMOD_STR_BOTH;

	ctxt.seid = vsi->seid;
	ctxt.info = vsi->info;
	ret = i40e_aq_update_vsi_params(&vsi->back->hw, &ctxt, NULL);
	if (ret) {
		dev_info(&vsi->back->pdev->dev,
			 "update vlan stripping failed, err %s aq_err %s\n",
			 i40e_stat_str(&vsi->back->hw, ret),
			 i40e_aq_str(&vsi->back->hw,
				     vsi->back->hw.aq.asq_last_status));
	}
}