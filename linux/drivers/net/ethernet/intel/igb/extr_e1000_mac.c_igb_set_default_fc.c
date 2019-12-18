#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_9__ {int /*<<< orphan*/  requested_mode; } ;
struct TYPE_7__ {scalar_t__ (* read ) (struct e1000_hw*,int,int,int*) ;} ;
struct TYPE_8__ {TYPE_2__ ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  func; } ;
struct TYPE_10__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_4__ fc; TYPE_3__ nvm; TYPE_1__ bus; TYPE_5__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int NVM_82580_LAN_FUNC_OFFSET (int /*<<< orphan*/ ) ; 
 int NVM_INIT_CONTROL2_REG ; 
 int NVM_WORD0F_ASM_DIR ; 
 int NVM_WORD0F_PAUSE_MASK ; 
 int /*<<< orphan*/  e1000_fc_full ; 
 int /*<<< orphan*/  e1000_fc_none ; 
 int /*<<< orphan*/  e1000_fc_tx_pause ; 
 scalar_t__ e1000_i350 ; 
 int /*<<< orphan*/  hw_dbg (char*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int,int,int*) ; 

__attribute__((used)) static s32 igb_set_default_fc(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	u16 lan_offset;
	u16 nvm_data;

	/* Read and store word 0x0F of the EEPROM. This word contains bits
	 * that determine the hardware's default PAUSE (flow control) mode,
	 * a bit that determines whether the HW defaults to enabling or
	 * disabling auto-negotiation, and the direction of the
	 * SW defined pins. If there is no SW over-ride of the flow
	 * control setting, then the variable hw->fc will
	 * be initialized based on a value in the EEPROM.
	 */
	if (hw->mac.type == e1000_i350)
		lan_offset = NVM_82580_LAN_FUNC_OFFSET(hw->bus.func);
	else
		lan_offset = 0;

	ret_val = hw->nvm.ops.read(hw, NVM_INIT_CONTROL2_REG + lan_offset,
				   1, &nvm_data);
	if (ret_val) {
		hw_dbg("NVM Read Error\n");
		goto out;
	}

	if ((nvm_data & NVM_WORD0F_PAUSE_MASK) == 0)
		hw->fc.requested_mode = e1000_fc_none;
	else if ((nvm_data & NVM_WORD0F_PAUSE_MASK) == NVM_WORD0F_ASM_DIR)
		hw->fc.requested_mode = e1000_fc_tx_pause;
	else
		hw->fc.requested_mode = e1000_fc_full;

out:
	return ret_val;
}