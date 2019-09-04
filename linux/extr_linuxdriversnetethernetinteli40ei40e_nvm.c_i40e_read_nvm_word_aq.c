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
typedef  int /*<<< orphan*/  i40e_status ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_TIMEOUT ; 
 int /*<<< orphan*/  i40e_read_nvm_aq (struct i40e_hw*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static i40e_status i40e_read_nvm_word_aq(struct i40e_hw *hw, u16 offset,
					 u16 *data)
{
	i40e_status ret_code = I40E_ERR_TIMEOUT;

	ret_code = i40e_read_nvm_aq(hw, 0x0, offset, 1, data, true);
	*data = le16_to_cpu(*(__le16 *)data);

	return ret_code;
}