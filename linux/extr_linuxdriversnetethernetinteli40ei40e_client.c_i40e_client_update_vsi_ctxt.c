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
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  queueing_opt_flags; void* valid_sections; } ;
struct i40e_vsi_context {TYPE_1__ info; int /*<<< orphan*/  flags; int /*<<< orphan*/  pf_num; int /*<<< orphan*/  seid; } ;
struct i40e_vsi {TYPE_2__* back; } ;
struct TYPE_11__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_12__ {TYPE_4__ aq; int /*<<< orphan*/  pf_id; } ;
struct i40e_pf {size_t lan_vsi; TYPE_5__ hw; TYPE_3__* pdev; int /*<<< orphan*/  main_vsi_seid; struct i40e_vsi** vsi; } ;
struct i40e_info {struct i40e_pf* pf; } ;
struct i40e_client {int dummy; } ;
typedef  int i40e_status ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  I40E_AQ_VSI_PROP_QUEUE_OPT_VALID ; 
 int /*<<< orphan*/  I40E_AQ_VSI_QUE_OPT_TCP_ENA ; 
 int /*<<< orphan*/  I40E_AQ_VSI_TYPE_PF ; 
 int I40E_CLIENT_VSI_FLAG_TCP_ENABLE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int i40e_aq_get_vsi_params (TYPE_5__*,struct i40e_vsi_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int i40e_aq_update_vsi_params (int /*<<< orphan*/ *,struct i40e_vsi_context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_stat_str (TYPE_5__*,int) ; 

__attribute__((used)) static int i40e_client_update_vsi_ctxt(struct i40e_info *ldev,
				       struct i40e_client *client,
				       bool is_vf, u32 vf_id,
				       u32 flag, u32 valid_flag)
{
	struct i40e_pf *pf = ldev->pf;
	struct i40e_vsi *vsi = pf->vsi[pf->lan_vsi];
	struct i40e_vsi_context ctxt;
	bool update = true;
	i40e_status err;

	/* TODO: for now do not allow setting VF's VSI setting */
	if (is_vf)
		return -EINVAL;

	ctxt.seid = pf->main_vsi_seid;
	ctxt.pf_num = pf->hw.pf_id;
	err = i40e_aq_get_vsi_params(&pf->hw, &ctxt, NULL);
	ctxt.flags = I40E_AQ_VSI_TYPE_PF;
	if (err) {
		dev_info(&pf->pdev->dev,
			 "couldn't get PF vsi config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, err),
			 i40e_aq_str(&pf->hw,
				     pf->hw.aq.asq_last_status));
		return -ENOENT;
	}

	if ((valid_flag & I40E_CLIENT_VSI_FLAG_TCP_ENABLE) &&
	    (flag & I40E_CLIENT_VSI_FLAG_TCP_ENABLE)) {
		ctxt.info.valid_sections =
			cpu_to_le16(I40E_AQ_VSI_PROP_QUEUE_OPT_VALID);
		ctxt.info.queueing_opt_flags |= I40E_AQ_VSI_QUE_OPT_TCP_ENA;
	} else if ((valid_flag & I40E_CLIENT_VSI_FLAG_TCP_ENABLE) &&
		  !(flag & I40E_CLIENT_VSI_FLAG_TCP_ENABLE)) {
		ctxt.info.valid_sections =
			cpu_to_le16(I40E_AQ_VSI_PROP_QUEUE_OPT_VALID);
		ctxt.info.queueing_opt_flags &= ~I40E_AQ_VSI_QUE_OPT_TCP_ENA;
	} else {
		update = false;
		dev_warn(&pf->pdev->dev,
			 "Client for PF id %d request an unsupported Config: %x.\n",
			 pf->hw.pf_id, flag);
	}

	if (update) {
		err = i40e_aq_update_vsi_params(&vsi->back->hw, &ctxt, NULL);
		if (err) {
			dev_info(&pf->pdev->dev,
				 "update VSI ctxt for PE failed, err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, err),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
		}
	}
	return err;
}