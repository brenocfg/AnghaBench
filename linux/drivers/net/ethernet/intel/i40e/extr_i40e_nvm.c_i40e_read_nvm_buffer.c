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
typedef  int /*<<< orphan*/  u16 ;
struct i40e_hw {int flags; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 int I40E_HW_FLAG_AQ_SRCTL_ACCESS_ENABLE ; 
 int /*<<< orphan*/  I40E_RESOURCE_READ ; 
 scalar_t__ i40e_acquire_nvm (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_read_nvm_buffer_aq (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_read_nvm_buffer_srctl (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_release_nvm (struct i40e_hw*) ; 

i40e_status i40e_read_nvm_buffer(struct i40e_hw *hw, u16 offset,
				 u16 *words, u16 *data)
{
	i40e_status ret_code = 0;

	if (hw->flags & I40E_HW_FLAG_AQ_SRCTL_ACCESS_ENABLE) {
		ret_code = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
		if (!ret_code) {
			ret_code = i40e_read_nvm_buffer_aq(hw, offset, words,
							   data);
			i40e_release_nvm(hw);
		}
	} else {
		ret_code = i40e_read_nvm_buffer_srctl(hw, offset, words, data);
	}

	return ret_code;
}