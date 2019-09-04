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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_AUTOC ; 
 scalar_t__ IXGBE_AUTOC_LMS_KX4_KX_KR ; 
 scalar_t__ IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN ; 
 scalar_t__ IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII ; 
 scalar_t__ IXGBE_AUTOC_LMS_MASK ; 
 scalar_t__ IXGBE_AUTO_NEG_TIME ; 
 scalar_t__ IXGBE_ERR_AUTONEG_NOT_COMPLETE ; 
 int /*<<< orphan*/  IXGBE_GSSR_MAC_CSR_SM ; 
 int /*<<< orphan*/  IXGBE_LINKS ; 
 scalar_t__ IXGBE_LINKS_KX_AN_COMP ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  ixgbe_reset_pipeline_82599 (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_verify_lesm_fw_enabled_82599 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_start_mac_link_82599(struct ixgbe_hw *hw,
			       bool autoneg_wait_to_complete)
{
	u32 autoc_reg;
	u32 links_reg;
	u32 i;
	s32 status = 0;
	bool got_lock = false;

	if (ixgbe_verify_lesm_fw_enabled_82599(hw)) {
		status = hw->mac.ops.acquire_swfw_sync(hw,
						IXGBE_GSSR_MAC_CSR_SM);
		if (status)
			return status;

		got_lock = true;
	}

	/* Restart link */
	ixgbe_reset_pipeline_82599(hw);

	if (got_lock)
		hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_MAC_CSR_SM);

	/* Only poll for autoneg to complete if specified to do so */
	if (autoneg_wait_to_complete) {
		autoc_reg = IXGBE_READ_REG(hw, IXGBE_AUTOC);
		if ((autoc_reg & IXGBE_AUTOC_LMS_MASK) ==
		     IXGBE_AUTOC_LMS_KX4_KX_KR ||
		    (autoc_reg & IXGBE_AUTOC_LMS_MASK) ==
		     IXGBE_AUTOC_LMS_KX4_KX_KR_1G_AN ||
		    (autoc_reg & IXGBE_AUTOC_LMS_MASK) ==
		     IXGBE_AUTOC_LMS_KX4_KX_KR_SGMII) {
			links_reg = 0; /* Just in case Autoneg time = 0 */
			for (i = 0; i < IXGBE_AUTO_NEG_TIME; i++) {
				links_reg = IXGBE_READ_REG(hw, IXGBE_LINKS);
				if (links_reg & IXGBE_LINKS_KX_AN_COMP)
					break;
				msleep(100);
			}
			if (!(links_reg & IXGBE_LINKS_KX_AN_COMP)) {
				status = IXGBE_ERR_AUTONEG_NOT_COMPLETE;
				hw_dbg(hw, "Autoneg did not complete.\n");
			}
		}
	}

	/* Add delay to filter out noises during initial link setup */
	msleep(50);

	return status;
}