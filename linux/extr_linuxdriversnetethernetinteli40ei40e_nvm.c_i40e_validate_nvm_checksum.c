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
typedef  scalar_t__ u16 ;
struct i40e_hw {int dummy; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 scalar_t__ I40E_ERR_NVM_CHECKSUM ; 
 int /*<<< orphan*/  I40E_RESOURCE_READ ; 
 int /*<<< orphan*/  I40E_SR_SW_CHECKSUM_WORD ; 
 int /*<<< orphan*/  __i40e_read_nvm_word (struct i40e_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ i40e_acquire_nvm (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_calc_nvm_checksum (struct i40e_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  i40e_release_nvm (struct i40e_hw*) ; 

i40e_status i40e_validate_nvm_checksum(struct i40e_hw *hw,
						 u16 *checksum)
{
	i40e_status ret_code = 0;
	u16 checksum_sr = 0;
	u16 checksum_local = 0;

	/* We must acquire the NVM lock in order to correctly synchronize the
	 * NVM accesses across multiple PFs. Without doing so it is possible
	 * for one of the PFs to read invalid data potentially indicating that
	 * the checksum is invalid.
	 */
	ret_code = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	if (ret_code)
		return ret_code;
	ret_code = i40e_calc_nvm_checksum(hw, &checksum_local);
	__i40e_read_nvm_word(hw, I40E_SR_SW_CHECKSUM_WORD, &checksum_sr);
	i40e_release_nvm(hw);
	if (ret_code)
		return ret_code;

	/* Verify read checksum from EEPROM is the same as
	 * calculated checksum
	 */
	if (checksum_local != checksum_sr)
		ret_code = I40E_ERR_NVM_CHECKSUM;

	/* If the user cares, return the calculated checksum */
	if (checksum)
		*checksum = checksum_local;

	return ret_code;
}