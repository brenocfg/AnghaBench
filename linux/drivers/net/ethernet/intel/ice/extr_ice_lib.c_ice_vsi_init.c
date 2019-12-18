#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  valid_sections; int /*<<< orphan*/  sec_flags; int /*<<< orphan*/  sw_id; int /*<<< orphan*/  sw_flags; } ;
struct ice_vsi_ctx {int /*<<< orphan*/  vsi_num; TYPE_5__ info; int /*<<< orphan*/  vf_num; int /*<<< orphan*/  flags; } ;
struct ice_vsi {int type; size_t vf_id; int /*<<< orphan*/  vsi_num; TYPE_5__ info; int /*<<< orphan*/  idx; TYPE_3__* port_info; TYPE_2__* vsw; struct ice_pf* back; } ;
struct TYPE_7__ {int /*<<< orphan*/  vf_base_id; } ;
struct ice_hw {TYPE_1__ func_caps; } ;
struct ice_pf {TYPE_6__* pdev; TYPE_4__* vf; int /*<<< orphan*/  flags; struct ice_hw hw; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {scalar_t__ spoofchk; } ;
struct TYPE_9__ {int /*<<< orphan*/  sw_id; } ;
struct TYPE_8__ {scalar_t__ bridge_mode; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_MODE_VEB ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_AQ_VSI_PROP_SECURITY_VALID ; 
 int /*<<< orphan*/  ICE_AQ_VSI_SEC_FLAG_ALLOW_DEST_OVRD ; 
 int /*<<< orphan*/  ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF ; 
 int /*<<< orphan*/  ICE_AQ_VSI_SW_FLAG_ALLOW_LB ; 
 int /*<<< orphan*/  ICE_AQ_VSI_TYPE_PF ; 
 int /*<<< orphan*/  ICE_AQ_VSI_TYPE_VF ; 
 int /*<<< orphan*/  ICE_FLAG_RSS_ENA ; 
#define  ICE_VSI_LB 130 
#define  ICE_VSI_PF 129 
#define  ICE_VSI_VF 128 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct ice_vsi_ctx*) ; 
 struct ice_vsi_ctx* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ice_add_vsi (struct ice_hw*,int /*<<< orphan*/ ,struct ice_vsi_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ice_set_dflt_vsi_ctx (struct ice_vsi_ctx*) ; 
 int /*<<< orphan*/  ice_set_rss_vsi_ctx (struct ice_vsi_ctx*,struct ice_vsi*) ; 
 int /*<<< orphan*/  ice_vsi_setup_q_map (struct ice_vsi*,struct ice_vsi_ctx*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_init(struct ice_vsi *vsi)
{
	struct ice_pf *pf = vsi->back;
	struct ice_hw *hw = &pf->hw;
	struct ice_vsi_ctx *ctxt;
	int ret = 0;

	ctxt = devm_kzalloc(&pf->pdev->dev, sizeof(*ctxt), GFP_KERNEL);
	if (!ctxt)
		return -ENOMEM;

	ctxt->info = vsi->info;
	switch (vsi->type) {
	case ICE_VSI_LB:
		/* fall through */
	case ICE_VSI_PF:
		ctxt->flags = ICE_AQ_VSI_TYPE_PF;
		break;
	case ICE_VSI_VF:
		ctxt->flags = ICE_AQ_VSI_TYPE_VF;
		/* VF number here is the absolute VF number (0-255) */
		ctxt->vf_num = vsi->vf_id + hw->func_caps.vf_base_id;
		break;
	default:
		return -ENODEV;
	}

	ice_set_dflt_vsi_ctx(ctxt);
	/* if the switch is in VEB mode, allow VSI loopback */
	if (vsi->vsw->bridge_mode == BRIDGE_MODE_VEB)
		ctxt->info.sw_flags |= ICE_AQ_VSI_SW_FLAG_ALLOW_LB;

	/* Set LUT type and HASH type if RSS is enabled */
	if (test_bit(ICE_FLAG_RSS_ENA, pf->flags))
		ice_set_rss_vsi_ctx(ctxt, vsi);

	ctxt->info.sw_id = vsi->port_info->sw_id;
	ice_vsi_setup_q_map(vsi, ctxt);

	/* Enable MAC Antispoof with new VSI being initialized or updated */
	if (vsi->type == ICE_VSI_VF && pf->vf[vsi->vf_id].spoofchk) {
		ctxt->info.valid_sections |=
			cpu_to_le16(ICE_AQ_VSI_PROP_SECURITY_VALID);
		ctxt->info.sec_flags |=
			ICE_AQ_VSI_SEC_FLAG_ENA_MAC_ANTI_SPOOF;
	}

	/* Allow control frames out of main VSI */
	if (vsi->type == ICE_VSI_PF) {
		ctxt->info.sec_flags |= ICE_AQ_VSI_SEC_FLAG_ALLOW_DEST_OVRD;
		ctxt->info.valid_sections |=
			cpu_to_le16(ICE_AQ_VSI_PROP_SECURITY_VALID);
	}

	ret = ice_add_vsi(hw, vsi->idx, ctxt, NULL);
	if (ret) {
		dev_err(&pf->pdev->dev,
			"Add VSI failed, err %d\n", ret);
		return -EIO;
	}

	/* keep context for update VSI operations */
	vsi->info = ctxt->info;

	/* record VSI number returned */
	vsi->vsi_num = ctxt->vsi_num;

	devm_kfree(&pf->pdev->dev, ctxt);
	return ret;
}