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
struct TYPE_6__ {scalar_t__ (* identify ) (struct ixgbe_hw*) ;int /*<<< orphan*/ * reset; int /*<<< orphan*/ * write_reg; int /*<<< orphan*/ * read_reg; int /*<<< orphan*/ * setup_link; int /*<<< orphan*/  handle_lasi; int /*<<< orphan*/  enter_lplu; int /*<<< orphan*/  setup_internal_link; } ;
struct ixgbe_phy_info {scalar_t__ sfp_type; int type; int nw_mng_if_sel; TYPE_3__ ops; int /*<<< orphan*/  phy_semaphore_mask; } ;
struct TYPE_4__ {scalar_t__ (* get_media_type ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* set_lan_id ) (struct ixgbe_hw*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  type; TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; struct ixgbe_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_PHY_ADDR_INVALID ; 
 scalar_t__ IXGBE_ERR_SFP_NOT_SUPPORTED ; 
 int /*<<< orphan*/  IXGBE_FUSES0_GROUP (int /*<<< orphan*/ ) ; 
 int IXGBE_FUSES0_REV_MASK ; 
 int /*<<< orphan*/  IXGBE_GSSR_SHARED_I2C_SM ; 
 int /*<<< orphan*/  IXGBE_NW_MNG_IF_SEL ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_enter_lplu_t_x550em ; 
 int /*<<< orphan*/  ixgbe_handle_lasi_ext_t_x550em ; 
 int /*<<< orphan*/  ixgbe_init_mac_link_ops_X550em (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_mac_X550EM_x ; 
 scalar_t__ ixgbe_media_type_fiber ; 
#define  ixgbe_phy_ext_1g_t 134 
#define  ixgbe_phy_fw 133 
#define  ixgbe_phy_sgmii 132 
#define  ixgbe_phy_x550em_ext_t 131 
#define  ixgbe_phy_x550em_kr 130 
#define  ixgbe_phy_x550em_kx4 129 
#define  ixgbe_phy_x550em_xfi 128 
 int /*<<< orphan*/  ixgbe_read_mng_if_sel_x550em (struct ixgbe_hw*) ; 
 void* ixgbe_read_phy_reg_x550em ; 
 int /*<<< orphan*/ * ixgbe_reset_phy_fw ; 
 int /*<<< orphan*/ * ixgbe_reset_phy_t_X550em ; 
 int /*<<< orphan*/ * ixgbe_setup_fw_link ; 
 int /*<<< orphan*/  ixgbe_setup_internal_phy_t_x550em ; 
 int /*<<< orphan*/ * ixgbe_setup_kr_x550em ; 
 int /*<<< orphan*/  ixgbe_setup_mux_ctl (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_sfp_type_unknown ; 
 void* ixgbe_write_phy_reg_x550em ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*) ; 

__attribute__((used)) static s32 ixgbe_init_phy_ops_X550em(struct ixgbe_hw *hw)
{
	struct ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val;

	hw->mac.ops.set_lan_id(hw);

	ixgbe_read_mng_if_sel_x550em(hw);

	if (hw->mac.ops.get_media_type(hw) == ixgbe_media_type_fiber) {
		phy->phy_semaphore_mask = IXGBE_GSSR_SHARED_I2C_SM;
		ixgbe_setup_mux_ctl(hw);
	}

	/* Identify the PHY or SFP module */
	ret_val = phy->ops.identify(hw);
	if (ret_val == IXGBE_ERR_SFP_NOT_SUPPORTED ||
	    ret_val == IXGBE_ERR_PHY_ADDR_INVALID)
		return ret_val;

	/* Setup function pointers based on detected hardware */
	ixgbe_init_mac_link_ops_X550em(hw);
	if (phy->sfp_type != ixgbe_sfp_type_unknown)
		phy->ops.reset = NULL;

	/* Set functions pointers based on phy type */
	switch (hw->phy.type) {
	case ixgbe_phy_x550em_kx4:
		phy->ops.setup_link = NULL;
		phy->ops.read_reg = ixgbe_read_phy_reg_x550em;
		phy->ops.write_reg = ixgbe_write_phy_reg_x550em;
		break;
	case ixgbe_phy_x550em_kr:
		phy->ops.setup_link = ixgbe_setup_kr_x550em;
		phy->ops.read_reg = ixgbe_read_phy_reg_x550em;
		phy->ops.write_reg = ixgbe_write_phy_reg_x550em;
		break;
	case ixgbe_phy_x550em_xfi:
		/* link is managed by HW */
		phy->ops.setup_link = NULL;
		phy->ops.read_reg = ixgbe_read_phy_reg_x550em;
		phy->ops.write_reg = ixgbe_write_phy_reg_x550em;
		break;
	case ixgbe_phy_x550em_ext_t:
		/* Save NW management interface connected on board. This is used
		 * to determine internal PHY mode
		 */
		phy->nw_mng_if_sel = IXGBE_READ_REG(hw, IXGBE_NW_MNG_IF_SEL);

		/* If internal link mode is XFI, then setup iXFI internal link,
		 * else setup KR now.
		 */
		phy->ops.setup_internal_link =
					      ixgbe_setup_internal_phy_t_x550em;

		/* setup SW LPLU only for first revision */
		if (hw->mac.type == ixgbe_mac_X550EM_x &&
		    !(IXGBE_READ_REG(hw, IXGBE_FUSES0_GROUP(0)) &
		      IXGBE_FUSES0_REV_MASK))
			phy->ops.enter_lplu = ixgbe_enter_lplu_t_x550em;

		phy->ops.handle_lasi = ixgbe_handle_lasi_ext_t_x550em;
		phy->ops.reset = ixgbe_reset_phy_t_X550em;
		break;
	case ixgbe_phy_sgmii:
		phy->ops.setup_link = NULL;
		break;
	case ixgbe_phy_fw:
		phy->ops.setup_link = ixgbe_setup_fw_link;
		phy->ops.reset = ixgbe_reset_phy_fw;
		break;
	case ixgbe_phy_ext_1g_t:
		phy->ops.setup_link = NULL;
		phy->ops.read_reg = NULL;
		phy->ops.write_reg = NULL;
		phy->ops.reset = NULL;
		break;
	default:
		break;
	}

	return ret_val;
}