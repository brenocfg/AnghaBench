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
typedef  scalar_t__ u16 ;
struct brcms_phy_lcnphy {int lcnphy_tx_power_idx_override; scalar_t__ lcnphy_current_index; int /*<<< orphan*/  lcnphy_tssi_tx_cnt; int /*<<< orphan*/  lcnphy_tssi_npt; int /*<<< orphan*/  lcnphy_tssi_idx; } ;
struct TYPE_2__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_1__ u; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 scalar_t__ LCNPHY_TX_PWR_CTRL_HW ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_TEMPBASED ; 
 int /*<<< orphan*/  RADIO_2064_REG11F ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_clear_tx_power_offsets (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_disable_tx_gain_override (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_enable_tx_gain_override (struct brcms_phy*) ; 
 scalar_t__ wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_start_tx_pwr_idx (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 scalar_t__ wlc_lcnphy_set_tx_pwr_ctrl_mode (struct brcms_phy*,scalar_t__) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_npt (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_soft_ctrl (struct brcms_phy*,scalar_t__) ; 
 scalar_t__ wlc_lcnphy_tempcompensated_txpwrctrl (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_total_tx_frames (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_tx_pwr_update_npt (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_txpower_recalc_target (struct brcms_phy*) ; 

void wlc_lcnphy_set_tx_pwr_ctrl(struct brcms_phy *pi, u16 mode)
{
	u16 old_mode = wlc_lcnphy_get_tx_pwr_ctrl(pi);
	s8 index;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	mode = wlc_lcnphy_set_tx_pwr_ctrl_mode(pi, mode);
	old_mode = wlc_lcnphy_set_tx_pwr_ctrl_mode(pi, old_mode);

	mod_phy_reg(pi, 0x6da, (0x1 << 6),
		    ((LCNPHY_TX_PWR_CTRL_HW == mode) ? 1 : 0) << 6);

	mod_phy_reg(pi, 0x6a3, (0x1 << 4),
		    ((LCNPHY_TX_PWR_CTRL_HW == mode) ? 0 : 1) << 4);

	if (old_mode != mode) {
		if (LCNPHY_TX_PWR_CTRL_HW == old_mode) {

			wlc_lcnphy_tx_pwr_update_npt(pi);

			wlc_lcnphy_clear_tx_power_offsets(pi);
		}
		if (LCNPHY_TX_PWR_CTRL_HW == mode) {

			wlc_lcnphy_txpower_recalc_target(pi);

			wlc_lcnphy_set_start_tx_pwr_idx(pi,
							pi_lcn->
							lcnphy_tssi_idx);
			wlc_lcnphy_set_tx_pwr_npt(pi, pi_lcn->lcnphy_tssi_npt);
			mod_radio_reg(pi, RADIO_2064_REG11F, 0x4, 0);

			pi_lcn->lcnphy_tssi_tx_cnt =
				wlc_lcnphy_total_tx_frames(pi);

			wlc_lcnphy_disable_tx_gain_override(pi);
			pi_lcn->lcnphy_tx_power_idx_override = -1;
		} else
			wlc_lcnphy_enable_tx_gain_override(pi);

		mod_phy_reg(pi, 0x4a4,
			    ((0x1 << 15) | (0x1 << 14) | (0x1 << 13)), mode);
		if (mode == LCNPHY_TX_PWR_CTRL_TEMPBASED) {
			index = wlc_lcnphy_tempcompensated_txpwrctrl(pi);
			wlc_lcnphy_set_tx_pwr_soft_ctrl(pi, index);
			pi_lcn->lcnphy_current_index = (s8)
						       ((read_phy_reg(pi,
								      0x4a9) &
							 0xFF) / 2);
		}
	}
}