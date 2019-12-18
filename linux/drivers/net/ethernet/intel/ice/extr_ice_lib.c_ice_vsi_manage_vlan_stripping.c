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
struct TYPE_10__ {int /*<<< orphan*/  vlan_flags; int /*<<< orphan*/  valid_sections; } ;
struct ice_vsi_ctx {TYPE_5__ info; } ;
struct TYPE_9__ {int /*<<< orphan*/  vlan_flags; } ;
struct ice_vsi {TYPE_4__ info; int /*<<< orphan*/  idx; TYPE_2__* back; } ;
struct TYPE_8__ {int /*<<< orphan*/  sq_last_status; } ;
struct ice_hw {TYPE_3__ adminq; } ;
struct device {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_7__ {struct ice_hw hw; TYPE_1__* pdev; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQ_VSI_PROP_VLAN_VALID ; 
 int /*<<< orphan*/  ICE_AQ_VSI_VLAN_EMOD_NOTHING ; 
 int /*<<< orphan*/  ICE_AQ_VSI_VLAN_EMOD_STR_BOTH ; 
 int /*<<< orphan*/  ICE_AQ_VSI_VLAN_MODE_ALL ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct ice_vsi_ctx*) ; 
 struct ice_vsi_ctx* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int ice_update_vsi (struct ice_hw*,int /*<<< orphan*/ ,struct ice_vsi_ctx*,int /*<<< orphan*/ *) ; 

int ice_vsi_manage_vlan_stripping(struct ice_vsi *vsi, bool ena)
{
	struct device *dev = &vsi->back->pdev->dev;
	struct ice_hw *hw = &vsi->back->hw;
	struct ice_vsi_ctx *ctxt;
	enum ice_status status;
	int ret = 0;

	ctxt = devm_kzalloc(dev, sizeof(*ctxt), GFP_KERNEL);
	if (!ctxt)
		return -ENOMEM;

	/* Here we are configuring what the VSI should do with the VLAN tag in
	 * the Rx packet. We can either leave the tag in the packet or put it in
	 * the Rx descriptor.
	 */
	if (ena)
		/* Strip VLAN tag from Rx packet and put it in the desc */
		ctxt->info.vlan_flags = ICE_AQ_VSI_VLAN_EMOD_STR_BOTH;
	else
		/* Disable stripping. Leave tag in packet */
		ctxt->info.vlan_flags = ICE_AQ_VSI_VLAN_EMOD_NOTHING;

	/* Allow all packets untagged/tagged */
	ctxt->info.vlan_flags |= ICE_AQ_VSI_VLAN_MODE_ALL;

	ctxt->info.valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_VLAN_VALID);

	status = ice_update_vsi(hw, vsi->idx, ctxt, NULL);
	if (status) {
		dev_err(dev, "update VSI for VLAN strip failed, ena = %d err %d aq_err %d\n",
			ena, status, hw->adminq.sq_last_status);
		ret = -EIO;
		goto out;
	}

	vsi->info.vlan_flags = ctxt->info.vlan_flags;
out:
	devm_kfree(dev, ctxt);
	return ret;
}