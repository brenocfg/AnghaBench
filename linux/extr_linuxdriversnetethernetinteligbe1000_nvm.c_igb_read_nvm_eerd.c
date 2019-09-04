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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct e1000_nvm_info {scalar_t__ word_size; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EERD ; 
 int E1000_ERR_NVM ; 
 int /*<<< orphan*/  E1000_NVM_POLL_READ ; 
 scalar_t__ E1000_NVM_RW_ADDR_SHIFT ; 
 scalar_t__ E1000_NVM_RW_REG_DATA ; 
 scalar_t__ E1000_NVM_RW_REG_START ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 int igb_poll_eerd_eewr_done (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,scalar_t__) ; 

s32 igb_read_nvm_eerd(struct e1000_hw *hw, u16 offset, u16 words, u16 *data)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 i, eerd = 0;
	s32 ret_val = 0;

	/* A check for invalid values:  offset too large, too many words,
	 * and not enough words.
	 */
	if ((offset >= nvm->word_size) || (words > (nvm->word_size - offset)) ||
	    (words == 0)) {
		hw_dbg("nvm parameter(s) out of bounds\n");
		ret_val = -E1000_ERR_NVM;
		goto out;
	}

	for (i = 0; i < words; i++) {
		eerd = ((offset+i) << E1000_NVM_RW_ADDR_SHIFT) +
			E1000_NVM_RW_REG_START;

		wr32(E1000_EERD, eerd);
		ret_val = igb_poll_eerd_eewr_done(hw, E1000_NVM_POLL_READ);
		if (ret_val)
			break;

		data[i] = (rd32(E1000_EERD) >>
			E1000_NVM_RW_REG_DATA);
	}

out:
	return ret_val;
}