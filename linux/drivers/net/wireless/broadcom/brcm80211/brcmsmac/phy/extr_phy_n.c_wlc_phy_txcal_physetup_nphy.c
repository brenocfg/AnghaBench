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
struct brcms_phy {int* tx_rx_cal_phy_saveregs; int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; int /*<<< orphan*/  internal_tx_iqlo_cal_tapoff_intpa_nphy; scalar_t__ use_int_tx_iqlo_cal_nphy; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID0 ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID1 ; 
 int /*<<< orphan*/  NPHY_RfctrlIntc_override_PA ; 
 int /*<<< orphan*/  NPHY_RfctrlIntc_override_TRSW ; 
 int /*<<< orphan*/  NPHY_TBL_ID_AFECTRL ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int PHY_CORE_0 ; 
 int /*<<< orphan*/  RADIO_2057_IPA5G_CASCOFFV_PU_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_IPA5G_CASCOFFV_PU_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_OVR_REG0 ; 
 int /*<<< orphan*/  RADIO_2057_PAD2G_TUNE_PUS_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_PAD2G_TUNE_PUS_CORE1 ; 
 int RADIO_MIMO_CORESEL_CORE1 ; 
 int RADIO_MIMO_CORESEL_CORE2 ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 void* read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_read_lpf_bw_ctl_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy_rev7 (struct brcms_phy*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrlintc_override_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_txcal_physetup_nphy(struct brcms_phy *pi)
{
	u16 val, mask;

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		pi->tx_rx_cal_phy_saveregs[0] = read_phy_reg(pi, 0xa6);
		pi->tx_rx_cal_phy_saveregs[1] = read_phy_reg(pi, 0xa7);

		mask = ((0x3 << 8) | (0x3 << 10));
		val = (0x2 << 8);
		val |= (0x2 << 10);
		mod_phy_reg(pi, 0xa6, mask, val);
		mod_phy_reg(pi, 0xa7, mask, val);

		val = read_phy_reg(pi, 0x8f);
		pi->tx_rx_cal_phy_saveregs[2] = val;
		val |= ((0x1 << 9) | (0x1 << 10));
		write_phy_reg(pi, 0x8f, val);

		val = read_phy_reg(pi, 0xa5);
		pi->tx_rx_cal_phy_saveregs[3] = val;
		val |= ((0x1 << 9) | (0x1 << 10));
		write_phy_reg(pi, 0xa5, val);

		pi->tx_rx_cal_phy_saveregs[4] = read_phy_reg(pi, 0x01);
		mod_phy_reg(pi, 0x01, (0x1 << 15), 0);

		wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_AFECTRL, 1, 3, 16,
					&val);
		pi->tx_rx_cal_phy_saveregs[5] = val;
		val = 0;
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_AFECTRL, 1, 3, 16,
					 &val);

		wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_AFECTRL, 1, 19, 16,
					&val);
		pi->tx_rx_cal_phy_saveregs[6] = val;
		val = 0;
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_AFECTRL, 1, 19, 16,
					 &val);

		pi->tx_rx_cal_phy_saveregs[7] = read_phy_reg(pi, 0x91);
		pi->tx_rx_cal_phy_saveregs[8] = read_phy_reg(pi, 0x92);

		if (!(pi->use_int_tx_iqlo_cal_nphy))
			wlc_phy_rfctrlintc_override_nphy(
				pi,
				NPHY_RfctrlIntc_override_PA,
				1,
				RADIO_MIMO_CORESEL_CORE1
				|
				RADIO_MIMO_CORESEL_CORE2);
		else
			wlc_phy_rfctrlintc_override_nphy(
				pi,
				NPHY_RfctrlIntc_override_PA,
				0,
				RADIO_MIMO_CORESEL_CORE1
				|
				RADIO_MIMO_CORESEL_CORE2);

		wlc_phy_rfctrlintc_override_nphy(pi,
						 NPHY_RfctrlIntc_override_TRSW,
						 0x2, RADIO_MIMO_CORESEL_CORE1);
		wlc_phy_rfctrlintc_override_nphy(pi,
						 NPHY_RfctrlIntc_override_TRSW,
						 0x8, RADIO_MIMO_CORESEL_CORE2);

		pi->tx_rx_cal_phy_saveregs[9] = read_phy_reg(pi, 0x297);
		pi->tx_rx_cal_phy_saveregs[10] = read_phy_reg(pi, 0x29b);
		mod_phy_reg(pi, (0 == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (0) << 0);

		mod_phy_reg(pi, (1 == PHY_CORE_0) ? 0x297 :
			    0x29b, (0x1 << 0), (0) << 0);

		if (NREV_IS(pi->pubpi.phy_rev, 7)
		    || NREV_GE(pi->pubpi.phy_rev, 8))
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 7),
				wlc_phy_read_lpf_bw_ctl_nphy
					(pi,
					0), 0, 0,
				NPHY_REV7_RFCTRLOVERRIDE_ID1);

		if (pi->use_int_tx_iqlo_cal_nphy
		    && !(pi->internal_tx_iqlo_cal_tapoff_intpa_nphy)) {

			if (NREV_IS(pi->pubpi.phy_rev, 7)) {

				mod_radio_reg(pi, RADIO_2057_OVR_REG0, 1 << 4,
					      1 << 4);

				if (CHSPEC_IS2G(pi->radio_chanspec)) {
					mod_radio_reg(
						pi,
						RADIO_2057_PAD2G_TUNE_PUS_CORE0,
						1, 0);
					mod_radio_reg(
						pi,
						RADIO_2057_PAD2G_TUNE_PUS_CORE1,
						1, 0);
				} else {
					mod_radio_reg(
					     pi,
					     RADIO_2057_IPA5G_CASCOFFV_PU_CORE0,
					     1, 0);
					mod_radio_reg(
					     pi,
					     RADIO_2057_IPA5G_CASCOFFV_PU_CORE1,
					     1, 0);
				}
			} else if (NREV_GE(pi->pubpi.phy_rev, 8)) {
				wlc_phy_rfctrl_override_nphy_rev7(
					pi,
					(0x1 << 3), 0,
					0x3, 0,
					NPHY_REV7_RFCTRLOVERRIDE_ID0);
			}
		}
	} else {
		pi->tx_rx_cal_phy_saveregs[0] = read_phy_reg(pi, 0xa6);
		pi->tx_rx_cal_phy_saveregs[1] = read_phy_reg(pi, 0xa7);

		mask = ((0x3 << 12) | (0x3 << 14));
		val = (0x2 << 12);
		val |= (0x2 << 14);
		mod_phy_reg(pi, 0xa6, mask, val);
		mod_phy_reg(pi, 0xa7, mask, val);

		val = read_phy_reg(pi, 0xa5);
		pi->tx_rx_cal_phy_saveregs[2] = val;
		val |= ((0x1 << 12) | (0x1 << 13));
		write_phy_reg(pi, 0xa5, val);

		wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_AFECTRL, 1, 2, 16,
					&val);
		pi->tx_rx_cal_phy_saveregs[3] = val;
		val |= 0x2000;
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_AFECTRL, 1, 2, 16,
					 &val);

		wlc_phy_table_read_nphy(pi, NPHY_TBL_ID_AFECTRL, 1, 18, 16,
					&val);
		pi->tx_rx_cal_phy_saveregs[4] = val;
		val |= 0x2000;
		wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_AFECTRL, 1, 18, 16,
					 &val);

		pi->tx_rx_cal_phy_saveregs[5] = read_phy_reg(pi, 0x91);
		pi->tx_rx_cal_phy_saveregs[6] = read_phy_reg(pi, 0x92);
		val = CHSPEC_IS5G(pi->radio_chanspec) ? 0x180 : 0x120;
		write_phy_reg(pi, 0x91, val);
		write_phy_reg(pi, 0x92, val);
	}
}