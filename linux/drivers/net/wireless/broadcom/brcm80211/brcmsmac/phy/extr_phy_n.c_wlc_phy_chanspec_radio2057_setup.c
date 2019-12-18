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
struct chan_info_nphy_radio2057_rev5 {int RF_vcocal_countval0; int RF_vcocal_countval1; int RF_rfpll_refmaster_sparextalsize; int RF_rfpll_loopfilter_r1; int RF_rfpll_loopfilter_c2; int RF_rfpll_loopfilter_c1; int RF_cp_kpd_idac; int RF_rfpll_mmd0; int RF_rfpll_mmd1; int RF_vcobuf_tune; int RF_logen_mx2g_tune; int RF_logen_indbuf2g_tune; int RF_txmix2g_tune_boost_pu_core0; int RF_pad2g_tune_pus_core0; int RF_lna2g_tune_core0; int RF_txmix2g_tune_boost_pu_core1; int RF_pad2g_tune_pus_core1; int RF_lna2g_tune_core1; } ;
struct chan_info_nphy_radio2057 {int RF_vcocal_countval0; int RF_vcocal_countval1; int RF_rfpll_refmaster_sparextalsize; int RF_rfpll_loopfilter_r1; int RF_rfpll_loopfilter_c2; int RF_rfpll_loopfilter_c1; int RF_cp_kpd_idac; int RF_rfpll_mmd0; int RF_rfpll_mmd1; int RF_vcobuf_tune; int RF_logen_mx2g_tune; int RF_logen_mx5g_tune; int RF_logen_indbuf2g_tune; int RF_logen_indbuf5g_tune; int RF_txmix2g_tune_boost_pu_core0; int RF_pad2g_tune_pus_core0; int RF_pga_boost_tune_core0; int RF_txmix5g_boost_tune_core0; int RF_pad5g_tune_misc_pus_core0; int RF_lna2g_tune_core0; int RF_lna5g_tune_core0; int RF_txmix2g_tune_boost_pu_core1; int RF_pad2g_tune_pus_core1; int RF_pga_boost_tune_core1; int RF_txmix5g_boost_tune_core1; int RF_pad5g_tune_misc_pus_core1; int RF_lna2g_tune_core1; int RF_lna5g_tune_core1; } ;
struct TYPE_2__ {int radiorev; } ;
struct brcms_phy {TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CORE ; 
 int /*<<< orphan*/  PAD2G_TUNE_PUS ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 int /*<<< orphan*/  RADIO_2057 ; 
 int /*<<< orphan*/  RADIO_2057_CP_KPD_IDAC ; 
 int /*<<< orphan*/  RADIO_2057_LNA2G_TUNE_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_LNA2G_TUNE_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_LNA5G_TUNE_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_LNA5G_TUNE_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_LOGEN_INDBUF2G_TUNE ; 
 int /*<<< orphan*/  RADIO_2057_LOGEN_INDBUF5G_TUNE ; 
 int /*<<< orphan*/  RADIO_2057_LOGEN_MX2G_TUNE ; 
 int /*<<< orphan*/  RADIO_2057_LOGEN_MX5G_TUNE ; 
 int /*<<< orphan*/  RADIO_2057_PAD2G_TUNE_PUS_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_PAD2G_TUNE_PUS_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_PAD5G_TUNE_MISC_PUS_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_PAD5G_TUNE_MISC_PUS_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_PGA_BOOST_TUNE_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_PGA_BOOST_TUNE_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_LOOPFILTER_C1 ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_LOOPFILTER_C2 ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_LOOPFILTER_R1 ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_MMD0 ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_MMD1 ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_REFMASTER_SPAREXTALSIZE ; 
 int /*<<< orphan*/  RADIO_2057_TXMIX2G_TUNE_BOOST_PU_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_TXMIX2G_TUNE_BOOST_PU_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_TXMIX5G_BOOST_TUNE_CORE0 ; 
 int /*<<< orphan*/  RADIO_2057_TXMIX5G_BOOST_TUNE_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_VCOBUF_TUNE ; 
 int /*<<< orphan*/  RADIO_2057_VCOCAL_COUNTVAL0 ; 
 int /*<<< orphan*/  RADIO_2057_VCOCAL_COUNTVAL1 ; 
 int /*<<< orphan*/  TXMIX2G_TUNE_BOOST_PU ; 
 int /*<<< orphan*/  WRITE_RADIO_REG4 (struct brcms_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wlc_phy_radio205x_vcocal_nphy (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wlc_phy_chanspec_radio2057_setup(
	struct brcms_phy *pi,
	const struct chan_info_nphy_radio2057 *ci,
	const struct chan_info_nphy_radio2057_rev5 *
	ci2)
{
	int coreNum;
	u16 txmix2g_tune_boost_pu = 0;
	u16 pad2g_tune_pus = 0;

	if (pi->pubpi.radiorev == 5) {

		write_radio_reg(pi,
				RADIO_2057_VCOCAL_COUNTVAL0,
				ci2->RF_vcocal_countval0);
		write_radio_reg(pi, RADIO_2057_VCOCAL_COUNTVAL1,
				ci2->RF_vcocal_countval1);
		write_radio_reg(pi, RADIO_2057_RFPLL_REFMASTER_SPAREXTALSIZE,
				ci2->RF_rfpll_refmaster_sparextalsize);
		write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_R1,
				ci2->RF_rfpll_loopfilter_r1);
		write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C2,
				ci2->RF_rfpll_loopfilter_c2);
		write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C1,
				ci2->RF_rfpll_loopfilter_c1);
		write_radio_reg(pi, RADIO_2057_CP_KPD_IDAC,
				ci2->RF_cp_kpd_idac);
		write_radio_reg(pi, RADIO_2057_RFPLL_MMD0, ci2->RF_rfpll_mmd0);
		write_radio_reg(pi, RADIO_2057_RFPLL_MMD1, ci2->RF_rfpll_mmd1);
		write_radio_reg(pi,
				RADIO_2057_VCOBUF_TUNE, ci2->RF_vcobuf_tune);
		write_radio_reg(pi,
				RADIO_2057_LOGEN_MX2G_TUNE,
				ci2->RF_logen_mx2g_tune);
		write_radio_reg(pi, RADIO_2057_LOGEN_INDBUF2G_TUNE,
				ci2->RF_logen_indbuf2g_tune);

		write_radio_reg(pi,
				RADIO_2057_TXMIX2G_TUNE_BOOST_PU_CORE0,
				ci2->RF_txmix2g_tune_boost_pu_core0);
		write_radio_reg(pi,
				RADIO_2057_PAD2G_TUNE_PUS_CORE0,
				ci2->RF_pad2g_tune_pus_core0);
		write_radio_reg(pi, RADIO_2057_LNA2G_TUNE_CORE0,
				ci2->RF_lna2g_tune_core0);

		write_radio_reg(pi,
				RADIO_2057_TXMIX2G_TUNE_BOOST_PU_CORE1,
				ci2->RF_txmix2g_tune_boost_pu_core1);
		write_radio_reg(pi,
				RADIO_2057_PAD2G_TUNE_PUS_CORE1,
				ci2->RF_pad2g_tune_pus_core1);
		write_radio_reg(pi, RADIO_2057_LNA2G_TUNE_CORE1,
				ci2->RF_lna2g_tune_core1);

	} else {

		write_radio_reg(pi,
				RADIO_2057_VCOCAL_COUNTVAL0,
				ci->RF_vcocal_countval0);
		write_radio_reg(pi, RADIO_2057_VCOCAL_COUNTVAL1,
				ci->RF_vcocal_countval1);
		write_radio_reg(pi, RADIO_2057_RFPLL_REFMASTER_SPAREXTALSIZE,
				ci->RF_rfpll_refmaster_sparextalsize);
		write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_R1,
				ci->RF_rfpll_loopfilter_r1);
		write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C2,
				ci->RF_rfpll_loopfilter_c2);
		write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C1,
				ci->RF_rfpll_loopfilter_c1);
		write_radio_reg(pi, RADIO_2057_CP_KPD_IDAC, ci->RF_cp_kpd_idac);
		write_radio_reg(pi, RADIO_2057_RFPLL_MMD0, ci->RF_rfpll_mmd0);
		write_radio_reg(pi, RADIO_2057_RFPLL_MMD1, ci->RF_rfpll_mmd1);
		write_radio_reg(pi, RADIO_2057_VCOBUF_TUNE, ci->RF_vcobuf_tune);
		write_radio_reg(pi,
				RADIO_2057_LOGEN_MX2G_TUNE,
				ci->RF_logen_mx2g_tune);
		write_radio_reg(pi, RADIO_2057_LOGEN_MX5G_TUNE,
				ci->RF_logen_mx5g_tune);
		write_radio_reg(pi, RADIO_2057_LOGEN_INDBUF2G_TUNE,
				ci->RF_logen_indbuf2g_tune);
		write_radio_reg(pi, RADIO_2057_LOGEN_INDBUF5G_TUNE,
				ci->RF_logen_indbuf5g_tune);

		write_radio_reg(pi,
				RADIO_2057_TXMIX2G_TUNE_BOOST_PU_CORE0,
				ci->RF_txmix2g_tune_boost_pu_core0);
		write_radio_reg(pi,
				RADIO_2057_PAD2G_TUNE_PUS_CORE0,
				ci->RF_pad2g_tune_pus_core0);
		write_radio_reg(pi, RADIO_2057_PGA_BOOST_TUNE_CORE0,
				ci->RF_pga_boost_tune_core0);
		write_radio_reg(pi, RADIO_2057_TXMIX5G_BOOST_TUNE_CORE0,
				ci->RF_txmix5g_boost_tune_core0);
		write_radio_reg(pi, RADIO_2057_PAD5G_TUNE_MISC_PUS_CORE0,
				ci->RF_pad5g_tune_misc_pus_core0);
		write_radio_reg(pi, RADIO_2057_LNA2G_TUNE_CORE0,
				ci->RF_lna2g_tune_core0);
		write_radio_reg(pi, RADIO_2057_LNA5G_TUNE_CORE0,
				ci->RF_lna5g_tune_core0);

		write_radio_reg(pi,
				RADIO_2057_TXMIX2G_TUNE_BOOST_PU_CORE1,
				ci->RF_txmix2g_tune_boost_pu_core1);
		write_radio_reg(pi,
				RADIO_2057_PAD2G_TUNE_PUS_CORE1,
				ci->RF_pad2g_tune_pus_core1);
		write_radio_reg(pi, RADIO_2057_PGA_BOOST_TUNE_CORE1,
				ci->RF_pga_boost_tune_core1);
		write_radio_reg(pi, RADIO_2057_TXMIX5G_BOOST_TUNE_CORE1,
				ci->RF_txmix5g_boost_tune_core1);
		write_radio_reg(pi, RADIO_2057_PAD5G_TUNE_MISC_PUS_CORE1,
				ci->RF_pad5g_tune_misc_pus_core1);
		write_radio_reg(pi, RADIO_2057_LNA2G_TUNE_CORE1,
				ci->RF_lna2g_tune_core1);
		write_radio_reg(pi, RADIO_2057_LNA5G_TUNE_CORE1,
				ci->RF_lna5g_tune_core1);
	}

	if ((pi->pubpi.radiorev <= 4) || (pi->pubpi.radiorev == 6)) {

		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_R1,
					0x3f);
			write_radio_reg(pi, RADIO_2057_CP_KPD_IDAC, 0x3f);
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C1,
					0x8);
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C2,
					0x8);
		} else {
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_R1,
					0x1f);
			write_radio_reg(pi, RADIO_2057_CP_KPD_IDAC, 0x3f);
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C1,
					0x8);
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C2,
					0x8);
		}
	} else if ((pi->pubpi.radiorev == 5) || (pi->pubpi.radiorev == 7) ||
		   (pi->pubpi.radiorev == 8)) {

		if (CHSPEC_IS2G(pi->radio_chanspec)) {
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_R1,
					0x1b);
			write_radio_reg(pi, RADIO_2057_CP_KPD_IDAC, 0x30);
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C1,
					0xa);
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C2,
					0xa);
		} else {
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_R1,
					0x1f);
			write_radio_reg(pi, RADIO_2057_CP_KPD_IDAC, 0x3f);
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C1,
					0x8);
			write_radio_reg(pi, RADIO_2057_RFPLL_LOOPFILTER_C2,
					0x8);
		}

	}

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		if (PHY_IPA(pi)) {
			if (pi->pubpi.radiorev == 3)
				txmix2g_tune_boost_pu = 0x6b;

			if (pi->pubpi.radiorev == 5)
				pad2g_tune_pus = 0x73;

		} else {
			if (pi->pubpi.radiorev != 5) {
				pad2g_tune_pus = 0x3;

				txmix2g_tune_boost_pu = 0x61;
			}
		}

		for (coreNum = 0; coreNum <= 1; coreNum++) {

			if (txmix2g_tune_boost_pu != 0)
				WRITE_RADIO_REG4(pi, RADIO_2057, CORE, coreNum,
						 TXMIX2G_TUNE_BOOST_PU,
						 txmix2g_tune_boost_pu);

			if (pad2g_tune_pus != 0)
				WRITE_RADIO_REG4(pi, RADIO_2057, CORE, coreNum,
						 PAD2G_TUNE_PUS,
						 pad2g_tune_pus);
		}
	}

	udelay(50);

	wlc_phy_radio205x_vcocal_nphy(pi);
}