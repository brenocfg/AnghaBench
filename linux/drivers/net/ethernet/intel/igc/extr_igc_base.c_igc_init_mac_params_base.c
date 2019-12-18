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
struct TYPE_3__ {int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  release_swfw_sync; int /*<<< orphan*/  acquire_swfw_sync; int /*<<< orphan*/  reset_hw; } ;
struct igc_mac_info {int mta_reg_count; scalar_t__ type; TYPE_1__ ops; int /*<<< orphan*/  rar_entry_count; } ;
struct igc_dev_spec_base {int clear_semaphore_once; } ;
struct TYPE_4__ {struct igc_dev_spec_base _base; } ;
struct igc_hw {struct igc_mac_info mac; TYPE_2__ dev_spec; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_RAR_ENTRIES ; 
 int /*<<< orphan*/  igc_acquire_swfw_sync_i225 ; 
 scalar_t__ igc_i225 ; 
 int /*<<< orphan*/  igc_release_swfw_sync_i225 ; 
 int /*<<< orphan*/  igc_reset_hw_base ; 
 int /*<<< orphan*/  igc_setup_copper_link_base ; 

__attribute__((used)) static s32 igc_init_mac_params_base(struct igc_hw *hw)
{
	struct igc_dev_spec_base *dev_spec = &hw->dev_spec._base;
	struct igc_mac_info *mac = &hw->mac;

	/* Set mta register count */
	mac->mta_reg_count = 128;
	mac->rar_entry_count = IGC_RAR_ENTRIES;

	/* reset */
	mac->ops.reset_hw = igc_reset_hw_base;

	mac->ops.acquire_swfw_sync = igc_acquire_swfw_sync_i225;
	mac->ops.release_swfw_sync = igc_release_swfw_sync_i225;

	/* Allow a single clear of the SW semaphore on I225 */
	if (mac->type == igc_i225)
		dev_spec->clear_semaphore_once = true;

	/* physical interface link setup */
	mac->ops.setup_physical_interface = igc_setup_copper_link_base;

	return 0;
}