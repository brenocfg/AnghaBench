#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flcdone; scalar_t__ flcerr; } ;
union ich8_hws_flash_status {TYPE_4__ hsf_status; void* regval; } ;
struct TYPE_6__ {int fldbcount; int /*<<< orphan*/  flcycle; } ;
union ich8_hws_flash_ctrl {int regval; TYPE_2__ hsf_ctrl; } ;
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_7__ {scalar_t__ type; } ;
struct TYPE_5__ {int flash_base_addr; } ;
struct e1000_hw {TYPE_3__ mac; TYPE_1__ nvm; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_NVM ; 
 int /*<<< orphan*/  ICH_CYCLE_WRITE ; 
 scalar_t__ ICH_FLASH_CYCLE_REPEAT_COUNT ; 
 int /*<<< orphan*/  ICH_FLASH_FADDR ; 
 int /*<<< orphan*/  ICH_FLASH_FDATA0 ; 
 int /*<<< orphan*/  ICH_FLASH_HSFCTL ; 
 int /*<<< orphan*/  ICH_FLASH_HSFSTS ; 
 int ICH_FLASH_LINEAR_ADDR_MASK ; 
 int /*<<< orphan*/  ICH_FLASH_WRITE_COMMAND_TIMEOUT ; 
 scalar_t__ e1000_flash_cycle_ich8lan (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ e1000_flash_cycle_init_ich8lan (struct e1000_hw*) ; 
 scalar_t__ e1000_pch_spt ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 void* er16flash (int /*<<< orphan*/ ) ; 
 int er32flash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew16flash (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ew32flash (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 e1000_write_flash_data_ich8lan(struct e1000_hw *hw, u32 offset,
					  u8 size, u16 data)
{
	union ich8_hws_flash_status hsfsts;
	union ich8_hws_flash_ctrl hsflctl;
	u32 flash_linear_addr;
	u32 flash_data = 0;
	s32 ret_val;
	u8 count = 0;

	if (hw->mac.type >= e1000_pch_spt) {
		if (size != 4 || offset > ICH_FLASH_LINEAR_ADDR_MASK)
			return -E1000_ERR_NVM;
	} else {
		if (size < 1 || size > 2 || offset > ICH_FLASH_LINEAR_ADDR_MASK)
			return -E1000_ERR_NVM;
	}

	flash_linear_addr = ((ICH_FLASH_LINEAR_ADDR_MASK & offset) +
			     hw->nvm.flash_base_addr);

	do {
		udelay(1);
		/* Steps */
		ret_val = e1000_flash_cycle_init_ich8lan(hw);
		if (ret_val)
			break;
		/* In SPT, This register is in Lan memory space, not
		 * flash.  Therefore, only 32 bit access is supported
		 */
		if (hw->mac.type >= e1000_pch_spt)
			hsflctl.regval = er32flash(ICH_FLASH_HSFSTS) >> 16;
		else
			hsflctl.regval = er16flash(ICH_FLASH_HSFCTL);

		/* 0b/1b corresponds to 1 or 2 byte size, respectively. */
		hsflctl.hsf_ctrl.fldbcount = size - 1;
		hsflctl.hsf_ctrl.flcycle = ICH_CYCLE_WRITE;
		/* In SPT, This register is in Lan memory space,
		 * not flash.  Therefore, only 32 bit access is
		 * supported
		 */
		if (hw->mac.type >= e1000_pch_spt)
			ew32flash(ICH_FLASH_HSFSTS, hsflctl.regval << 16);
		else
			ew16flash(ICH_FLASH_HSFCTL, hsflctl.regval);

		ew32flash(ICH_FLASH_FADDR, flash_linear_addr);

		if (size == 1)
			flash_data = (u32)data & 0x00FF;
		else
			flash_data = (u32)data;

		ew32flash(ICH_FLASH_FDATA0, flash_data);

		/* check if FCERR is set to 1 , if set to 1, clear it
		 * and try the whole sequence a few more times else done
		 */
		ret_val =
		    e1000_flash_cycle_ich8lan(hw,
					      ICH_FLASH_WRITE_COMMAND_TIMEOUT);
		if (!ret_val)
			break;

		/* If we're here, then things are most likely
		 * completely hosed, but if the error condition
		 * is detected, it won't hurt to give it another
		 * try...ICH_FLASH_CYCLE_REPEAT_COUNT times.
		 */
		hsfsts.regval = er16flash(ICH_FLASH_HSFSTS);
		if (hsfsts.hsf_status.flcerr)
			/* Repeat for some time before giving up. */
			continue;
		if (!hsfsts.hsf_status.flcdone) {
			e_dbg("Timeout error - flash cycle did not complete.\n");
			break;
		}
	} while (count++ < ICH_FLASH_CYCLE_REPEAT_COUNT);

	return ret_val;
}