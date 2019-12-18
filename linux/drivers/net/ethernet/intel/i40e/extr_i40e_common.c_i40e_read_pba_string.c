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
typedef  char u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct i40e_hw {int dummy; } ;
typedef  scalar_t__ i40e_status ;

/* Variables and functions */
 scalar_t__ I40E_ERR_PARAM ; 
 int I40E_SR_PBA_BLOCK_PTR ; 
 int I40E_SR_PBA_FLAGS ; 
 int /*<<< orphan*/  hw_dbg (struct i40e_hw*,char*,...) ; 
 scalar_t__ i40e_read_nvm_word (struct i40e_hw*,int,int*) ; 

i40e_status i40e_read_pba_string(struct i40e_hw *hw, u8 *pba_num,
				 u32 pba_num_size)
{
	i40e_status status = 0;
	u16 pba_word = 0;
	u16 pba_size = 0;
	u16 pba_ptr = 0;
	u16 i = 0;

	status = i40e_read_nvm_word(hw, I40E_SR_PBA_FLAGS, &pba_word);
	if (status || (pba_word != 0xFAFA)) {
		hw_dbg(hw, "Failed to read PBA flags or flag is invalid.\n");
		return status;
	}

	status = i40e_read_nvm_word(hw, I40E_SR_PBA_BLOCK_PTR, &pba_ptr);
	if (status) {
		hw_dbg(hw, "Failed to read PBA Block pointer.\n");
		return status;
	}

	status = i40e_read_nvm_word(hw, pba_ptr, &pba_size);
	if (status) {
		hw_dbg(hw, "Failed to read PBA Block size.\n");
		return status;
	}

	/* Subtract one to get PBA word count (PBA Size word is included in
	 * total size)
	 */
	pba_size--;
	if (pba_num_size < (((u32)pba_size * 2) + 1)) {
		hw_dbg(hw, "Buffer to small for PBA data.\n");
		return I40E_ERR_PARAM;
	}

	for (i = 0; i < pba_size; i++) {
		status = i40e_read_nvm_word(hw, (pba_ptr + 1) + i, &pba_word);
		if (status) {
			hw_dbg(hw, "Failed to read PBA Block word %d.\n", i);
			return status;
		}

		pba_num[(i * 2)] = (pba_word >> 8) & 0xFF;
		pba_num[(i * 2) + 1] = pba_word & 0xFF;
	}
	pba_num[(pba_size * 2)] = '\0';

	return status;
}