#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct atl1c_hw {scalar_t__ nic_type; int ctrl_flags; } ;

/* Variables and functions */
 int ATL1C_ASPM_L0S_SUPPORT ; 
 int ATL1C_ASPM_L1_SUPPORT ; 
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int FIELD_SETX (int,int /*<<< orphan*/ ,int) ; 
 int L1C_PM_CTRL_L1_ENTRY_TM ; 
 int /*<<< orphan*/  L1D_PMCTRL_L1_ENTRY_TM ; 
 int L1D_PMCTRL_L1_ENTRY_TM_16US ; 
 int L2CB1_PM_CTRL_L1_ENTRY_TM ; 
 int PMCTRL_TXL1_AFTER_L0S ; 
 int PM_CTRL_ASPM_L0S_EN ; 
 int PM_CTRL_ASPM_L1_EN ; 
 int PM_CTRL_CLK_SWH_L1 ; 
 int PM_CTRL_HOTRST ; 
 int /*<<< orphan*/  PM_CTRL_L1_ENTRY_TIMER ; 
 int PM_CTRL_MAC_ASPM_CHK ; 
 int /*<<< orphan*/  PM_CTRL_PM_REQ_TIMER ; 
 int PM_CTRL_PM_REQ_TO_DEF ; 
 int PM_CTRL_RCVR_WT_TIMER ; 
 int PM_CTRL_SA_DLY_EN ; 
 int PM_CTRL_SERDES_BUFS_RX_L1_EN ; 
 int PM_CTRL_SERDES_L1_EN ; 
 int PM_CTRL_SERDES_PD_EX_L1 ; 
 int PM_CTRL_SERDES_PLL_L1_EN ; 
 int /*<<< orphan*/  REG_PM_CTRL ; 
 scalar_t__ SPEED_0 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 scalar_t__ athr_l1d ; 
 scalar_t__ athr_l1d_2 ; 
 scalar_t__ athr_l2c_b ; 
 scalar_t__ athr_l2c_b2 ; 

__attribute__((used)) static void atl1c_set_aspm(struct atl1c_hw *hw, u16 link_speed)
{
	u32 pm_ctrl_data;
	u32 link_l1_timer;

	AT_READ_REG(hw, REG_PM_CTRL, &pm_ctrl_data);
	pm_ctrl_data &= ~(PM_CTRL_ASPM_L1_EN |
			  PM_CTRL_ASPM_L0S_EN |
			  PM_CTRL_MAC_ASPM_CHK);
	/* L1 timer */
	if (hw->nic_type == athr_l2c_b2 || hw->nic_type == athr_l1d_2) {
		pm_ctrl_data &= ~PMCTRL_TXL1_AFTER_L0S;
		link_l1_timer =
			link_speed == SPEED_1000 || link_speed == SPEED_100 ?
			L1D_PMCTRL_L1_ENTRY_TM_16US : 1;
		pm_ctrl_data = FIELD_SETX(pm_ctrl_data,
			L1D_PMCTRL_L1_ENTRY_TM, link_l1_timer);
	} else {
		link_l1_timer = hw->nic_type == athr_l2c_b ?
			L2CB1_PM_CTRL_L1_ENTRY_TM : L1C_PM_CTRL_L1_ENTRY_TM;
		if (link_speed != SPEED_1000 && link_speed != SPEED_100)
			link_l1_timer = 1;
		pm_ctrl_data = FIELD_SETX(pm_ctrl_data,
			PM_CTRL_L1_ENTRY_TIMER, link_l1_timer);
	}

	/* L0S/L1 enable */
	if ((hw->ctrl_flags & ATL1C_ASPM_L0S_SUPPORT) && link_speed != SPEED_0)
		pm_ctrl_data |= PM_CTRL_ASPM_L0S_EN | PM_CTRL_MAC_ASPM_CHK;
	if (hw->ctrl_flags & ATL1C_ASPM_L1_SUPPORT)
		pm_ctrl_data |= PM_CTRL_ASPM_L1_EN | PM_CTRL_MAC_ASPM_CHK;

	/* l2cb & l1d & l2cb2 & l1d2 */
	if (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l1d ||
	    hw->nic_type == athr_l2c_b2 || hw->nic_type == athr_l1d_2) {
		pm_ctrl_data = FIELD_SETX(pm_ctrl_data,
			PM_CTRL_PM_REQ_TIMER, PM_CTRL_PM_REQ_TO_DEF);
		pm_ctrl_data |= PM_CTRL_RCVR_WT_TIMER |
				PM_CTRL_SERDES_PD_EX_L1 |
				PM_CTRL_CLK_SWH_L1;
		pm_ctrl_data &= ~(PM_CTRL_SERDES_L1_EN |
				  PM_CTRL_SERDES_PLL_L1_EN |
				  PM_CTRL_SERDES_BUFS_RX_L1_EN |
				  PM_CTRL_SA_DLY_EN |
				  PM_CTRL_HOTRST);
		/* disable l0s if link down or l2cb */
		if (link_speed == SPEED_0 || hw->nic_type == athr_l2c_b)
			pm_ctrl_data &= ~PM_CTRL_ASPM_L0S_EN;
	} else { /* l1c */
		pm_ctrl_data =
			FIELD_SETX(pm_ctrl_data, PM_CTRL_L1_ENTRY_TIMER, 0);
		if (link_speed != SPEED_0) {
			pm_ctrl_data |= PM_CTRL_SERDES_L1_EN |
					PM_CTRL_SERDES_PLL_L1_EN |
					PM_CTRL_SERDES_BUFS_RX_L1_EN;
			pm_ctrl_data &= ~(PM_CTRL_SERDES_PD_EX_L1 |
					  PM_CTRL_CLK_SWH_L1 |
					  PM_CTRL_ASPM_L0S_EN |
					  PM_CTRL_ASPM_L1_EN);
		} else { /* link down */
			pm_ctrl_data |= PM_CTRL_CLK_SWH_L1;
			pm_ctrl_data &= ~(PM_CTRL_SERDES_L1_EN |
					  PM_CTRL_SERDES_PLL_L1_EN |
					  PM_CTRL_SERDES_BUFS_RX_L1_EN |
					  PM_CTRL_ASPM_L0S_EN);
		}
	}
	AT_WRITE_REG(hw, REG_PM_CTRL, pm_ctrl_data);

	return;
}