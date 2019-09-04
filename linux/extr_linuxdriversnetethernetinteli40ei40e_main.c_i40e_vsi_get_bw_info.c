#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct i40e_vsi {int bw_limit; int* bw_ets_limit_credits; scalar_t__* bw_ets_max_quanta; int /*<<< orphan*/ * bw_ets_share_credits; int /*<<< orphan*/  bw_max_quanta; int /*<<< orphan*/  seid; struct i40e_pf* back; } ;
struct TYPE_3__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_1__ aq; } ;
struct i40e_pf {TYPE_2__* pdev; struct i40e_hw hw; } ;
struct i40e_aqc_query_vsi_ets_sla_config_resp {scalar_t__ tc_valid_bits; int /*<<< orphan*/ * credits; int /*<<< orphan*/ * share_credits; int /*<<< orphan*/ * tc_bw_max; int /*<<< orphan*/  member_0; } ;
struct i40e_aqc_query_vsi_bw_config_resp {scalar_t__ tc_valid_bits; int /*<<< orphan*/  max_bw; int /*<<< orphan*/  port_bw_limit; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int I40E_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ i40e_aq_query_vsi_bw_config (struct i40e_hw*,int /*<<< orphan*/ ,struct i40e_aqc_query_vsi_bw_config_resp*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_aq_query_vsi_ets_sla_config (struct i40e_hw*,int /*<<< orphan*/ ,struct i40e_aqc_query_vsi_ets_sla_config_resp*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_stat_str (struct i40e_hw*,scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_vsi_get_bw_info(struct i40e_vsi *vsi)
{
	struct i40e_aqc_query_vsi_ets_sla_config_resp bw_ets_config = {0};
	struct i40e_aqc_query_vsi_bw_config_resp bw_config = {0};
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	i40e_status ret;
	u32 tc_bw_max;
	int i;

	/* Get the VSI level BW configuration */
	ret = i40e_aq_query_vsi_bw_config(hw, vsi->seid, &bw_config, NULL);
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "couldn't get PF vsi bw config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		return -EINVAL;
	}

	/* Get the VSI level BW configuration per TC */
	ret = i40e_aq_query_vsi_ets_sla_config(hw, vsi->seid, &bw_ets_config,
					       NULL);
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "couldn't get PF vsi ets bw config, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, pf->hw.aq.asq_last_status));
		return -EINVAL;
	}

	if (bw_config.tc_valid_bits != bw_ets_config.tc_valid_bits) {
		dev_info(&pf->pdev->dev,
			 "Enabled TCs mismatch from querying VSI BW info 0x%08x 0x%08x\n",
			 bw_config.tc_valid_bits,
			 bw_ets_config.tc_valid_bits);
		/* Still continuing */
	}

	vsi->bw_limit = le16_to_cpu(bw_config.port_bw_limit);
	vsi->bw_max_quanta = bw_config.max_bw;
	tc_bw_max = le16_to_cpu(bw_ets_config.tc_bw_max[0]) |
		    (le16_to_cpu(bw_ets_config.tc_bw_max[1]) << 16);
	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) {
		vsi->bw_ets_share_credits[i] = bw_ets_config.share_credits[i];
		vsi->bw_ets_limit_credits[i] =
					le16_to_cpu(bw_ets_config.credits[i]);
		/* 3 bits out of 4 for each TC */
		vsi->bw_ets_max_quanta[i] = (u8)((tc_bw_max >> (i*4)) & 0x7);
	}

	return 0;
}