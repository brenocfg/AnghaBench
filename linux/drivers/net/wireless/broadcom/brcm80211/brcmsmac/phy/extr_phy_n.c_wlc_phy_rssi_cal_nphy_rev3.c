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
typedef  int u8 ;
typedef  int u16 ;
struct brcms_phy_pub {int dummy; } ;
struct TYPE_4__ {void** rssical_phyregs_5G; void** rssical_radio_regs_5G; void** rssical_phyregs_2G; void** rssical_radio_regs_2G; } ;
struct TYPE_3__ {int phy_corenum; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; int /*<<< orphan*/  nphy_rssical_chanspec_5G; TYPE_2__ rssical_cache; TYPE_1__ pubpi; int /*<<< orphan*/  nphy_rssical_chanspec_2G; } ;
typedef  int s8 ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_RAIL_I ; 
 int /*<<< orphan*/  NPHY_RAIL_Q ; 
 int /*<<< orphan*/  NPHY_REV7_RFCTRLOVERRIDE_ID0 ; 
 int /*<<< orphan*/  NPHY_REV7_RfctrlOverride_cmd_rx_pu ; 
 int /*<<< orphan*/  NPHY_REV7_RfctrlOverride_cmd_rxrf_pu ; 
 int /*<<< orphan*/  NPHY_RFSEQ_RESET2RX ; 
 int NPHY_RSSICAL_MAXD ; 
 int NPHY_RSSICAL_MAXREAD ; 
 int NPHY_RSSICAL_NB_TARGET ; 
 int NPHY_RSSICAL_NPOLL ; 
 int NPHY_RSSICAL_W1_TARGET_REV3 ; 
 int NPHY_RSSICAL_W2_TARGET_REV3 ; 
 int NPHY_RSSI_SEL_NB ; 
 int NPHY_RSSI_SEL_W1 ; 
 int NPHY_RSSI_SEL_W2 ; 
 int /*<<< orphan*/  NPHY_RfctrlIntc_override_OFF ; 
 int /*<<< orphan*/  NPHY_RfctrlIntc_override_TRSW ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int PHY_CORE_0 ; 
 int RADIO_2056_RSSI_VCM_SHIFT ; 
 int RADIO_2056_RX0 ; 
 int RADIO_2056_RX1 ; 
 int RADIO_2056_RX_RSSI_MISC ; 
 int /*<<< orphan*/  RADIO_2056_VCM_MASK ; 
 int RADIO_2057_NB_MASTER_CORE0 ; 
 int RADIO_2057_NB_MASTER_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_VCM_MASK ; 
 int /*<<< orphan*/  RADIO_MIMO_CORESEL_ALLRXTX ; 
 int /*<<< orphan*/  RADIO_MIMO_CORESEL_CORE1 ; 
 int /*<<< orphan*/  RADIO_MIMO_CORESEL_CORE2 ; 
 int abs (int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int,int /*<<< orphan*/ ,int) ; 
 void* read_phy_reg (struct brcms_phy*,int) ; 
 void* read_radio_reg (struct brcms_phy*,int) ; 
 int wlc_phy_classifier_nphy (struct brcms_phy*,int,int) ; 
 int /*<<< orphan*/  wlc_phy_clip_det_nphy (struct brcms_phy*,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_force_rfseq_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_poll_rssi_nphy (struct brcms_phy*,int,int*,int) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_1tomany_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy (struct brcms_phy*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrl_override_nphy_rev7 (struct brcms_phy*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_rfctrlintc_override_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int wlc_phy_rxcore_getstate_nphy (struct brcms_phy_pub*) ; 
 int /*<<< orphan*/  wlc_phy_scale_offset_rssi_nphy (struct brcms_phy*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_rssi_cal_nphy_rev3(struct brcms_phy *pi)
{
	u16 classif_state;
	u16 clip_state[2];
	u16 clip_off[] = { 0xffff, 0xffff };
	s32 target_code;
	u8 vcm, min_vcm;
	u8 vcm_final = 0;
	u8 result_idx;
	s32 poll_results[8][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};
	s32 poll_result_core[4] = { 0, 0, 0, 0 };
	s32 min_d = NPHY_RSSICAL_MAXD, curr_d;
	s32 fine_digital_offset[4];
	s32 poll_results_min[4] = { 0, 0, 0, 0 };
	s32 min_poll;
	u8 vcm_level_max;
	u8 core;
	u8 wb_cnt;
	u8 rssi_type;
	u16 NPHY_Rfctrlintc1_save, NPHY_Rfctrlintc2_save;
	u16 NPHY_AfectrlOverride1_save, NPHY_AfectrlOverride2_save;
	u16 NPHY_AfectrlCore1_save, NPHY_AfectrlCore2_save;
	u16 NPHY_RfctrlOverride0_save, NPHY_RfctrlOverride1_save;
	u16 NPHY_RfctrlOverrideAux0_save, NPHY_RfctrlOverrideAux1_save;
	u16 NPHY_RfctrlCmd_save;
	u16 NPHY_RfctrlMiscReg1_save, NPHY_RfctrlMiscReg2_save;
	u16 NPHY_RfctrlRSSIOTHERS1_save, NPHY_RfctrlRSSIOTHERS2_save;
	u8 rxcore_state;
	u16 NPHY_REV7_RfctrlOverride3_save, NPHY_REV7_RfctrlOverride4_save;
	u16 NPHY_REV7_RfctrlOverride5_save, NPHY_REV7_RfctrlOverride6_save;
	u16 NPHY_REV7_RfctrlMiscReg3_save, NPHY_REV7_RfctrlMiscReg4_save;
	u16 NPHY_REV7_RfctrlMiscReg5_save, NPHY_REV7_RfctrlMiscReg6_save;

	NPHY_REV7_RfctrlOverride3_save =
		NPHY_REV7_RfctrlOverride4_save =
		NPHY_REV7_RfctrlOverride5_save =
		NPHY_REV7_RfctrlOverride6_save =
		NPHY_REV7_RfctrlMiscReg3_save =
		NPHY_REV7_RfctrlMiscReg4_save =
		NPHY_REV7_RfctrlMiscReg5_save =
		NPHY_REV7_RfctrlMiscReg6_save = 0;

	classif_state = wlc_phy_classifier_nphy(pi, 0, 0);
	wlc_phy_classifier_nphy(pi, (0x7 << 0), 4);
	wlc_phy_clip_det_nphy(pi, 0, clip_state);
	wlc_phy_clip_det_nphy(pi, 1, clip_off);

	NPHY_Rfctrlintc1_save = read_phy_reg(pi, 0x91);
	NPHY_Rfctrlintc2_save = read_phy_reg(pi, 0x92);
	NPHY_AfectrlOverride1_save = read_phy_reg(pi, 0x8f);
	NPHY_AfectrlOverride2_save = read_phy_reg(pi, 0xa5);
	NPHY_AfectrlCore1_save = read_phy_reg(pi, 0xa6);
	NPHY_AfectrlCore2_save = read_phy_reg(pi, 0xa7);
	NPHY_RfctrlOverride0_save = read_phy_reg(pi, 0xe7);
	NPHY_RfctrlOverride1_save = read_phy_reg(pi, 0xec);
	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		NPHY_REV7_RfctrlOverride3_save = read_phy_reg(pi, 0x342);
		NPHY_REV7_RfctrlOverride4_save = read_phy_reg(pi, 0x343);
		NPHY_REV7_RfctrlOverride5_save = read_phy_reg(pi, 0x346);
		NPHY_REV7_RfctrlOverride6_save = read_phy_reg(pi, 0x347);
	}
	NPHY_RfctrlOverrideAux0_save = read_phy_reg(pi, 0xe5);
	NPHY_RfctrlOverrideAux1_save = read_phy_reg(pi, 0xe6);
	NPHY_RfctrlCmd_save = read_phy_reg(pi, 0x78);
	NPHY_RfctrlMiscReg1_save = read_phy_reg(pi, 0xf9);
	NPHY_RfctrlMiscReg2_save = read_phy_reg(pi, 0xfb);
	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		NPHY_REV7_RfctrlMiscReg3_save = read_phy_reg(pi, 0x340);
		NPHY_REV7_RfctrlMiscReg4_save = read_phy_reg(pi, 0x341);
		NPHY_REV7_RfctrlMiscReg5_save = read_phy_reg(pi, 0x344);
		NPHY_REV7_RfctrlMiscReg6_save = read_phy_reg(pi, 0x345);
	}
	NPHY_RfctrlRSSIOTHERS1_save = read_phy_reg(pi, 0x7a);
	NPHY_RfctrlRSSIOTHERS2_save = read_phy_reg(pi, 0x7d);

	wlc_phy_rfctrlintc_override_nphy(pi, NPHY_RfctrlIntc_override_OFF, 0,
					 RADIO_MIMO_CORESEL_ALLRXTX);
	wlc_phy_rfctrlintc_override_nphy(pi, NPHY_RfctrlIntc_override_TRSW, 1,
					 RADIO_MIMO_CORESEL_ALLRXTX);

	if (NREV_GE(pi->pubpi.phy_rev, 7))
		wlc_phy_rfctrl_override_1tomany_nphy(
			pi,
			NPHY_REV7_RfctrlOverride_cmd_rxrf_pu,
			0, 0, 0);
	else
		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 0), 0, 0, 0);

	if (NREV_GE(pi->pubpi.phy_rev, 7))
		wlc_phy_rfctrl_override_1tomany_nphy(
			pi,
			NPHY_REV7_RfctrlOverride_cmd_rx_pu,
			1, 0, 0);
	else
		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 1), 1, 0, 0);

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 7),
						  1, 0, 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);
		wlc_phy_rfctrl_override_nphy_rev7(pi, (0x1 << 6), 1, 0, 0,
						  NPHY_REV7_RFCTRLOVERRIDE_ID0);
	} else {
		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 7), 1, 0, 0);
		wlc_phy_rfctrl_override_nphy(pi, (0x1 << 6), 1, 0, 0);
	}

	if (CHSPEC_IS5G(pi->radio_chanspec)) {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 5),
				0, 0, 0,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 4), 1, 0,
				0,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
		} else {
			wlc_phy_rfctrl_override_nphy(pi, (0x1 << 5), 0, 0, 0);
			wlc_phy_rfctrl_override_nphy(pi, (0x1 << 4), 1, 0, 0);
		}

	} else {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 4),
				0, 0, 0,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
			wlc_phy_rfctrl_override_nphy_rev7(
				pi, (0x1 << 5), 1, 0,
				0,
				NPHY_REV7_RFCTRLOVERRIDE_ID0);
		} else {
			wlc_phy_rfctrl_override_nphy(pi, (0x1 << 4), 0, 0, 0);
			wlc_phy_rfctrl_override_nphy(pi, (0x1 << 5), 1, 0, 0);
		}
	}

	rxcore_state = wlc_phy_rxcore_getstate_nphy(
		(struct brcms_phy_pub *) pi);

	vcm_level_max = 8;

	for (core = 0; core < pi->pubpi.phy_corenum; core++) {

		if ((rxcore_state & (1 << core)) == 0)
			continue;

		wlc_phy_scale_offset_rssi_nphy(pi, 0x0, 0x0,
					       core ==
					       PHY_CORE_0 ?
					       RADIO_MIMO_CORESEL_CORE1 :
					       RADIO_MIMO_CORESEL_CORE2,
					       NPHY_RAIL_I, NPHY_RSSI_SEL_NB);
		wlc_phy_scale_offset_rssi_nphy(pi, 0x0, 0x0,
					       core ==
					       PHY_CORE_0 ?
					       RADIO_MIMO_CORESEL_CORE1 :
					       RADIO_MIMO_CORESEL_CORE2,
					       NPHY_RAIL_Q, NPHY_RSSI_SEL_NB);

		for (vcm = 0; vcm < vcm_level_max; vcm++) {
			if (NREV_GE(pi->pubpi.phy_rev, 7))
				mod_radio_reg(pi, (core == PHY_CORE_0) ?
					      RADIO_2057_NB_MASTER_CORE0 :
					      RADIO_2057_NB_MASTER_CORE1,
					      RADIO_2057_VCM_MASK, vcm);
			else
				mod_radio_reg(pi, RADIO_2056_RX_RSSI_MISC |
					      ((core ==
						PHY_CORE_0) ? RADIO_2056_RX0 :
					       RADIO_2056_RX1),
					      RADIO_2056_VCM_MASK,
					      vcm << RADIO_2056_RSSI_VCM_SHIFT);

			wlc_phy_poll_rssi_nphy(pi, NPHY_RSSI_SEL_NB,
					       &poll_results[vcm][0],
					       NPHY_RSSICAL_NPOLL);
		}

		for (result_idx = 0; result_idx < 4; result_idx++) {
			if ((core == result_idx / 2) &&
			    (result_idx % 2 == 0)) {

				min_d = NPHY_RSSICAL_MAXD;
				min_vcm = 0;
				min_poll =
					NPHY_RSSICAL_MAXREAD *
					NPHY_RSSICAL_NPOLL + 1;
				for (vcm = 0; vcm < vcm_level_max; vcm++) {
					curr_d =
						poll_results[vcm][result_idx] *
						poll_results[vcm][result_idx] +
						poll_results[vcm][result_idx +
								  1] *
						poll_results[vcm][result_idx +
								  1];
					if (curr_d < min_d) {
						min_d = curr_d;
						min_vcm = vcm;
					}
					if (poll_results[vcm][result_idx] <
					    min_poll)
						min_poll =
							poll_results[vcm]
							[result_idx];
				}
				vcm_final = min_vcm;
				poll_results_min[result_idx] = min_poll;
			}
		}

		if (NREV_GE(pi->pubpi.phy_rev, 7))
			mod_radio_reg(pi, (core == PHY_CORE_0) ?
				      RADIO_2057_NB_MASTER_CORE0 :
				      RADIO_2057_NB_MASTER_CORE1,
				      RADIO_2057_VCM_MASK, vcm_final);
		else
			mod_radio_reg(pi, RADIO_2056_RX_RSSI_MISC |
				      ((core ==
					PHY_CORE_0) ? RADIO_2056_RX0 :
				       RADIO_2056_RX1), RADIO_2056_VCM_MASK,
				      vcm_final << RADIO_2056_RSSI_VCM_SHIFT);

		for (result_idx = 0; result_idx < 4; result_idx++) {
			if (core == result_idx / 2) {
				fine_digital_offset[result_idx] =
					(NPHY_RSSICAL_NB_TARGET *
					 NPHY_RSSICAL_NPOLL) -
					poll_results[vcm_final][result_idx];
				if (fine_digital_offset[result_idx] < 0) {
					fine_digital_offset[result_idx] =
						abs(fine_digital_offset
						    [result_idx]);
					fine_digital_offset[result_idx] +=
						(NPHY_RSSICAL_NPOLL / 2);
					fine_digital_offset[result_idx] /=
						NPHY_RSSICAL_NPOLL;
					fine_digital_offset[result_idx] =
						-fine_digital_offset[
								    result_idx];
				} else {
					fine_digital_offset[result_idx] +=
						(NPHY_RSSICAL_NPOLL / 2);
					fine_digital_offset[result_idx] /=
						NPHY_RSSICAL_NPOLL;
				}

				if (poll_results_min[result_idx] ==
				    NPHY_RSSICAL_MAXREAD * NPHY_RSSICAL_NPOLL)
					fine_digital_offset[result_idx] =
						(NPHY_RSSICAL_NB_TARGET -
						 NPHY_RSSICAL_MAXREAD - 1);

				wlc_phy_scale_offset_rssi_nphy(
					pi, 0x0,
					(s8)
					fine_digital_offset
					[result_idx],
					(result_idx / 2 == 0) ?
					RADIO_MIMO_CORESEL_CORE1 :
					RADIO_MIMO_CORESEL_CORE2,
					(result_idx % 2 == 0) ?
					NPHY_RAIL_I : NPHY_RAIL_Q,
					NPHY_RSSI_SEL_NB);
			}
		}

	}

	for (core = 0; core < pi->pubpi.phy_corenum; core++) {

		if ((rxcore_state & (1 << core)) == 0)
			continue;

		for (wb_cnt = 0; wb_cnt < 2; wb_cnt++) {
			if (wb_cnt == 0) {
				rssi_type = NPHY_RSSI_SEL_W1;
				target_code = NPHY_RSSICAL_W1_TARGET_REV3;
			} else {
				rssi_type = NPHY_RSSI_SEL_W2;
				target_code = NPHY_RSSICAL_W2_TARGET_REV3;
			}

			wlc_phy_scale_offset_rssi_nphy(pi, 0x0, 0x0,
						       core ==
						       PHY_CORE_0 ?
						       RADIO_MIMO_CORESEL_CORE1
						       :
						       RADIO_MIMO_CORESEL_CORE2,
						       NPHY_RAIL_I, rssi_type);
			wlc_phy_scale_offset_rssi_nphy(pi, 0x0, 0x0,
						       core ==
						       PHY_CORE_0 ?
						       RADIO_MIMO_CORESEL_CORE1
						       :
						       RADIO_MIMO_CORESEL_CORE2,
						       NPHY_RAIL_Q, rssi_type);

			wlc_phy_poll_rssi_nphy(pi, rssi_type, poll_result_core,
					       NPHY_RSSICAL_NPOLL);

			for (result_idx = 0; result_idx < 4; result_idx++) {
				if (core == result_idx / 2) {
					fine_digital_offset[result_idx] =
						(target_code *
						 NPHY_RSSICAL_NPOLL) -
						poll_result_core[result_idx];
					if (fine_digital_offset[result_idx] <
					    0) {
						fine_digital_offset[result_idx]
							= abs(
							    fine_digital_offset
							    [result_idx]);
						fine_digital_offset[result_idx]
							+= (NPHY_RSSICAL_NPOLL
							    / 2);
						fine_digital_offset[result_idx]
							/= NPHY_RSSICAL_NPOLL;
						fine_digital_offset[result_idx]
							= -fine_digital_offset
								[result_idx];
					} else {
						fine_digital_offset[result_idx]
							+= (NPHY_RSSICAL_NPOLL
							    / 2);
						fine_digital_offset[result_idx]
							/= NPHY_RSSICAL_NPOLL;
					}

					wlc_phy_scale_offset_rssi_nphy(
						pi, 0x0,
						(s8)
						fine_digital_offset
						[core *
						 2],
						(core == PHY_CORE_0) ?
						RADIO_MIMO_CORESEL_CORE1 :
						RADIO_MIMO_CORESEL_CORE2,
						(result_idx % 2 == 0) ?
						NPHY_RAIL_I :
						NPHY_RAIL_Q,
						rssi_type);
				}
			}

		}
	}

	write_phy_reg(pi, 0x91, NPHY_Rfctrlintc1_save);
	write_phy_reg(pi, 0x92, NPHY_Rfctrlintc2_save);

	wlc_phy_force_rfseq_nphy(pi, NPHY_RFSEQ_RESET2RX);

	mod_phy_reg(pi, 0xe7, (0x1 << 0), 1 << 0);
	mod_phy_reg(pi, 0x78, (0x1 << 0), 1 << 0);
	mod_phy_reg(pi, 0xe7, (0x1 << 0), 0);

	mod_phy_reg(pi, 0xec, (0x1 << 0), 1 << 0);
	mod_phy_reg(pi, 0x78, (0x1 << 1), 1 << 1);
	mod_phy_reg(pi, 0xec, (0x1 << 0), 0);

	write_phy_reg(pi, 0x8f, NPHY_AfectrlOverride1_save);
	write_phy_reg(pi, 0xa5, NPHY_AfectrlOverride2_save);
	write_phy_reg(pi, 0xa6, NPHY_AfectrlCore1_save);
	write_phy_reg(pi, 0xa7, NPHY_AfectrlCore2_save);
	write_phy_reg(pi, 0xe7, NPHY_RfctrlOverride0_save);
	write_phy_reg(pi, 0xec, NPHY_RfctrlOverride1_save);
	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		write_phy_reg(pi, 0x342, NPHY_REV7_RfctrlOverride3_save);
		write_phy_reg(pi, 0x343, NPHY_REV7_RfctrlOverride4_save);
		write_phy_reg(pi, 0x346, NPHY_REV7_RfctrlOverride5_save);
		write_phy_reg(pi, 0x347, NPHY_REV7_RfctrlOverride6_save);
	}
	write_phy_reg(pi, 0xe5, NPHY_RfctrlOverrideAux0_save);
	write_phy_reg(pi, 0xe6, NPHY_RfctrlOverrideAux1_save);
	write_phy_reg(pi, 0x78, NPHY_RfctrlCmd_save);
	write_phy_reg(pi, 0xf9, NPHY_RfctrlMiscReg1_save);
	write_phy_reg(pi, 0xfb, NPHY_RfctrlMiscReg2_save);
	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		write_phy_reg(pi, 0x340, NPHY_REV7_RfctrlMiscReg3_save);
		write_phy_reg(pi, 0x341, NPHY_REV7_RfctrlMiscReg4_save);
		write_phy_reg(pi, 0x344, NPHY_REV7_RfctrlMiscReg5_save);
		write_phy_reg(pi, 0x345, NPHY_REV7_RfctrlMiscReg6_save);
	}
	write_phy_reg(pi, 0x7a, NPHY_RfctrlRSSIOTHERS1_save);
	write_phy_reg(pi, 0x7d, NPHY_RfctrlRSSIOTHERS2_save);

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			pi->rssical_cache.rssical_radio_regs_2G[0] =
				read_radio_reg(pi, RADIO_2057_NB_MASTER_CORE0);
			pi->rssical_cache.rssical_radio_regs_2G[1] =
				read_radio_reg(pi, RADIO_2057_NB_MASTER_CORE1);
		} else {
			pi->rssical_cache.rssical_radio_regs_2G[0] =
				read_radio_reg(pi,
					       RADIO_2056_RX_RSSI_MISC |
					       RADIO_2056_RX0);
			pi->rssical_cache.rssical_radio_regs_2G[1] =
				read_radio_reg(pi,
					       RADIO_2056_RX_RSSI_MISC |
					       RADIO_2056_RX1);
		}

		pi->rssical_cache.rssical_phyregs_2G[0] =
			read_phy_reg(pi, 0x1a6);
		pi->rssical_cache.rssical_phyregs_2G[1] =
			read_phy_reg(pi, 0x1ac);
		pi->rssical_cache.rssical_phyregs_2G[2] =
			read_phy_reg(pi, 0x1b2);
		pi->rssical_cache.rssical_phyregs_2G[3] =
			read_phy_reg(pi, 0x1b8);
		pi->rssical_cache.rssical_phyregs_2G[4] =
			read_phy_reg(pi, 0x1a4);
		pi->rssical_cache.rssical_phyregs_2G[5] =
			read_phy_reg(pi, 0x1aa);
		pi->rssical_cache.rssical_phyregs_2G[6] =
			read_phy_reg(pi, 0x1b0);
		pi->rssical_cache.rssical_phyregs_2G[7] =
			read_phy_reg(pi, 0x1b6);
		pi->rssical_cache.rssical_phyregs_2G[8] =
			read_phy_reg(pi, 0x1a5);
		pi->rssical_cache.rssical_phyregs_2G[9] =
			read_phy_reg(pi, 0x1ab);
		pi->rssical_cache.rssical_phyregs_2G[10] =
			read_phy_reg(pi, 0x1b1);
		pi->rssical_cache.rssical_phyregs_2G[11] =
			read_phy_reg(pi, 0x1b7);

		pi->nphy_rssical_chanspec_2G = pi->radio_chanspec;
	} else {
		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			pi->rssical_cache.rssical_radio_regs_5G[0] =
				read_radio_reg(pi, RADIO_2057_NB_MASTER_CORE0);
			pi->rssical_cache.rssical_radio_regs_5G[1] =
				read_radio_reg(pi, RADIO_2057_NB_MASTER_CORE1);
		} else {
			pi->rssical_cache.rssical_radio_regs_5G[0] =
				read_radio_reg(pi,
					       RADIO_2056_RX_RSSI_MISC |
					       RADIO_2056_RX0);
			pi->rssical_cache.rssical_radio_regs_5G[1] =
				read_radio_reg(pi,
					       RADIO_2056_RX_RSSI_MISC |
					       RADIO_2056_RX1);
		}

		pi->rssical_cache.rssical_phyregs_5G[0] =
			read_phy_reg(pi, 0x1a6);
		pi->rssical_cache.rssical_phyregs_5G[1] =
			read_phy_reg(pi, 0x1ac);
		pi->rssical_cache.rssical_phyregs_5G[2] =
			read_phy_reg(pi, 0x1b2);
		pi->rssical_cache.rssical_phyregs_5G[3] =
			read_phy_reg(pi, 0x1b8);
		pi->rssical_cache.rssical_phyregs_5G[4] =
			read_phy_reg(pi, 0x1a4);
		pi->rssical_cache.rssical_phyregs_5G[5] =
			read_phy_reg(pi, 0x1aa);
		pi->rssical_cache.rssical_phyregs_5G[6] =
			read_phy_reg(pi, 0x1b0);
		pi->rssical_cache.rssical_phyregs_5G[7] =
			read_phy_reg(pi, 0x1b6);
		pi->rssical_cache.rssical_phyregs_5G[8] =
			read_phy_reg(pi, 0x1a5);
		pi->rssical_cache.rssical_phyregs_5G[9] =
			read_phy_reg(pi, 0x1ab);
		pi->rssical_cache.rssical_phyregs_5G[10] =
			read_phy_reg(pi, 0x1b1);
		pi->rssical_cache.rssical_phyregs_5G[11] =
			read_phy_reg(pi, 0x1b7);

		pi->nphy_rssical_chanspec_5G = pi->radio_chanspec;
	}

	wlc_phy_classifier_nphy(pi, (0x7 << 0), classif_state);
	wlc_phy_clip_det_nphy(pi, 1, clip_state);
}