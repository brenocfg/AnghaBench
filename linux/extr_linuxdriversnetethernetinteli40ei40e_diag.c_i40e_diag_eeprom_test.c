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
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  i40e_status ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_ERR_DIAG_TEST_FAILED ; 
 int I40E_SR_CONTROL_WORD_1_MASK ; 
 int /*<<< orphan*/  I40E_SR_CONTROL_WORD_1_SHIFT ; 
 int /*<<< orphan*/  I40E_SR_NVM_CONTROL_WORD ; 
 int /*<<< orphan*/  i40e_read_nvm_word (struct i40e_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  i40e_validate_nvm_checksum (struct i40e_hw*,int /*<<< orphan*/ *) ; 

i40e_status i40e_diag_eeprom_test(struct i40e_hw *hw)
{
	i40e_status ret_code;
	u16 reg_val;

	/* read NVM control word and if NVM valid, validate EEPROM checksum*/
	ret_code = i40e_read_nvm_word(hw, I40E_SR_NVM_CONTROL_WORD, &reg_val);
	if (!ret_code &&
	    ((reg_val & I40E_SR_CONTROL_WORD_1_MASK) ==
	     BIT(I40E_SR_CONTROL_WORD_1_SHIFT)))
		return i40e_validate_nvm_checksum(hw, NULL);
	else
		return I40E_ERR_DIAG_TEST_FAILED;
}