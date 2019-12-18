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
struct TYPE_2__ {int /*<<< orphan*/ * update; int /*<<< orphan*/ * validate; int /*<<< orphan*/ * write; int /*<<< orphan*/  read; int /*<<< orphan*/  release; int /*<<< orphan*/  acquire; } ;
struct igc_nvm_info {TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct igc_hw {struct igc_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  igc_acquire_nvm_i225 ; 
 scalar_t__ igc_get_flash_presence_i225 (struct igc_hw*) ; 
 int /*<<< orphan*/  igc_nvm_flash_hw ; 
 int /*<<< orphan*/  igc_nvm_invm ; 
 int /*<<< orphan*/  igc_read_nvm_eerd ; 
 int /*<<< orphan*/  igc_read_nvm_srrd_i225 ; 
 int /*<<< orphan*/  igc_release_nvm_i225 ; 
 int /*<<< orphan*/ * igc_update_nvm_checksum_i225 ; 
 int /*<<< orphan*/ * igc_validate_nvm_checksum_i225 ; 
 int /*<<< orphan*/ * igc_write_nvm_srwr_i225 ; 

s32 igc_init_nvm_params_i225(struct igc_hw *hw)
{
	struct igc_nvm_info *nvm = &hw->nvm;

	nvm->ops.acquire = igc_acquire_nvm_i225;
	nvm->ops.release = igc_release_nvm_i225;

	/* NVM Function Pointers */
	if (igc_get_flash_presence_i225(hw)) {
		hw->nvm.type = igc_nvm_flash_hw;
		nvm->ops.read = igc_read_nvm_srrd_i225;
		nvm->ops.write = igc_write_nvm_srwr_i225;
		nvm->ops.validate = igc_validate_nvm_checksum_i225;
		nvm->ops.update = igc_update_nvm_checksum_i225;
	} else {
		hw->nvm.type = igc_nvm_invm;
		nvm->ops.read = igc_read_nvm_eerd;
		nvm->ops.write = NULL;
		nvm->ops.validate = NULL;
		nvm->ops.update = NULL;
	}
	return 0;
}