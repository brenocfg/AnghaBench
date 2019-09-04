#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * update; int /*<<< orphan*/ * validate; int /*<<< orphan*/ * write; int /*<<< orphan*/  read; int /*<<< orphan*/  valid_led_default; int /*<<< orphan*/  release; int /*<<< orphan*/  acquire; } ;
struct e1000_nvm_info {TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct e1000_hw {struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_nvm_flash_hw ; 
 int /*<<< orphan*/  e1000_nvm_invm ; 
 int /*<<< orphan*/  igb_acquire_nvm_i210 ; 
 scalar_t__ igb_get_flash_presence_i210 (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_read_invm_i210 ; 
 int /*<<< orphan*/  igb_read_nvm_srrd_i210 ; 
 int /*<<< orphan*/  igb_release_nvm_i210 ; 
 int /*<<< orphan*/ * igb_update_nvm_checksum_i210 ; 
 int /*<<< orphan*/  igb_valid_led_default_i210 ; 
 int /*<<< orphan*/ * igb_validate_nvm_checksum_i210 ; 
 int /*<<< orphan*/ * igb_write_nvm_srwr_i210 ; 

s32 igb_init_nvm_params_i210(struct e1000_hw *hw)
{
	s32 ret_val = 0;
	struct e1000_nvm_info *nvm = &hw->nvm;

	nvm->ops.acquire = igb_acquire_nvm_i210;
	nvm->ops.release = igb_release_nvm_i210;
	nvm->ops.valid_led_default = igb_valid_led_default_i210;

	/* NVM Function Pointers */
	if (igb_get_flash_presence_i210(hw)) {
		hw->nvm.type = e1000_nvm_flash_hw;
		nvm->ops.read    = igb_read_nvm_srrd_i210;
		nvm->ops.write   = igb_write_nvm_srwr_i210;
		nvm->ops.validate = igb_validate_nvm_checksum_i210;
		nvm->ops.update   = igb_update_nvm_checksum_i210;
	} else {
		hw->nvm.type = e1000_nvm_invm;
		nvm->ops.read     = igb_read_invm_i210;
		nvm->ops.write    = NULL;
		nvm->ops.validate = NULL;
		nvm->ops.update   = NULL;
	}
	return ret_val;
}