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
typedef  int u32 ;
struct i40e_lldp_variables {int dummy; } ;
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  mem ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_EMP_MODULE_PTR ; 
 scalar_t__ I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_NVM_LLDP_CFG_PTR ; 
 int /*<<< orphan*/  I40E_RESOURCE_READ ; 
 int /*<<< orphan*/  I40E_SR_EMP_MODULE_PTR ; 
 int /*<<< orphan*/  I40E_SR_LLDP_CFG_PTR ; 
 int /*<<< orphan*/  I40E_SR_NVM_CONTROL_WORD ; 
 int I40E_SR_NVM_MAP_STRUCTURE_TYPE ; 
 scalar_t__ _i40e_read_lldp_cfg (struct i40e_hw*,struct i40e_lldp_variables*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_acquire_nvm (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_read_nvm (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_release_nvm (struct i40e_hw*) ; 

i40e_status i40e_read_lldp_cfg(struct i40e_hw *hw,
			       struct i40e_lldp_variables *lldp_cfg)
{
	i40e_status ret = 0;
	u32 mem;

	if (!lldp_cfg)
		return I40E_ERR_PARAM;

	ret = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	if (ret)
		return ret;

	ret = i40e_aq_read_nvm(hw, I40E_SR_NVM_CONTROL_WORD, 0, sizeof(mem),
			       &mem, true, NULL);
	i40e_release_nvm(hw);
	if (ret)
		return ret;

	/* Read a bit that holds information whether we are running flat or
	 * structured NVM image. Flat image has LLDP configuration in shadow
	 * ram, so there is a need to pass different addresses for both cases.
	 */
	if (mem & I40E_SR_NVM_MAP_STRUCTURE_TYPE) {
		/* Flat NVM case */
		ret = _i40e_read_lldp_cfg(hw, lldp_cfg, I40E_SR_EMP_MODULE_PTR,
					  I40E_SR_LLDP_CFG_PTR);
	} else {
		/* Good old structured NVM image */
		ret = _i40e_read_lldp_cfg(hw, lldp_cfg, I40E_EMP_MODULE_PTR,
					  I40E_NVM_LLDP_CFG_PTR);
	}

	return ret;
}