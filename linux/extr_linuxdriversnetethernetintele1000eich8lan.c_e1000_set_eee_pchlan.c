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
typedef  int u16 ;
struct TYPE_5__ {int /*<<< orphan*/  (* release ) (struct e1000_hw*) ;scalar_t__ (* acquire ) (struct e1000_hw*) ;} ;
struct TYPE_6__ {int type; TYPE_2__ ops; } ;
struct e1000_dev_spec_ich8lan {int eee_lp_ability; int /*<<< orphan*/  eee_disable; } ;
struct TYPE_4__ {struct e1000_dev_spec_ich8lan ich8lan; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_1__ dev_spec; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int I217_EEE_ADVERTISEMENT ; 
 int I217_EEE_LP_ABILITY ; 
 int I217_EEE_PCS_STATUS ; 
 int I82579_EEE_1000_SUPPORTED ; 
 int I82579_EEE_100_SUPPORTED ; 
 int I82579_EEE_ADVERTISEMENT ; 
 int I82579_EEE_LP_ABILITY ; 
 int I82579_EEE_PCS_STATUS ; 
 int I82579_LPI_100_PLL_SHUT ; 
 int /*<<< orphan*/  I82579_LPI_CTRL ; 
 int I82579_LPI_CTRL_1000_ENABLE ; 
 int I82579_LPI_CTRL_100_ENABLE ; 
 int I82579_LPI_CTRL_ENABLE_MASK ; 
 int I82579_LPI_PLL_SHUT ; 
 int LPA_100FULL ; 
 int /*<<< orphan*/  MII_LPA ; 
#define  e1000_phy_82579 129 
#define  e1000_phy_i217 128 
 scalar_t__ e1000_read_emi_reg_locked (struct e1000_hw*,int,int*) ; 
 scalar_t__ e1000_write_emi_reg_locked (struct e1000_hw*,int,int) ; 
 scalar_t__ e1e_rphy_locked (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1e_wphy_locked (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 

s32 e1000_set_eee_pchlan(struct e1000_hw *hw)
{
	struct e1000_dev_spec_ich8lan *dev_spec = &hw->dev_spec.ich8lan;
	s32 ret_val;
	u16 lpa, pcs_status, adv, adv_addr, lpi_ctrl, data;

	switch (hw->phy.type) {
	case e1000_phy_82579:
		lpa = I82579_EEE_LP_ABILITY;
		pcs_status = I82579_EEE_PCS_STATUS;
		adv_addr = I82579_EEE_ADVERTISEMENT;
		break;
	case e1000_phy_i217:
		lpa = I217_EEE_LP_ABILITY;
		pcs_status = I217_EEE_PCS_STATUS;
		adv_addr = I217_EEE_ADVERTISEMENT;
		break;
	default:
		return 0;
	}

	ret_val = hw->phy.ops.acquire(hw);
	if (ret_val)
		return ret_val;

	ret_val = e1e_rphy_locked(hw, I82579_LPI_CTRL, &lpi_ctrl);
	if (ret_val)
		goto release;

	/* Clear bits that enable EEE in various speeds */
	lpi_ctrl &= ~I82579_LPI_CTRL_ENABLE_MASK;

	/* Enable EEE if not disabled by user */
	if (!dev_spec->eee_disable) {
		/* Save off link partner's EEE ability */
		ret_val = e1000_read_emi_reg_locked(hw, lpa,
						    &dev_spec->eee_lp_ability);
		if (ret_val)
			goto release;

		/* Read EEE advertisement */
		ret_val = e1000_read_emi_reg_locked(hw, adv_addr, &adv);
		if (ret_val)
			goto release;

		/* Enable EEE only for speeds in which the link partner is
		 * EEE capable and for which we advertise EEE.
		 */
		if (adv & dev_spec->eee_lp_ability & I82579_EEE_1000_SUPPORTED)
			lpi_ctrl |= I82579_LPI_CTRL_1000_ENABLE;

		if (adv & dev_spec->eee_lp_ability & I82579_EEE_100_SUPPORTED) {
			e1e_rphy_locked(hw, MII_LPA, &data);
			if (data & LPA_100FULL)
				lpi_ctrl |= I82579_LPI_CTRL_100_ENABLE;
			else
				/* EEE is not supported in 100Half, so ignore
				 * partner's EEE in 100 ability if full-duplex
				 * is not advertised.
				 */
				dev_spec->eee_lp_ability &=
				    ~I82579_EEE_100_SUPPORTED;
		}
	}

	if (hw->phy.type == e1000_phy_82579) {
		ret_val = e1000_read_emi_reg_locked(hw, I82579_LPI_PLL_SHUT,
						    &data);
		if (ret_val)
			goto release;

		data &= ~I82579_LPI_100_PLL_SHUT;
		ret_val = e1000_write_emi_reg_locked(hw, I82579_LPI_PLL_SHUT,
						     data);
	}

	/* R/Clr IEEE MMD 3.1 bits 11:10 - Tx/Rx LPI Received */
	ret_val = e1000_read_emi_reg_locked(hw, pcs_status, &data);
	if (ret_val)
		goto release;

	ret_val = e1e_wphy_locked(hw, I82579_LPI_CTRL, lpi_ctrl);
release:
	hw->phy.ops.release(hw);

	return ret_val;
}