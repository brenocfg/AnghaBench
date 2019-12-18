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
typedef  size_t uint ;
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_2__ pubpi; TYPE_1__* sh; scalar_t__ phy_5g_pwrgain; int /*<<< orphan*/  radio_chanspec; } ;
typedef  int s16 ;
struct TYPE_3__ {int boardflags2; int boardtype; int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
 int BFL2_SKWRKFEM_BRD ; 
 int /*<<< orphan*/  BRCM_BAND_ALL ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MHF3 ; 
 int /*<<< orphan*/  MHF3_NPHY_MLADV_WAR ; 
 int NPHY_FORCESIG_DECODEGATEDCLKS ; 
 int NPHY_MLenable ; 
#define  NPHY_RFSEQ_CMD_CLR_HIQ_DIS 134 
#define  NPHY_RFSEQ_CMD_EXT_PA 133 
#define  NPHY_RFSEQ_CMD_NOP 132 
#define  NPHY_RFSEQ_CMD_RXG_FBW 131 
#define  NPHY_RFSEQ_CMD_RXPD_TXPD 130 
#define  NPHY_RFSEQ_CMD_TR_SWITCH 129 
#define  NPHY_RFSEQ_CMD_TX_GAIN 128 
 int /*<<< orphan*/  NPHY_RFSEQ_RX2TX ; 
 int /*<<< orphan*/  NPHY_RFSEQ_TX2RX ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_LT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_TX_RF_SPARE ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_TX_RF_SPARE ; 
 int /*<<< orphan*/  and_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlapi_bmac_mhf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_set_rfseq_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int const*,int const*,size_t) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_workarounds_nphy_gainctrl (struct brcms_phy*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_workarounds_nphy_rev1(struct brcms_phy *pi)
{
	static const u8 rfseq_rx2tx_events[] = {
		NPHY_RFSEQ_CMD_NOP,
		NPHY_RFSEQ_CMD_RXG_FBW,
		NPHY_RFSEQ_CMD_TR_SWITCH,
		NPHY_RFSEQ_CMD_CLR_HIQ_DIS,
		NPHY_RFSEQ_CMD_RXPD_TXPD,
		NPHY_RFSEQ_CMD_TX_GAIN,
		NPHY_RFSEQ_CMD_EXT_PA
	};
	u8 rfseq_rx2tx_dlys[] = { 8, 6, 6, 2, 4, 60, 1 };
	static const u8 rfseq_tx2rx_events[] = {
		NPHY_RFSEQ_CMD_NOP,
		NPHY_RFSEQ_CMD_EXT_PA,
		NPHY_RFSEQ_CMD_TX_GAIN,
		NPHY_RFSEQ_CMD_RXPD_TXPD,
		NPHY_RFSEQ_CMD_TR_SWITCH,
		NPHY_RFSEQ_CMD_RXG_FBW,
		NPHY_RFSEQ_CMD_CLR_HIQ_DIS
	};
	static const u8 rfseq_tx2rx_dlys[] = { 8, 6, 2, 4, 4, 6, 1 };
	s16 alpha0, alpha1, alpha2;
	s16 beta0, beta1, beta2;
	u16 regval;

	if (pi->sh->boardflags2 & BFL2_SKWRKFEM_BRD ||
	    (pi->sh->boardtype == 0x8b)) {
		uint i;
		u8 war_dlys[] = { 1, 6, 6, 2, 4, 20, 1 };
		for (i = 0; i < ARRAY_SIZE(rfseq_rx2tx_dlys); i++)
			rfseq_rx2tx_dlys[i] = war_dlys[i];
	}

	if (CHSPEC_IS5G(pi->radio_chanspec) && pi->phy_5g_pwrgain) {
		and_radio_reg(pi, RADIO_2055_CORE1_TX_RF_SPARE, 0xf7);
		and_radio_reg(pi, RADIO_2055_CORE2_TX_RF_SPARE, 0xf7);
	} else {
		or_radio_reg(pi, RADIO_2055_CORE1_TX_RF_SPARE, 0x8);
		or_radio_reg(pi, RADIO_2055_CORE2_TX_RF_SPARE, 0x8);
	}

	regval = 0x000a;
	wlc_phy_table_write_nphy(pi, 8, 1, 0, 16, &regval);
	wlc_phy_table_write_nphy(pi, 8, 1, 0x10, 16, &regval);

	if (NREV_LT(pi->pubpi.phy_rev, 3)) {
		regval = 0xcdaa;
		wlc_phy_table_write_nphy(pi, 8, 1, 0x02, 16, &regval);
		wlc_phy_table_write_nphy(pi, 8, 1, 0x12, 16, &regval);
	}

	if (NREV_LT(pi->pubpi.phy_rev, 2)) {
		regval = 0x0000;
		wlc_phy_table_write_nphy(pi, 8, 1, 0x08, 16, &regval);
		wlc_phy_table_write_nphy(pi, 8, 1, 0x18, 16, &regval);

		regval = 0x7aab;
		wlc_phy_table_write_nphy(pi, 8, 1, 0x07, 16, &regval);
		wlc_phy_table_write_nphy(pi, 8, 1, 0x17, 16, &regval);

		regval = 0x0800;
		wlc_phy_table_write_nphy(pi, 8, 1, 0x06, 16, &regval);
		wlc_phy_table_write_nphy(pi, 8, 1, 0x16, 16, &regval);
	}

	write_phy_reg(pi, 0xf8, 0x02d8);
	write_phy_reg(pi, 0xf9, 0x0301);
	write_phy_reg(pi, 0xfa, 0x02d8);
	write_phy_reg(pi, 0xfb, 0x0301);

	wlc_phy_set_rfseq_nphy(pi, NPHY_RFSEQ_RX2TX, rfseq_rx2tx_events,
			       rfseq_rx2tx_dlys,
			       ARRAY_SIZE(rfseq_rx2tx_events));

	wlc_phy_set_rfseq_nphy(pi, NPHY_RFSEQ_TX2RX, rfseq_tx2rx_events,
			       rfseq_tx2rx_dlys,
			       ARRAY_SIZE(rfseq_tx2rx_events));

	wlc_phy_workarounds_nphy_gainctrl(pi);

	if (NREV_LT(pi->pubpi.phy_rev, 2)) {

		if (read_phy_reg(pi, 0xa0) & NPHY_MLenable)
			wlapi_bmac_mhf(pi->sh->physhim, MHF3,
				       MHF3_NPHY_MLADV_WAR,
				       MHF3_NPHY_MLADV_WAR, BRCM_BAND_ALL);

	} else if (NREV_IS(pi->pubpi.phy_rev, 2)) {
		write_phy_reg(pi, 0x1e3, 0x0);
		write_phy_reg(pi, 0x1e4, 0x0);
	}

	if (NREV_LT(pi->pubpi.phy_rev, 2))
		mod_phy_reg(pi, 0x90, (0x1 << 7), 0);

	alpha0 = 293;
	alpha1 = 435;
	alpha2 = 261;
	beta0 = 366;
	beta1 = 205;
	beta2 = 32;
	write_phy_reg(pi, 0x145, alpha0);
	write_phy_reg(pi, 0x146, alpha1);
	write_phy_reg(pi, 0x147, alpha2);
	write_phy_reg(pi, 0x148, beta0);
	write_phy_reg(pi, 0x149, beta1);
	write_phy_reg(pi, 0x14a, beta2);

	if (NREV_LT(pi->pubpi.phy_rev, 3)) {
		mod_phy_reg(pi, 0x142, (0xf << 12), 0);

		write_phy_reg(pi, 0x192, 0xb5);
		write_phy_reg(pi, 0x193, 0xa4);
		write_phy_reg(pi, 0x194, 0x0);
	}

	if (NREV_IS(pi->pubpi.phy_rev, 2))
		mod_phy_reg(pi, 0x221,
			    NPHY_FORCESIG_DECODEGATEDCLKS,
			    NPHY_FORCESIG_DECODEGATEDCLKS);
}