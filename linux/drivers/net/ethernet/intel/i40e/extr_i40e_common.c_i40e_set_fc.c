#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct i40e_hw {int dummy; } ;
struct i40e_aq_get_phy_abilities_resp {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int I40E_SET_FC_AQ_FAIL_GET ; 
 int I40E_SET_FC_AQ_FAIL_SET ; 
 int I40E_SET_FC_AQ_FAIL_UPDATE ; 
 int i40e_aq_get_phy_capabilities (struct i40e_hw*,int,int,struct i40e_aq_get_phy_abilities_resp*,int /*<<< orphan*/ *) ; 
 int i40e_set_fc_status (struct i40e_hw*,struct i40e_aq_get_phy_abilities_resp*,int) ; 
 int i40e_update_link_info (struct i40e_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 

enum i40e_status_code i40e_set_fc(struct i40e_hw *hw, u8 *aq_failures,
				  bool atomic_restart)
{
	struct i40e_aq_get_phy_abilities_resp abilities;
	enum i40e_status_code status;

	*aq_failures = 0x0;

	/* Get the current phy config */
	status = i40e_aq_get_phy_capabilities(hw, false, false, &abilities,
					      NULL);
	if (status) {
		*aq_failures |= I40E_SET_FC_AQ_FAIL_GET;
		return status;
	}

	status = i40e_set_fc_status(hw, &abilities, atomic_restart);
	if (status)
		*aq_failures |= I40E_SET_FC_AQ_FAIL_SET;

	/* Update the link info */
	status = i40e_update_link_info(hw);
	if (status) {
		/* Wait a little bit (on 40G cards it sometimes takes a really
		 * long time for link to come back from the atomic reset)
		 * and try once more
		 */
		msleep(1000);
		status = i40e_update_link_info(hw);
	}
	if (status)
		*aq_failures |= I40E_SET_FC_AQ_FAIL_UPDATE;

	return status;
}