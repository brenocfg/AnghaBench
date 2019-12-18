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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_DEBUG_ALL ; 
 scalar_t__ I40E_ERR_BAD_PTR ; 
 scalar_t__ I40E_ERR_NVM ; 
 int I40E_NVM_INVALID_PTR_VAL ; 
 int I40E_NVM_INVALID_VAL ; 
 int I40E_PTR_TYPE ; 
 int /*<<< orphan*/  I40E_RESOURCE_READ ; 
 scalar_t__ i40e_acquire_nvm (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_read_nvm (struct i40e_hw*,int /*<<< orphan*/ ,int,int,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_debug (struct i40e_hw*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ i40e_read_nvm_buffer (struct i40e_hw*,int,int*,int*) ; 
 scalar_t__ i40e_read_nvm_word (struct i40e_hw*,scalar_t__,int*) ; 
 int /*<<< orphan*/  i40e_release_nvm (struct i40e_hw*) ; 

i40e_status i40e_read_nvm_module_data(struct i40e_hw *hw,
				      u8 module_ptr, u16 offset,
				      u16 words_data_size,
				      u16 *data_ptr)
{
	i40e_status status;
	u16 ptr_value = 0;
	u32 flat_offset;

	if (module_ptr != 0) {
		status = i40e_read_nvm_word(hw, module_ptr, &ptr_value);
		if (status) {
			i40e_debug(hw, I40E_DEBUG_ALL,
				   "Reading nvm word failed.Error code: %d.\n",
				   status);
			return I40E_ERR_NVM;
		}
	}
#define I40E_NVM_INVALID_PTR_VAL 0x7FFF
#define I40E_NVM_INVALID_VAL 0xFFFF

	/* Pointer not initialized */
	if (ptr_value == I40E_NVM_INVALID_PTR_VAL ||
	    ptr_value == I40E_NVM_INVALID_VAL)
		return I40E_ERR_BAD_PTR;

	/* Check whether the module is in SR mapped area or outside */
	if (ptr_value & I40E_PTR_TYPE) {
		/* Pointer points outside of the Shared RAM mapped area */
		ptr_value &= ~I40E_PTR_TYPE;

		/* PtrValue in 4kB units, need to convert to words */
		ptr_value /= 2;
		flat_offset = ((u32)ptr_value * 0x1000) + (u32)offset;
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
		if (!status) {
			status = i40e_aq_read_nvm(hw, 0, 2 * flat_offset,
						  2 * words_data_size,
						  data_ptr, true, NULL);
			i40e_release_nvm(hw);
			if (status) {
				i40e_debug(hw, I40E_DEBUG_ALL,
					   "Reading nvm aq failed.Error code: %d.\n",
					   status);
				return I40E_ERR_NVM;
			}
		} else {
			return I40E_ERR_NVM;
		}
	} else {
		/* Read from the Shadow RAM */
		status = i40e_read_nvm_buffer(hw, ptr_value + offset,
					      &words_data_size, data_ptr);
		if (status) {
			i40e_debug(hw, I40E_DEBUG_ALL,
				   "Reading nvm buffer failed.Error code: %d.\n",
				   status);
		}
	}

	return status;
}