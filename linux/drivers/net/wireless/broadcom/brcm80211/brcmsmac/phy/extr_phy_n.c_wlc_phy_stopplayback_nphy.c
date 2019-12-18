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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int nphy_bb_mult_save; int nphy_sample_play_lpf_bw_ctl_ovr; scalar_t__ phyhang_avoid; TYPE_1__ pubpi; } ;

/* Variables and functions */
 int BB_MULT_MASK ; 
 int BB_MULT_VALID_MASK ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID1 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_IQLOCAL ; 
 scalar_t__ NPHY_iqloCalCmdGctl_IQLO_CAL_EN ; 
 int /*<<< orphan*/  NPHY_sampleCmd_STOP ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  and_phy_reg (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy_rev7 (struct brcms_phy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 

void wlc_phy_stopplayback_nphy(struct brcms_phy *pi)
{
	u16 playback_status;
	u16 bb_mult;

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, true);

	playback_status = read_phy_reg(pi, 0xc7);
	if (playback_status & 0x1)
		or_phy_reg(pi, 0xc3, NPHY_sampleCmd_STOP);
	else if (playback_status & 0x2)
		and_phy_reg(pi, 0xc2,
			    (u16) ~NPHY_iqloCalCmdGctl_IQLO_CAL_EN);

	and_phy_reg(pi, 0xc3, (u16) ~(0x1 << 2));

	if ((pi->nphy_bb_mult_save & BB_MULT_VALID_MASK) != 0) {

		bb_mult = pi->nphy_bb_mult_save & BB_MULT_MASK;
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_IQLOCAL, 1, 87, 16,
					 &bb_mult);

		pi->nphy_bb_mult_save = 0;
	}

	if (NREV_IS(pi->pubpi.phy_rev, 7) || NREV_GE(pi->pubpi.phy_rev, 8)) {
		if (pi->nphy_sample_play_lpf_bw_ctl_ovr) {
			wlc_phy_rfctrl_override_nphy_rev7(
				pi,
				(0x1 << 7),
				0, 0, 1,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);
			pi->nphy_sample_play_lpf_bw_ctl_ovr = false;
		}
	}

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, false);
}