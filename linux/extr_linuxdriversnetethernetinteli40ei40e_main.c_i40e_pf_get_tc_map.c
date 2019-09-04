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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ iscsi; } ;
struct TYPE_4__ {TYPE_1__ func_caps; int /*<<< orphan*/  local_dcbx_config; } ;
struct i40e_pf {int flags; TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_DEFAULT_TRAFFIC_CLASS ; 
 int I40E_FLAG_DCB_ENABLED ; 
 int I40E_FLAG_MFP_ENABLED ; 
 int I40E_FLAG_TC_MQPRIO ; 
 int /*<<< orphan*/  i40e_dcb_get_enabled_tc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_get_iscsi_tc_map (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_mqprio_get_enabled_tc (struct i40e_pf*) ; 

__attribute__((used)) static u8 i40e_pf_get_tc_map(struct i40e_pf *pf)
{
	if (pf->flags & I40E_FLAG_TC_MQPRIO)
		return i40e_mqprio_get_enabled_tc(pf);

	/* If neither MQPRIO nor DCB is enabled for this PF then just return
	 * default TC
	 */
	if (!(pf->flags & I40E_FLAG_DCB_ENABLED))
		return I40E_DEFAULT_TRAFFIC_CLASS;

	/* SFP mode we want PF to be enabled for all TCs */
	if (!(pf->flags & I40E_FLAG_MFP_ENABLED))
		return i40e_dcb_get_enabled_tc(&pf->hw.local_dcbx_config);

	/* MFP enabled and iSCSI PF type */
	if (pf->hw.func_caps.iscsi)
		return i40e_get_iscsi_tc_map(pf);
	else
		return I40E_DEFAULT_TRAFFIC_CLASS;
}