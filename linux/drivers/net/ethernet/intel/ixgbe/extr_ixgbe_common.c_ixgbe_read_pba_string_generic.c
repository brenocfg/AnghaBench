#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct ixgbe_hw*,int,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_INVALID_ARGUMENT ; 
 scalar_t__ IXGBE_ERR_NO_SPACE ; 
 scalar_t__ IXGBE_ERR_PBA_SECTION ; 
 int IXGBE_PBANUM0_PTR ; 
 int IXGBE_PBANUM1_PTR ; 
 int IXGBE_PBANUM_PTR_GUARD ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub4 (struct ixgbe_hw*,int,int*) ; 

s32 ixgbe_read_pba_string_generic(struct ixgbe_hw *hw, u8 *pba_num,
				  u32 pba_num_size)
{
	s32 ret_val;
	u16 data;
	u16 pba_ptr;
	u16 offset;
	u16 length;

	if (pba_num == NULL) {
		hw_dbg(hw, "PBA string buffer was null\n");
		return IXGBE_ERR_INVALID_ARGUMENT;
	}

	ret_val = hw->eeprom.ops.read(hw, IXGBE_PBANUM0_PTR, &data);
	if (ret_val) {
		hw_dbg(hw, "NVM Read Error\n");
		return ret_val;
	}

	ret_val = hw->eeprom.ops.read(hw, IXGBE_PBANUM1_PTR, &pba_ptr);
	if (ret_val) {
		hw_dbg(hw, "NVM Read Error\n");
		return ret_val;
	}

	/*
	 * if data is not ptr guard the PBA must be in legacy format which
	 * means pba_ptr is actually our second data word for the PBA number
	 * and we can decode it into an ascii string
	 */
	if (data != IXGBE_PBANUM_PTR_GUARD) {
		hw_dbg(hw, "NVM PBA number is not stored as string\n");

		/* we will need 11 characters to store the PBA */
		if (pba_num_size < 11) {
			hw_dbg(hw, "PBA string buffer too small\n");
			return IXGBE_ERR_NO_SPACE;
		}

		/* extract hex string from data and pba_ptr */
		pba_num[0] = (data >> 12) & 0xF;
		pba_num[1] = (data >> 8) & 0xF;
		pba_num[2] = (data >> 4) & 0xF;
		pba_num[3] = data & 0xF;
		pba_num[4] = (pba_ptr >> 12) & 0xF;
		pba_num[5] = (pba_ptr >> 8) & 0xF;
		pba_num[6] = '-';
		pba_num[7] = 0;
		pba_num[8] = (pba_ptr >> 4) & 0xF;
		pba_num[9] = pba_ptr & 0xF;

		/* put a null character on the end of our string */
		pba_num[10] = '\0';

		/* switch all the data but the '-' to hex char */
		for (offset = 0; offset < 10; offset++) {
			if (pba_num[offset] < 0xA)
				pba_num[offset] += '0';
			else if (pba_num[offset] < 0x10)
				pba_num[offset] += 'A' - 0xA;
		}

		return 0;
	}

	ret_val = hw->eeprom.ops.read(hw, pba_ptr, &length);
	if (ret_val) {
		hw_dbg(hw, "NVM Read Error\n");
		return ret_val;
	}

	if (length == 0xFFFF || length == 0) {
		hw_dbg(hw, "NVM PBA number section invalid length\n");
		return IXGBE_ERR_PBA_SECTION;
	}

	/* check if pba_num buffer is big enough */
	if (pba_num_size  < (((u32)length * 2) - 1)) {
		hw_dbg(hw, "PBA string buffer too small\n");
		return IXGBE_ERR_NO_SPACE;
	}

	/* trim pba length from start of string */
	pba_ptr++;
	length--;

	for (offset = 0; offset < length; offset++) {
		ret_val = hw->eeprom.ops.read(hw, pba_ptr + offset, &data);
		if (ret_val) {
			hw_dbg(hw, "NVM Read Error\n");
			return ret_val;
		}
		pba_num[offset * 2] = (u8)(data >> 8);
		pba_num[(offset * 2) + 1] = (u8)(data & 0xFF);
	}
	pba_num[offset * 2] = '\0';

	return 0;
}