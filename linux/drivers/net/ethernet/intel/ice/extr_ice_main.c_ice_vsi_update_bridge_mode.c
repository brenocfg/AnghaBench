#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ice_aqc_vsi_props {int /*<<< orphan*/  sw_flags; int /*<<< orphan*/  valid_sections; } ;
struct ice_vsi_ctx {struct ice_aqc_vsi_props info; } ;
struct ice_vsi {int /*<<< orphan*/  idx; struct ice_aqc_vsi_props info; TYPE_2__* back; } ;
struct TYPE_6__ {int /*<<< orphan*/  sq_last_status; } ;
struct ice_hw {TYPE_3__ adminq; } ;
struct device {int dummy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_5__ {struct ice_hw hw; TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_MODE_VEB ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQ_VSI_PROP_SW_VALID ; 
 int /*<<< orphan*/  ICE_AQ_VSI_SW_FLAG_ALLOW_LB ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct ice_vsi_ctx*) ; 
 struct ice_vsi_ctx* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int ice_update_vsi (struct ice_hw*,int /*<<< orphan*/ ,struct ice_vsi_ctx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ice_vsi_update_bridge_mode(struct ice_vsi *vsi, u16 bmode)
{
	struct device *dev = &vsi->back->pdev->dev;
	struct ice_aqc_vsi_props *vsi_props;
	struct ice_hw *hw = &vsi->back->hw;
	struct ice_vsi_ctx *ctxt;
	enum ice_status status;
	int ret = 0;

	vsi_props = &vsi->info;

	ctxt = devm_kzalloc(dev, sizeof(*ctxt), GFP_KERNEL);
	if (!ctxt)
		return -ENOMEM;

	ctxt->info = vsi->info;

	if (bmode == BRIDGE_MODE_VEB)
		/* change from VEPA to VEB mode */
		ctxt->info.sw_flags |= ICE_AQ_VSI_SW_FLAG_ALLOW_LB;
	else
		/* change from VEB to VEPA mode */
		ctxt->info.sw_flags &= ~ICE_AQ_VSI_SW_FLAG_ALLOW_LB;
	ctxt->info.valid_sections = cpu_to_le16(ICE_AQ_VSI_PROP_SW_VALID);

	status = ice_update_vsi(hw, vsi->idx, ctxt, NULL);
	if (status) {
		dev_err(dev, "update VSI for bridge mode failed, bmode = %d err %d aq_err %d\n",
			bmode, status, hw->adminq.sq_last_status);
		ret = -EIO;
		goto out;
	}
	/* Update sw flags for book keeping */
	vsi_props->sw_flags = ctxt->info.sw_flags;

out:
	devm_kfree(dev, ctxt);
	return ret;
}