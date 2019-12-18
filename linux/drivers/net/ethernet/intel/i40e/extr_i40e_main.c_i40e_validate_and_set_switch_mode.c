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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_6__ {scalar_t__ asq_last_status; } ;
struct TYPE_4__ {int switch_mode; } ;
struct i40e_hw {TYPE_3__ aq; TYPE_1__ dev_caps; } ;
struct i40e_pf {TYPE_2__* pdev; int /*<<< orphan*/  last_sw_conf_valid_flags; int /*<<< orphan*/  last_sw_conf_flags; struct i40e_hw hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ I40E_AQ_RC_ESRCH ; 
 int /*<<< orphan*/  I40E_AQ_SET_SWITCH_BIT7_VALID ; 
 int /*<<< orphan*/  I40E_AQ_SET_SWITCH_L4_TYPE_TCP ; 
 int /*<<< orphan*/  I40E_AQ_SET_SWITCH_MODE_NON_TUNNEL ; 
 scalar_t__ I40E_CLOUD_FILTER_MODE1 ; 
 scalar_t__ I40E_CLOUD_FILTER_MODE2 ; 
 scalar_t__ I40E_SWITCH_MODE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int i40e_aq_set_switch_config (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,scalar_t__) ; 
 int /*<<< orphan*/  i40e_aqc_opc_list_dev_capabilities ; 
 int i40e_get_capabilities (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 

__attribute__((used)) static int i40e_validate_and_set_switch_mode(struct i40e_vsi *vsi)
{
	u8 mode;
	struct i40e_pf *pf = vsi->back;
	struct i40e_hw *hw = &pf->hw;
	int ret;

	ret = i40e_get_capabilities(pf, i40e_aqc_opc_list_dev_capabilities);
	if (ret)
		return -EINVAL;

	if (hw->dev_caps.switch_mode) {
		/* if switch mode is set, support mode2 (non-tunneled for
		 * cloud filter) for now
		 */
		u32 switch_mode = hw->dev_caps.switch_mode &
				  I40E_SWITCH_MODE_MASK;
		if (switch_mode >= I40E_CLOUD_FILTER_MODE1) {
			if (switch_mode == I40E_CLOUD_FILTER_MODE2)
				return 0;
			dev_err(&pf->pdev->dev,
				"Invalid switch_mode (%d), only non-tunneled mode for cloud filter is supported\n",
				hw->dev_caps.switch_mode);
			return -EINVAL;
		}
	}

	/* Set Bit 7 to be valid */
	mode = I40E_AQ_SET_SWITCH_BIT7_VALID;

	/* Set L4type for TCP support */
	mode |= I40E_AQ_SET_SWITCH_L4_TYPE_TCP;

	/* Set cloud filter mode */
	mode |= I40E_AQ_SET_SWITCH_MODE_NON_TUNNEL;

	/* Prep mode field for set_switch_config */
	ret = i40e_aq_set_switch_config(hw, pf->last_sw_conf_flags,
					pf->last_sw_conf_valid_flags,
					mode, NULL);
	if (ret && hw->aq.asq_last_status != I40E_AQ_RC_ESRCH)
		dev_err(&pf->pdev->dev,
			"couldn't set switch config bits, err %s aq_err %s\n",
			i40e_stat_str(hw, ret),
			i40e_aq_str(hw,
				    hw->aq.asq_last_status));

	return ret;
}