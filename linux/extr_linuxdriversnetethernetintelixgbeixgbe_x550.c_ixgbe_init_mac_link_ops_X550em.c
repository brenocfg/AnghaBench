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
struct TYPE_2__ {int (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/  setup_link; int /*<<< orphan*/  check_link; int /*<<< orphan*/  setup_fc; int /*<<< orphan*/  set_rate_select_speed; int /*<<< orphan*/  setup_mac_link; int /*<<< orphan*/ * flap_tx_laser; int /*<<< orphan*/ * enable_tx_laser; int /*<<< orphan*/ * disable_tx_laser; } ;
struct ixgbe_mac_info {scalar_t__ type; TYPE_1__ ops; } ;
struct ixgbe_hw {struct ixgbe_mac_info mac; int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
#define  IXGBE_DEV_ID_X550EM_A_SFP 132 
#define  IXGBE_DEV_ID_X550EM_A_SFP_N 131 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SGMII ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_SGMII_L ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_X_1G_T ; 
 int /*<<< orphan*/  ixgbe_check_link_t_X550em ; 
 int /*<<< orphan*/  ixgbe_init_mac_link_ops_X550em_a (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_mac_x550em_a ; 
#define  ixgbe_media_type_backplane 130 
#define  ixgbe_media_type_copper 129 
#define  ixgbe_media_type_fiber 128 
 int /*<<< orphan*/  ixgbe_set_soft_rate_select_speed ; 
 int /*<<< orphan*/  ixgbe_setup_fc_generic ; 
 int /*<<< orphan*/  ixgbe_setup_fc_x550em ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_multispeed_fiber ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_sfp_n ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_sfp_x550a ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_sfp_x550em ; 
 int /*<<< orphan*/  ixgbe_setup_mac_link_t_X550em ; 
 int /*<<< orphan*/  ixgbe_setup_sgmii ; 
 int stub1 (struct ixgbe_hw*) ; 

__attribute__((used)) static void ixgbe_init_mac_link_ops_X550em(struct ixgbe_hw *hw)
{
	struct ixgbe_mac_info *mac = &hw->mac;

	mac->ops.setup_fc = ixgbe_setup_fc_x550em;

	switch (mac->ops.get_media_type(hw)) {
	case ixgbe_media_type_fiber:
		/* CS4227 does not support autoneg, so disable the laser control
		 * functions for SFP+ fiber
		 */
		mac->ops.disable_tx_laser = NULL;
		mac->ops.enable_tx_laser = NULL;
		mac->ops.flap_tx_laser = NULL;
		mac->ops.setup_link = ixgbe_setup_mac_link_multispeed_fiber;
		switch (hw->device_id) {
		case IXGBE_DEV_ID_X550EM_A_SFP_N:
			mac->ops.setup_mac_link = ixgbe_setup_mac_link_sfp_n;
			break;
		case IXGBE_DEV_ID_X550EM_A_SFP:
			mac->ops.setup_mac_link =
						ixgbe_setup_mac_link_sfp_x550a;
			break;
		default:
			mac->ops.setup_mac_link =
						ixgbe_setup_mac_link_sfp_x550em;
			break;
		}
		mac->ops.set_rate_select_speed =
					ixgbe_set_soft_rate_select_speed;
		break;
	case ixgbe_media_type_copper:
		if (hw->device_id == IXGBE_DEV_ID_X550EM_X_1G_T)
			break;
		mac->ops.setup_link = ixgbe_setup_mac_link_t_X550em;
		mac->ops.setup_fc = ixgbe_setup_fc_generic;
		mac->ops.check_link = ixgbe_check_link_t_X550em;
		break;
	case ixgbe_media_type_backplane:
		if (hw->device_id == IXGBE_DEV_ID_X550EM_A_SGMII ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_A_SGMII_L)
			mac->ops.setup_link = ixgbe_setup_sgmii;
		break;
	default:
		break;
	}

	/* Additional modification for X550em_a devices */
	if (hw->mac.type == ixgbe_mac_x550em_a)
		ixgbe_init_mac_link_ops_X550em_a(hw);
}