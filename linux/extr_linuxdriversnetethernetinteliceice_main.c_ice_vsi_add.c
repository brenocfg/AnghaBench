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
struct TYPE_8__ {int /*<<< orphan*/  sw_id; int /*<<< orphan*/  sw_flags; } ;
struct ice_vsi_ctx {int /*<<< orphan*/  vsi_num; TYPE_4__ info; int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
struct ice_vsi {int type; int /*<<< orphan*/  vsi_num; TYPE_4__ info; struct ice_pf* back; TYPE_2__* port_info; TYPE_1__* vsw; } ;
struct ice_hw {int dummy; } ;
struct ice_pf {TYPE_3__* pdev; int /*<<< orphan*/  flags; struct ice_hw hw; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  sw_id; } ;
struct TYPE_5__ {scalar_t__ bridge_mode; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_MODE_VEB ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  ICE_AQ_VSI_SW_FLAG_ALLOW_LB ; 
 int /*<<< orphan*/  ICE_AQ_VSI_TYPE_PF ; 
 int /*<<< orphan*/  ICE_FLAG_RSS_ENA ; 
#define  ICE_VSI_PF 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int ice_aq_add_vsi (struct ice_hw*,struct ice_vsi_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_set_dflt_vsi_ctx (struct ice_vsi_ctx*) ; 
 int /*<<< orphan*/  ice_set_rss_vsi_ctx (struct ice_vsi_ctx*,struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_setup_q_map (struct ice_vsi*,struct ice_vsi_ctx*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_add(struct ice_vsi *vsi)
{
	struct ice_vsi_ctx ctxt = { 0 };
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;
	int ret = 0;

	switch (vsi->type) {
	case ICE_VSI_PF:
		ctxt.flags = ICE_AQ_VSI_TYPE_PF;
		break;
	default:
		return -ENODEV;
	}

	ice_set_dflt_vsi_ctx(&ctxt);
	/* if the switch is in VEB mode, allow VSI loopback */
	if (vsi->vsw->bridge_mode == BRIDGE_MODE_VEB)
		ctxt.info.sw_flags |= ICE_AQ_VSI_SW_FLAG_ALLOW_LB;

	/* Set LUT type and HASH type if RSS is enabled */
	if (test_bit(ICE_FLAG_RSS_ENA, pf->flags))
		ice_set_rss_vsi_ctx(&ctxt, vsi);

	ctxt.info.sw_id = vsi->port_info->sw_id;
	ice_vsi_setup_q_map(vsi, &ctxt);

	ret = ice_aq_add_vsi(hw, &ctxt, NULL);
	if (ret) {
		dev_err(&vsi->back->pdev->dev,
			"Add VSI AQ call failed, err %d\n", ret);
		return -EIO;
	}
	vsi->info = ctxt.info;
	vsi->vsi_num = ctxt.vsi_num;

	return ret;
}