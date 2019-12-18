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
struct i40e_hw {int dummy; } ;
typedef  scalar_t__ i40e_status ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_SR_SW_CHECKSUM_WORD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_calc_nvm_checksum (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_write_nvm_aq (struct i40e_hw*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

i40e_status i40e_update_nvm_checksum(struct i40e_hw *hw)
{
	i40e_status ret_code;
	u16 checksum;
	__le16 le_sum;

	ret_code = i40e_calc_nvm_checksum(hw, &checksum);
	le_sum = cpu_to_le16(checksum);
	if (!ret_code)
		ret_code = i40e_write_nvm_aq(hw, 0x00, I40E_SR_SW_CHECKSUM_WORD,
					     1, &le_sum, true);

	return ret_code;
}