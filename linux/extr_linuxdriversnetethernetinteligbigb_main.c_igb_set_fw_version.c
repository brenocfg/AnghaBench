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
struct TYPE_2__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igb_adapter {int /*<<< orphan*/  fw_version; struct e1000_hw hw; } ;
struct e1000_fw_version {int invm_major; int invm_minor; int invm_img_type; int eep_major; int eep_minor; int etrack_id; int or_major; int or_build; int or_patch; int eep_build; int /*<<< orphan*/  or_valid; } ;

/* Variables and functions */
#define  e1000_i210 129 
#define  e1000_i211 128 
 int /*<<< orphan*/  igb_get_flash_presence_i210 (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_get_fw_version (struct e1000_hw*,struct e1000_fw_version*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,...) ; 

void igb_set_fw_version(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_fw_version fw;

	igb_get_fw_version(hw, &fw);

	switch (hw->mac.type) {
	case e1000_i210:
	case e1000_i211:
		if (!(igb_get_flash_presence_i210(hw))) {
			snprintf(adapter->fw_version,
				 sizeof(adapter->fw_version),
				 "%2d.%2d-%d",
				 fw.invm_major, fw.invm_minor,
				 fw.invm_img_type);
			break;
		}
		/* fall through */
	default:
		/* if option is rom valid, display its version too */
		if (fw.or_valid) {
			snprintf(adapter->fw_version,
				 sizeof(adapter->fw_version),
				 "%d.%d, 0x%08x, %d.%d.%d",
				 fw.eep_major, fw.eep_minor, fw.etrack_id,
				 fw.or_major, fw.or_build, fw.or_patch);
		/* no option rom */
		} else if (fw.etrack_id != 0X0000) {
			snprintf(adapter->fw_version,
			    sizeof(adapter->fw_version),
			    "%d.%d, 0x%08x",
			    fw.eep_major, fw.eep_minor, fw.etrack_id);
		} else {
		snprintf(adapter->fw_version,
		    sizeof(adapter->fw_version),
		    "%d.%d.%d",
		    fw.eep_major, fw.eep_minor, fw.eep_build);
		}
		break;
	}
}