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
typedef  int /*<<< orphan*/  u8 ;
struct i40e_vsi {TYPE_3__* back; } ;
struct TYPE_9__ {int /*<<< orphan*/ * qs_handle; } ;
struct i40e_channel {TYPE_4__ info; int /*<<< orphan*/  seid; int /*<<< orphan*/  enabled_tc; } ;
struct i40e_aqc_configure_vsi_tc_bw_data {int /*<<< orphan*/ * qs_handles; int /*<<< orphan*/ * tc_bw_credits; int /*<<< orphan*/  tc_valid_bits; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_7__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_10__ {TYPE_2__ aq; } ;
struct TYPE_8__ {TYPE_5__ hw; TYPE_1__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int I40E_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_config_vsi_tc_bw (TYPE_5__*,int /*<<< orphan*/ ,struct i40e_aqc_configure_vsi_tc_bw_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_channel_config_bw(struct i40e_vsi *vsi, struct i40e_channel *ch,
				  u8 *bw_share)
{
	struct i40e_aqc_configure_vsi_tc_bw_data bw_data;
	i40e_status ret;
	int i;

	bw_data.tc_valid_bits = ch->enabled_tc;
	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		bw_data.tc_bw_credits[i] = bw_share[i];

	ret = i40e_aq_config_vsi_tc_bw(&vsi->back->hw, ch->seid,
				       &bw_data, NULL);
	if (ret) {
		dev_info(&vsi->back->pdev->dev,
			 "Config VSI BW allocation per TC failed, aq_err: %d for new_vsi->seid %u\n",
			 vsi->back->hw.aq.asq_last_status, ch->seid);
		return -EINVAL;
	}

	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++)
		ch->info.qs_handle[i] = bw_data.qs_handles[i];

	return 0;
}