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
typedef  size_t uint ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int extpagain; } ;
struct TYPE_5__ {size_t phy_corenum; int /*<<< orphan*/  phy_rev; } ;
struct TYPE_4__ {int extpagain; } ;
struct brcms_phy {int phyhang_avoid; int nphy_txcal_bbmult; scalar_t__* nphy_txcal_pwr_idx; scalar_t__ nphy_bb_mult_save; TYPE_3__ srom_fem2g; TYPE_2__ pubpi; TYPE_1__ srom_fem5g; int /*<<< orphan*/  radio_chanspec; scalar_t__* nphy_cal_orig_pwr_idx; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_CAL_TSSISAMPS ; 
 int /*<<< orphan*/  NPHY_RfctrlIntc_override_PA ; 
 int /*<<< orphan*/  NPHY_RfctrlIntc_override_TRSW ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 size_t PHY_CORE_0 ; 
 int RADIO_MIMO_CORESEL_CORE1 ; 
 int RADIO_MIMO_CORESEL_CORE2 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int /*<<< orphan*/ ) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlc_phy_est_tonepwr_nphy (struct brcms_phy*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrlintc_override_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_stopplayback_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_tx_tone_nphy (struct brcms_phy*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_txpwr_index_nphy (struct brcms_phy*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void
wlc_phy_cal_txgainctrl_nphy(struct brcms_phy *pi, s32 dBm_targetpower,
			    bool debug)
{
	int gainctrl_loopidx;
	uint core;
	u16 m0m1, curr_m0m1;
	s32 delta_power;
	s32 txpwrindex;
	s32 qdBm_power[2];
	u16 orig_BBConfig;
	u16 phy_saveregs[4];
	u32 freq_test;
	u16 ampl_test = 250;
	uint stepsize;
	bool phyhang_avoid_state = false;

	if (NREV_GE(pi->pubpi.phy_rev, 7))
		stepsize = 2;
	else
		stepsize = 1;

	if (CHSPEC_IS40(pi->radio_chanspec))
		freq_test = 5000;
	else
		freq_test = 2500;

	wlc_phy_txpwr_index_nphy(pi, 1, pi->nphy_cal_orig_pwr_idx[0], true);
	wlc_phy_txpwr_index_nphy(pi, 2, pi->nphy_cal_orig_pwr_idx[1], true);

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, true);

	phyhang_avoid_state = pi->phyhang_avoid;
	pi->phyhang_avoid = false;

	phy_saveregs[0] = read_phy_reg(pi, 0x91);
	phy_saveregs[1] = read_phy_reg(pi, 0x92);
	phy_saveregs[2] = read_phy_reg(pi, 0xe7);
	phy_saveregs[3] = read_phy_reg(pi, 0xec);
	wlc_phy_rfctrlintc_override_nphy(pi, NPHY_RfctrlIntc_override_PA, 1,
					 RADIO_MIMO_CORESEL_CORE1 |
					 RADIO_MIMO_CORESEL_CORE2);

	if (!debug) {
		wlc_phy_rfctrlintc_override_nphy(pi,
						 NPHY_RfctrlIntc_override_TRSW,
						 0x2, RADIO_MIMO_CORESEL_CORE1);
		wlc_phy_rfctrlintc_override_nphy(pi,
						 NPHY_RfctrlIntc_override_TRSW,
						 0x8, RADIO_MIMO_CORESEL_CORE2);
	} else {
		wlc_phy_rfctrlintc_override_nphy(pi,
						 NPHY_RfctrlIntc_override_TRSW,
						 0x1, RADIO_MIMO_CORESEL_CORE1);
		wlc_phy_rfctrlintc_override_nphy(pi,
						 NPHY_RfctrlIntc_override_TRSW,
						 0x7, RADIO_MIMO_CORESEL_CORE2);
	}

	orig_BBConfig = read_phy_reg(pi, 0x01);
	mod_phy_reg(pi, 0x01, (0x1 << 15), 0);

	wlc_phy_table_read_nphy(pi, 15, 1, 87, 16, &m0m1);

	for (core = 0; core < pi->pubpi.phy_corenum; core++) {
		txpwrindex = (s32) pi->nphy_cal_orig_pwr_idx[core];

		for (gainctrl_loopidx = 0; gainctrl_loopidx < 2;
		     gainctrl_loopidx++) {
			wlc_phy_tx_tone_nphy(pi, freq_test, ampl_test, 0, 0,
					     false);

			if (core == PHY_CORE_0)
				curr_m0m1 = m0m1 & 0xff00;
			else
				curr_m0m1 = m0m1 & 0x00ff;

			wlc_phy_table_write_nphy(pi, 15, 1, 87, 16, &curr_m0m1);
			wlc_phy_table_write_nphy(pi, 15, 1, 95, 16, &curr_m0m1);

			udelay(50);

			wlc_phy_est_tonepwr_nphy(pi, qdBm_power,
						 NPHY_CAL_TSSISAMPS);

			pi->nphy_bb_mult_save = 0;
			wlc_phy_stopplayback_nphy(pi);

			delta_power = (dBm_targetpower * 4) - qdBm_power[core];

			txpwrindex -= stepsize * delta_power;
			if (txpwrindex < 0)
				txpwrindex = 0;
			else if (txpwrindex > 127)
				txpwrindex = 127;

			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				if (NREV_IS(pi->pubpi.phy_rev, 4) &&
				    (pi->srom_fem5g.extpagain == 3)) {
					if (txpwrindex < 30)
						txpwrindex = 30;
				}
			} else {
				if (NREV_GE(pi->pubpi.phy_rev, 5) &&
				    (pi->srom_fem2g.extpagain == 3)) {
					if (txpwrindex < 50)
						txpwrindex = 50;
				}
			}

			wlc_phy_txpwr_index_nphy(pi, (1 << core),
						 (u8) txpwrindex, true);
		}

		pi->nphy_txcal_pwr_idx[core] = (u8) txpwrindex;

		if (debug) {
			u16 radio_gain;
			u16 dbg_m0m1;

			wlc_phy_table_read_nphy(pi, 15, 1, 87, 16, &dbg_m0m1);

			wlc_phy_tx_tone_nphy(pi, freq_test, ampl_test, 0, 0,
					     false);

			wlc_phy_table_write_nphy(pi, 15, 1, 87, 16, &dbg_m0m1);
			wlc_phy_table_write_nphy(pi, 15, 1, 95, 16, &dbg_m0m1);

			udelay(100);

			wlc_phy_est_tonepwr_nphy(pi, qdBm_power,
						 NPHY_CAL_TSSISAMPS);

			wlc_phy_table_read_nphy(pi, 7, 1, (0x110 + core), 16,
						&radio_gain);

			mdelay(4000);
			pi->nphy_bb_mult_save = 0;
			wlc_phy_stopplayback_nphy(pi);
		}
	}

	wlc_phy_txpwr_index_nphy(pi, 1, pi->nphy_txcal_pwr_idx[0], true);
	wlc_phy_txpwr_index_nphy(pi, 2, pi->nphy_txcal_pwr_idx[1], true);

	wlc_phy_table_read_nphy(pi, 15, 1, 87, 16, &pi->nphy_txcal_bbmult);

	write_phy_reg(pi, 0x01, orig_BBConfig);

	write_phy_reg(pi, 0x91, phy_saveregs[0]);
	write_phy_reg(pi, 0x92, phy_saveregs[1]);
	write_phy_reg(pi, 0xe7, phy_saveregs[2]);
	write_phy_reg(pi, 0xec, phy_saveregs[3]);

	pi->phyhang_avoid = phyhang_avoid_state;

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, false);
}