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
struct TYPE_4__ {int /*<<< orphan*/  setup_physical_interface; int /*<<< orphan*/  write_vfta; int /*<<< orphan*/  release_swfw_sync; int /*<<< orphan*/  acquire_swfw_sync; int /*<<< orphan*/  reset_hw; } ;
struct e1000_mac_info {int mta_reg_count; int uta_reg_count; scalar_t__ type; int asf_firmware_present; int arc_subsystem_valid; TYPE_1__ ops; int /*<<< orphan*/  rar_entry_count; } ;
struct e1000_dev_spec_82575 {int eee_disable; int clear_semaphore_once; int mas_capable; } ;
struct TYPE_6__ {struct e1000_dev_spec_82575 _82575; } ;
struct TYPE_5__ {scalar_t__ media_type; } ;
struct e1000_hw {int device_id; TYPE_3__ dev_spec; TYPE_2__ phy; struct e1000_mac_info mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  E1000_DEV_ID_DH89XXCC_BACKPLANE 135 
#define  E1000_DEV_ID_DH89XXCC_SERDES 134 
#define  E1000_DEV_ID_DH89XXCC_SFP 133 
#define  E1000_DEV_ID_DH89XXCC_SGMII 132 
 int /*<<< orphan*/  E1000_FWSM ; 
 int E1000_FWSM_MODE_MASK ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES_82575 ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES_82576 ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES_82580 ; 
 int /*<<< orphan*/  E1000_RAR_ENTRIES_I350 ; 
 scalar_t__ e1000_82575 ; 
#define  e1000_82576 131 
#define  e1000_82580 130 
 int const e1000_i210 ; 
#define  e1000_i350 129 
#define  e1000_i354 128 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  igb_acquire_swfw_sync_82575 ; 
 int /*<<< orphan*/  igb_acquire_swfw_sync_i210 ; 
 int /*<<< orphan*/  igb_release_swfw_sync_82575 ; 
 int /*<<< orphan*/  igb_release_swfw_sync_i210 ; 
 int /*<<< orphan*/  igb_reset_hw_82575 ; 
 int /*<<< orphan*/  igb_reset_hw_82580 ; 
 int /*<<< orphan*/  igb_setup_copper_link_82575 ; 
 int /*<<< orphan*/  igb_setup_serdes_link_82575 ; 
 int /*<<< orphan*/  igb_write_vfta ; 
 int /*<<< orphan*/  igb_write_vfta_i350 ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 igb_init_mac_params_82575(struct e1000_hw *hw)
{
	struct e1000_mac_info *mac = &hw->mac;
	struct e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;

	/* Set mta register count */
	mac->mta_reg_count = 128;
	/* Set uta register count */
	mac->uta_reg_count = (hw->mac.type == e1000_82575) ? 0 : 128;
	/* Set rar entry count */
	switch (mac->type) {
	case e1000_82576:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82576;
		break;
	case e1000_82580:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82580;
		break;
	case e1000_i350:
	case e1000_i354:
		mac->rar_entry_count = E1000_RAR_ENTRIES_I350;
		break;
	default:
		mac->rar_entry_count = E1000_RAR_ENTRIES_82575;
		break;
	}
	/* reset */
	if (mac->type >= e1000_82580)
		mac->ops.reset_hw = igb_reset_hw_82580;
	else
		mac->ops.reset_hw = igb_reset_hw_82575;

	if (mac->type >= e1000_i210) {
		mac->ops.acquire_swfw_sync = igb_acquire_swfw_sync_i210;
		mac->ops.release_swfw_sync = igb_release_swfw_sync_i210;

	} else {
		mac->ops.acquire_swfw_sync = igb_acquire_swfw_sync_82575;
		mac->ops.release_swfw_sync = igb_release_swfw_sync_82575;
	}

	if ((hw->mac.type == e1000_i350) || (hw->mac.type == e1000_i354))
		mac->ops.write_vfta = igb_write_vfta_i350;
	else
		mac->ops.write_vfta = igb_write_vfta;

	/* Set if part includes ASF firmware */
	mac->asf_firmware_present = true;
	/* Set if manageability features are enabled. */
	mac->arc_subsystem_valid =
		(rd32(E1000_FWSM) & E1000_FWSM_MODE_MASK)
			? true : false;
	/* enable EEE on i350 parts and later parts */
	if (mac->type >= e1000_i350)
		dev_spec->eee_disable = false;
	else
		dev_spec->eee_disable = true;
	/* Allow a single clear of the SW semaphore on I210 and newer */
	if (mac->type >= e1000_i210)
		dev_spec->clear_semaphore_once = true;
	/* physical interface link setup */
	mac->ops.setup_physical_interface =
		(hw->phy.media_type == e1000_media_type_copper)
			? igb_setup_copper_link_82575
			: igb_setup_serdes_link_82575;

	if (mac->type == e1000_82580 || mac->type == e1000_i350) {
		switch (hw->device_id) {
		/* feature not supported on these id's */
		case E1000_DEV_ID_DH89XXCC_SGMII:
		case E1000_DEV_ID_DH89XXCC_SERDES:
		case E1000_DEV_ID_DH89XXCC_BACKPLANE:
		case E1000_DEV_ID_DH89XXCC_SFP:
			break;
		default:
			hw->dev_spec._82575.mas_capable = true;
			break;
		}
	}
	return 0;
}