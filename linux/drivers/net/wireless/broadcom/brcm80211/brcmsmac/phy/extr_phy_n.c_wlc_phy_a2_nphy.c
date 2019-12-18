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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct nphy_txgains {int* txlpf; int* txgm; int* pga; int* ipa; int* pad; } ;
struct TYPE_4__ {int* pad; int* pga; } ;
struct nphy_ipa_txcalgains {int index; scalar_t__ useindex; TYPE_1__ gains; } ;
struct TYPE_6__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ bw; TYPE_3__ pubpi; int /*<<< orphan*/  radio_chanspec; TYPE_2__* sh; } ;
typedef  enum phy_cal_mode { ____Placeholder_phy_cal_mode } phy_cal_mode ;
struct TYPE_5__ {scalar_t__ chip; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM47162 ; 
 int CAL_FULL ; 
 int CAL_GCTRL ; 
 int CAL_SOFT ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID0 ; 
 int /*<<< orphan*/  NPHY_REV7_RfctrlOverride_cmd_txgain ; 
 int /*<<< orphan*/  NPHY_TBL_ID_EPSILONTBL0 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_EPSILONTBL1 ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 size_t PHY_CORE_0 ; 
 int /*<<< orphan*/  SPINWAIT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WL_CHANSPEC_BW_40 ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_a1_nphy (struct brcms_phy*,size_t,int,int /*<<< orphan*/ ,int) ; 
 struct nphy_txgains wlc_phy_get_tx_gain_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_ipa_set_bbmult_nphy (struct brcms_phy*,size_t,size_t) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_1tomany_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy (struct brcms_phy*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy_rev7 (struct brcms_phy*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void
wlc_phy_a2_nphy(struct brcms_phy *pi, struct nphy_ipa_txcalgains *txgains,
		enum phy_cal_mode cal_mode, u8 core)
{
	u16 phy_a1, phy_a2, phy_a3;
	u16 phy_a4, phy_a5;
	bool phy_a6;
	u8 phy_a7, m[2];
	u32 phy_a8 = 0;
	struct nphy_txgains phy_a9;

	if (NREV_LT(pi->pubpi.phy_rev, 3))
		return;

	phy_a7 = (core == PHY_CORE_0) ? 1 : 0;

	phy_a6 = ((cal_mode == CAL_GCTRL)
		  || (cal_mode == CAL_SOFT)) ? true : false;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {

		phy_a9 = wlc_phy_get_tx_gain_nphy(pi);

		if (CHSPEC_IS2G(pi->radio_chanspec))
			phy_a5 = ((phy_a9.txlpf[core] << 15) |
				  (phy_a9.txgm[core] << 12) |
				  (phy_a9.pga[core] << 8) |
				  (txgains->gains.pad[core] << 3) |
				  (phy_a9.ipa[core]));
		else
			phy_a5 = ((phy_a9.txlpf[core] << 15) |
				  (phy_a9.txgm[core] << 12) |
				  (txgains->gains.pga[core] << 8) |
				  (phy_a9.pad[core] << 3) | (phy_a9.ipa[core]));

		wlc_phy_rfctrl_override_1tomany_nphy(
			pi,
			NPHY_REV7_RfctrlOverride_cmd_txgain,
			phy_a5, (1 << core), 0);

		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			if ((pi->pubpi.radiorev <= 4)
			    || (pi->pubpi.radiorev == 6))
				m[core] = (pi->bw == WL_CHANSPEC_BW_40) ?
					  60 : 79;
			else
				m[core] = (pi->bw == WL_CHANSPEC_BW_40) ?
					  45 : 64;
		} else {
			m[core] = (pi->bw == WL_CHANSPEC_BW_40) ? 75 : 107;
		}

		m[phy_a7] = 0;
		wlc_phy_ipa_set_bbmult_nphy(pi, m[0], m[1]);

		phy_a2 = 63;

		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			if ((pi->pubpi.radiorev == 4)
			    || (pi->pubpi.radiorev == 6)) {
				phy_a1 = 30;
				phy_a3 = 30;
			} else {
				phy_a1 = 25;
				phy_a3 = 25;
			}
		} else {
			if ((pi->pubpi.radiorev == 5)
			    || (pi->pubpi.radiorev == 7)
			    || (pi->pubpi.radiorev == 8)) {
				phy_a1 = 25;
				phy_a3 = 25;
			} else {
				phy_a1 = 35;
				phy_a3 = 35;
			}
		}

		if (cal_mode == CAL_GCTRL) {
			if ((pi->pubpi.radiorev == 5)
			    && (CHSPEC_IS2G(pi->radio_chanspec)))
				phy_a1 = 55;
			else if (((pi->pubpi.radiorev == 7) &&
				  (CHSPEC_IS2G(pi->radio_chanspec))) ||
				 ((pi->pubpi.radiorev == 8) &&
				  (CHSPEC_IS2G(pi->radio_chanspec))))
				phy_a1 = 60;
			else
				phy_a1 = 63;

		} else if ((cal_mode != CAL_FULL) && (cal_mode != CAL_SOFT)) {

			phy_a1 = 35;
			phy_a3 = 35;
		}

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (1) << 0);

		mod_phy_reg(pi, (phy_a7 == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (0) << 0);

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
			    0x2a4, (0x1 << 13), (1) << 13);

		mod_phy_reg(pi, (phy_a7 == PHY_CORE_0) ? 0x2a3 :
			    0x2a4, (0x1 << 13), (0) << 13);

		write_phy_reg(pi, 0x2a1, 0x80);
		write_phy_reg(pi, 0x2a2, 0x100);

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
			    0x2a4, (0x7 << 4), (11) << 4);

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
			    0x2a4, (0x7 << 8), (11) << 8);

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
			    0x2a4, (0x7 << 0), (0x3) << 0);

		write_phy_reg(pi, 0x2e5, 0x20);

		mod_phy_reg(pi, 0x2a0, (0x3f << 0), (phy_a3) << 0);

		mod_phy_reg(pi, 0x29f, (0x3f << 0), (phy_a1) << 0);

		mod_phy_reg(pi, 0x29f, (0x3f << 8), (phy_a2) << 8);

		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 3),
						  1, ((core == 0) ? 1 : 2), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 3),
						  0, ((core == 0) ? 2 : 1), 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);

		write_phy_reg(pi, 0x2be, 1);
		SPINWAIT(read_phy_reg(pi, 0x2be), 10 * 1000 * 1000);

		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 3),
						  0, 0x3, 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);

		wlc_phy_table_write_nphy(pi,
					 (core ==
					  PHY_CORE_0) ? NPHY_TBL_ID_EPSILONTBL0
					 : NPHY_TBL_ID_EPSILONTBL1, 1, phy_a3,
					 32, &phy_a8);

		if (cal_mode != CAL_GCTRL) {
			if (CHSPEC_IS5G(pi->radio_chanspec))
				wlc_phy_a1_nphy(pi, core, 5, 0, 35);
		}

		wlc_phy_rfctrl_override_1tomany_nphy(
			pi,
			NPHY_REV7_RfctrlOverride_cmd_txgain,
			phy_a5, (1 << core), 1);

	} else {

		if (txgains) {
			if (txgains->useindex) {
				phy_a4 = 15 - ((txgains->index) >> 3);
				if (CHSPEC_IS2G(pi->radio_chanspec)) {
					if (NREV_GE(pi->pubpi.phy_rev, 6) &&
					    pi->sh->chip == BCMA_CHIP_ID_BCM47162) {
						phy_a5 = 0x10f7 | (phy_a4 << 8);
					} else if (NREV_GE(pi->pubpi.phy_rev, 6)) {
						phy_a5 = 0x00f7 | (phy_a4 << 8);
					} else if (NREV_IS(pi->pubpi.phy_rev, 5)) {
						phy_a5 = 0x10f7 | (phy_a4 << 8);
					} else {
						phy_a5 = 0x50f7 | (phy_a4 << 8);
					}
				} else {
					phy_a5 = 0x70f7 | (phy_a4 << 8);
				}
				wlc_phy_rfctrl_override_nphy(pi,
							     (0x1 << 13),
							     phy_a5,
							     (1 << core), 0);
			} else {
				wlc_phy_rfctrl_override_nphy(pi,
							     (0x1 << 13),
							     0x5bf7,
							     (1 << core), 0);
			}
		}

		if (CHSPEC_IS2G(pi->radio_chanspec))
			m[core] = (pi->bw == WL_CHANSPEC_BW_40) ? 45 : 64;
		else
			m[core] = (pi->bw == WL_CHANSPEC_BW_40) ? 75 : 107;

		m[phy_a7] = 0;
		wlc_phy_ipa_set_bbmult_nphy(pi, m[0], m[1]);

		phy_a2 = 63;

		if (cal_mode == CAL_FULL) {
			phy_a1 = 25;
			phy_a3 = 25;
		} else if (cal_mode == CAL_SOFT) {
			phy_a1 = 25;
			phy_a3 = 25;
		} else if (cal_mode == CAL_GCTRL) {
			phy_a1 = 63;
			phy_a3 = 25;
		} else {

			phy_a1 = 25;
			phy_a3 = 25;
		}

		mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (1) << 0);

		mod_phy_reg(pi, (phy_a7 == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (0) << 0);

		if (NREV_GE(pi->pubpi.phy_rev, 6)) {
			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0x1 << 13), (1) << 13);

			mod_phy_reg(pi, (phy_a7 == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0x1 << 13), (0) << 13);

			write_phy_reg(pi, 0x2a1, 0x20);
			write_phy_reg(pi, 0x2a2, 0x60);

			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0xf << 4), (9) << 4);

			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0xf << 8), (9) << 8);

			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0xf << 0), (0x2) << 0);

			write_phy_reg(pi, 0x2e5, 0x20);
		} else {
			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0x1 << 11), (1) << 11);

			mod_phy_reg(pi, (phy_a7 == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0x1 << 11), (0) << 11);

			write_phy_reg(pi, 0x2a1, 0x80);
			write_phy_reg(pi, 0x2a2, 0x600);

			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0x7 << 4), (0) << 4);

			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0x7 << 8), (0) << 8);

			mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x2a3 :
				    0x2a4, (0x7 << 0), (0x3) << 0);

			mod_phy_reg(pi, 0x2a0, (0x3f << 8), (0x20) << 8);

		}

		mod_phy_reg(pi, 0x2a0, (0x3f << 0), (phy_a3) << 0);

		mod_phy_reg(pi, 0x29f, (0x3f << 0), (phy_a1) << 0);

		mod_phy_reg(pi, 0x29f, (0x3f << 8), (phy_a2) << 8);

		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 3), 1, 0x3, 0);

		write_phy_reg(pi, 0x2be, 1);
		SPINWAIT(read_phy_reg(pi, 0x2be), 10 * 1000 * 1000);

		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 3), 0, 0x3, 0);

		wlc_phy_table_write_nphy(pi,
					 (core ==
					  PHY_CORE_0) ? NPHY_TBL_ID_EPSILONTBL0
					 : NPHY_TBL_ID_EPSILONTBL1, 1, phy_a3,
					 32, &phy_a8);

		if (cal_mode != CAL_GCTRL)
			wlc_phy_a1_nphy(pi, core, 5, 0, 40);
	}
}