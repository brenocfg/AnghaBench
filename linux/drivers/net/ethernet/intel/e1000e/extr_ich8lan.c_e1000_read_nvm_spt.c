#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;int /*<<< orphan*/  (* acquire ) (struct e1000_hw*) ;} ;
struct e1000_nvm_info {scalar_t__ word_size; scalar_t__ flash_bank_size; TYPE_3__ ops; } ;
struct e1000_dev_spec_ich8lan {TYPE_2__* shadow_ram; } ;
struct TYPE_4__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_1__ dev_spec; struct e1000_nvm_info nvm; } ;
typedef  int s32 ;
struct TYPE_5__ {scalar_t__ value; scalar_t__ modified; } ;

/* Variables and functions */
 int E1000_ERR_NVM ; 
 int e1000_read_flash_dword_ich8lan (struct e1000_hw*,scalar_t__,scalar_t__*) ; 
 int e1000_valid_nvm_bank_detect_ich8lan (struct e1000_hw*,scalar_t__*) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

__attribute__((used)) static s32 e1000_read_nvm_spt(struct e1000_hw *hw, u16 offset, u16 words,
			      u16 *data)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	u32 act_offset;
	s32 ret_val = 0;
	u32 bank = 0;
	u32 dword = 0;
	u16 offset_to_read;
	u16 i;

	if ((offset >= nvm->word_size) || (words > nvm->word_size - offset) ||
	    (words == 0)) {
		e_dbg("nvm parameter(s) out of bounds\n");
		ret_val = -E1000_ERR_NVM;
		goto out;
	}

	nvm->ops.acquire(hw);

	ret_val = e1000_valid_nvm_bank_detect_ich8lan(hw, &bank);
	if (ret_val) {
		e_dbg("Could not detect valid bank, assuming bank 0\n");
		bank = 0;
	}

	act_offset = (bank) ? nvm->flash_bank_size : 0;
	act_offset += offset;

	ret_val = 0;

	for (i = 0; i < words; i += 2) {
		if (words - i == 1) {
			if (dev_spec->shadow_ram[offset + i].modified) {
				data[i] =
				    dev_spec->shadow_ram[offset + i].value;
			} else {
				offset_to_read = act_offset + i -
				    ((act_offset + i) % 2);
				ret_val =
				  e1000_read_flash_dword_ich8lan(hw,
								 offset_to_read,
								 &dword);
				if (ret_val)
					break;
				if ((act_offset + i) % 2 == 0)
					data[i] = (u16)(dword & 0xFFFF);
				else
					data[i] = (u16)((dword >> 16) & 0xFFFF);
			}
		} else {
			offset_to_read = act_offset + i;
			if (!(dev_spec->shadow_ram[offset + i].modified) ||
			    !(dev_spec->shadow_ram[offset + i + 1].modified)) {
				ret_val =
				  e1000_read_flash_dword_ich8lan(hw,
								 offset_to_read,
								 &dword);
				if (ret_val)
					break;
			}
			if (dev_spec->shadow_ram[offset + i].modified)
				data[i] =
				    dev_spec->shadow_ram[offset + i].value;
			else
				data[i] = (u16)(dword & 0xFFFF);
			if (dev_spec->shadow_ram[offset + i].modified)
				data[i + 1] =
				    dev_spec->shadow_ram[offset + i + 1].value;
			else
				data[i + 1] = (u16)(dword >> 16 & 0xFFFF);
		}
	}

	nvm->ops.release(hw);

out:
	if (ret_val)
		e_dbg("NVM read error: %d\n", ret_val);

	return ret_val;
}