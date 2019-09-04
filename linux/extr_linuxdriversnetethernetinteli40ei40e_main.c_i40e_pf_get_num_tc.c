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
typedef  int u8 ;
struct TYPE_8__ {scalar_t__ iscsi; } ;
struct i40e_dcbx_config {int dummy; } ;
struct i40e_hw {TYPE_4__ func_caps; struct i40e_dcbx_config local_dcbx_config; } ;
struct i40e_pf {int flags; size_t lan_vsi; struct i40e_hw hw; TYPE_3__** vsi; } ;
struct TYPE_5__ {int num_tc; } ;
struct TYPE_6__ {TYPE_1__ qopt; } ;
struct TYPE_7__ {TYPE_2__ mqprio_qopt; } ;

/* Variables and functions */
 int BIT (int) ; 
 int I40E_FLAG_DCB_ENABLED ; 
 int I40E_FLAG_MFP_ENABLED ; 
 int I40E_FLAG_TC_MQPRIO ; 
 int I40E_MAX_TRAFFIC_CLASS ; 
 int i40e_dcb_get_num_tc (struct i40e_dcbx_config*) ; 
 int i40e_get_iscsi_tc_map (struct i40e_pf*) ; 

__attribute__((used)) static u8 i40e_pf_get_num_tc(struct i40e_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	u8 i, enabled_tc = 1;
	u8 num_tc = 0;
	struct i40e_dcbx_config *dcbcfg = &hw->local_dcbx_config;

	if (pf->flags & I40E_FLAG_TC_MQPRIO)
		return pf->vsi[pf->lan_vsi]->mqprio_qopt.qopt.num_tc;

	/* If neither MQPRIO nor DCB is enabled, then always use single TC */
	if (!(pf->flags & I40E_FLAG_DCB_ENABLED))
		return 1;

	/* SFP mode will be enabled for all TCs on port */
	if (!(pf->flags & I40E_FLAG_MFP_ENABLED))
		return i40e_dcb_get_num_tc(dcbcfg);

	/* MFP mode return count of enabled TCs for this PF */
	if (pf->hw.func_caps.iscsi)
		enabled_tc =  i40e_get_iscsi_tc_map(pf);
	else
		return 1; /* Only TC0 */

	for (i = 0; i < I40E_MAX_TRAFFIC_CLASS; i++) {
		if (enabled_tc & BIT(i))
			num_tc++;
	}
	return num_tc;
}