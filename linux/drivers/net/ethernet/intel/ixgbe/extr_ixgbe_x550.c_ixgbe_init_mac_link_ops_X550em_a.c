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
struct TYPE_2__ {int (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/ * setup_fc; int /*<<< orphan*/  fc_autoneg; int /*<<< orphan*/  check_link; int /*<<< orphan*/  setup_link; } ;
struct ixgbe_mac_info {TYPE_1__ ops; } ;
struct ixgbe_hw {int /*<<< orphan*/  device_id; struct ixgbe_mac_info mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_1G_T ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_1G_T_L ; 
 int /*<<< orphan*/  ixgbe_check_mac_link_generic ; 
 int /*<<< orphan*/  ixgbe_fc_autoneg_backplane_x550em_a ; 
 int /*<<< orphan*/  ixgbe_fc_autoneg_fiber_x550em_a ; 
 int /*<<< orphan*/ * ixgbe_fc_autoneg_fw ; 
 int /*<<< orphan*/  ixgbe_fc_autoneg_sgmii_x550em_a ; 
#define  ixgbe_media_type_backplane 130 
#define  ixgbe_media_type_copper 129 
#define  ixgbe_media_type_fiber 128 
 int /*<<< orphan*/ * ixgbe_setup_fc_backplane_x550em_a ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_t_X550em ; 
 int /*<<< orphan*/  ixgbe_setup_sgmii_fw ; 
 int stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static void ixgbe_init_mac_link_ops_X550em_a(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;

	switch (mac->ops.get_media_type(hw)) {
	case ixgbe_media_type_fiber:
		mac->ops.setup_fc = NULL;
		mac->ops.fc_autoneg = ixgbe_fc_autoneg_fiber_x550em_a;
		break;
	case ixgbe_media_type_copper:
		if (hw->device_id != IXGBE_DEV_ID_X550EM_A_1G_T &&
		    hw->device_id != IXGBE_DEV_ID_X550EM_A_1G_T_L) {
			mac->ops.setup_link = ixgbe_setup_mac_link_t_X550em;
			break;
		}
		mac->ops.fc_autoneg = ixgbe_fc_autoneg_sgmii_x550em_a;
		mac->ops.setup_fc = ixgbe_fc_autoneg_fw;
		mac->ops.setup_link = ixgbe_setup_sgmii_fw;
		mac->ops.check_link = ixgbe_check_mac_link_generic;
		break;
	case ixgbe_media_type_backplane:
		mac->ops.fc_autoneg = ixgbe_fc_autoneg_backplane_x550em_a;
		mac->ops.setup_fc = ixgbe_setup_fc_backplane_x550em_a;
		break;
	default:
		break;
	}
}