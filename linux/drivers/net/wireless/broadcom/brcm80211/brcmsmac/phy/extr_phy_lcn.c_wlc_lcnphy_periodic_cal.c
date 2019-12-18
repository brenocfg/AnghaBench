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
typedef  int /*<<< orphan*/  u16 ;
struct phytbl_info {int tbl_width; int* tbl_ptr; int tbl_len; scalar_t__ tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct lcnphy_rx_iqcomp {int dummy; } ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy_lcnphy {scalar_t__ lcnphy_full_cal_channel; int /*<<< orphan*/  lcnphy_current_index; } ;
struct TYPE_5__ {int /*<<< orphan*/  phy_rev; } ;
struct TYPE_4__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {int phy_forcecal; int* txpa_2g; TYPE_3__* sh; TYPE_2__ pubpi; int /*<<< orphan*/  d11core; int /*<<< orphan*/  radio_chanspec; int /*<<< orphan*/  phy_lastcal; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s32 ;
struct TYPE_6__ {int /*<<< orphan*/  physhim; int /*<<< orphan*/  now; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct lcnphy_rx_iqcomp*) ; 
 scalar_t__ CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCNPHY_TBL_ID_TXPWRCTL ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  M_CTS_DURATION ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lcnphy_rx_iqcomp* lcnphy_rx_iqcomp_table_rev0 ; 
 int /*<<< orphan*/  maccontrol ; 
 int /*<<< orphan*/  wlapi_bmac_write_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_deaf_mode (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_pwr_ctrl (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_idle_tssi_est (struct brcms_phy_pub*) ; 
 int /*<<< orphan*/  wlc_lcnphy_rx_iq_cal (struct brcms_phy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_by_index (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_pwr_ctrl (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int wlc_lcnphy_tssi2dbm (int,int,int,int) ; 
 scalar_t__ wlc_lcnphy_tssi_based_pwr_ctrl_enabled (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_txpwrtbl_iqlo_cal (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static void wlc_lcnphy_periodic_cal(struct brcms_phy *pi)
{
	bool suspend, full_cal;
	const struct lcnphy_rx_iqcomp *rx_iqcomp;
	int rx_iqcomp_sz;
	u16 SAVE_pwrctrl = wlc_lcnphy_get_tx_pwr_ctrl(pi);
	s8 index;
	struct phytbl_info tab;
	s32 a1, b0, b1;
	s32 tssi, pwr, mintargetpwr;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

	pi->phy_lastcal = pi->sh->now;
	pi->phy_forcecal = false;
	full_cal =
		(pi_lcn->lcnphy_full_cal_channel !=
		 CHSPEC_CHANNEL(pi->radio_chanspec));
	pi_lcn->lcnphy_full_cal_channel = CHSPEC_CHANNEL(pi->radio_chanspec);
	index = pi_lcn->lcnphy_current_index;

	suspend = (0 == (bcma_read32(pi->d11core, D11REGOFFS(maccontrol)) &
			 MCTL_EN_MAC));
	if (!suspend) {
		wlapi_bmac_write_shm(pi->sh->physhim, M_CTS_DURATION, 10000);
		wlapi_suspend_mac_and_wait(pi->sh->physhim);
	}

	wlc_lcnphy_deaf_mode(pi, true);

	wlc_lcnphy_txpwrtbl_iqlo_cal(pi);

	rx_iqcomp = lcnphy_rx_iqcomp_table_rev0;
	rx_iqcomp_sz = ARRAY_SIZE(lcnphy_rx_iqcomp_table_rev0);

	if (LCNREV_IS(pi->pubpi.phy_rev, 1))
		wlc_lcnphy_rx_iq_cal(pi, NULL, 0, true, false, 1, 40);
	else
		wlc_lcnphy_rx_iq_cal(pi, NULL, 0, true, false, 1, 127);

	if (wlc_lcnphy_tssi_based_pwr_ctrl_enabled(pi)) {

		wlc_lcnphy_idle_tssi_est((struct brcms_phy_pub *) pi);

		b0 = pi->txpa_2g[0];
		b1 = pi->txpa_2g[1];
		a1 = pi->txpa_2g[2];
		mintargetpwr = wlc_lcnphy_tssi2dbm(125, a1, b0, b1);

		tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
		tab.tbl_width = 32;
		tab.tbl_ptr = &pwr;
		tab.tbl_len = 1;
		tab.tbl_offset = 0;
		for (tssi = 0; tssi < 128; tssi++) {
			pwr = wlc_lcnphy_tssi2dbm(tssi, a1, b0, b1);
			pwr = (pwr < mintargetpwr) ? mintargetpwr : pwr;
			wlc_lcnphy_write_table(pi, &tab);
			tab.tbl_offset++;
		}
	}

	wlc_lcnphy_set_tx_pwr_by_index(pi, index);
	wlc_lcnphy_set_tx_pwr_ctrl(pi, SAVE_pwrctrl);
	wlc_lcnphy_deaf_mode(pi, false);
	if (!suspend)
		wlapi_enable_mac(pi->sh->physhim);
}