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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_2__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int* tx_rx_cal_radio_saveregs; TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PHY_CORE_0 ; 
 int RADIO_2056_RX0 ; 
 int RADIO_2056_RX1 ; 
 int RADIO_2056_RX_LNAA_MASTER ; 
 int RADIO_2056_RX_LNAA_TUNE ; 
 int RADIO_2056_RX_LNAG_MASTER ; 
 int RADIO_2056_RX_LNAG_TUNE ; 
 int RADIO_2056_RX_RXIQCAL_RXMUX ; 
 int RADIO_2056_RX_RXSPARE2 ; 
 int RADIO_2056_TX0 ; 
 int RADIO_2056_TX1 ; 
 int RADIO_2056_TX_RXIQCAL_TXMUX ; 
 int RADIO_2056_TX_TXSPARE2 ; 
 int RADIO_2057_TX0_TXRXCOUPLE_2G_ATTEN ; 
 int RADIO_2057_TX0_TXRXCOUPLE_2G_PWRUP ; 
 int RADIO_2057_TX0_TXRXCOUPLE_5G_ATTEN ; 
 int RADIO_2057_TX0_TXRXCOUPLE_5G_PWRUP ; 
 int RADIO_2057_TX1_TXRXCOUPLE_2G_ATTEN ; 
 int RADIO_2057_TX1_TXRXCOUPLE_2G_PWRUP ; 
 int RADIO_2057_TX1_TXRXCOUPLE_5G_ATTEN ; 
 int RADIO_2057_TX1_TXRXCOUPLE_5G_PWRUP ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int,int,int) ; 
 void* read_radio_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_rxcal_radio_setup_nphy(struct brcms_phy *pi, u8 rx_core)
{
	u16 offtune_val;
	u16 bias_g = 0;
	u16 bias_a = 0;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		if (rx_core == PHY_CORE_0) {
			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				pi->tx_rx_cal_radio_saveregs[0] =
					read_radio_reg(pi,
					    RADIO_2057_TX0_TXRXCOUPLE_5G_PWRUP);
				pi->tx_rx_cal_radio_saveregs[1] =
					read_radio_reg(pi,
					    RADIO_2057_TX0_TXRXCOUPLE_5G_ATTEN);

				write_radio_reg(pi,
					RADIO_2057_TX0_TXRXCOUPLE_5G_PWRUP,
					0x3);
				write_radio_reg(pi,
					RADIO_2057_TX0_TXRXCOUPLE_5G_ATTEN,
					0xaf);

			} else {
				pi->tx_rx_cal_radio_saveregs[0] =
					read_radio_reg(pi,
					    RADIO_2057_TX0_TXRXCOUPLE_2G_PWRUP);
				pi->tx_rx_cal_radio_saveregs[1] =
					read_radio_reg(pi,
					    RADIO_2057_TX0_TXRXCOUPLE_2G_ATTEN);

				write_radio_reg(
					pi,
					RADIO_2057_TX0_TXRXCOUPLE_2G_PWRUP,
					0x3);
				write_radio_reg(
					pi,
					RADIO_2057_TX0_TXRXCOUPLE_2G_ATTEN,
					0x7f);
			}

		} else {
			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				pi->tx_rx_cal_radio_saveregs[0] =
					read_radio_reg(pi,
					    RADIO_2057_TX1_TXRXCOUPLE_5G_PWRUP);
				pi->tx_rx_cal_radio_saveregs[1] =
					read_radio_reg(pi,
					    RADIO_2057_TX1_TXRXCOUPLE_5G_ATTEN);

				write_radio_reg(
					pi,
					RADIO_2057_TX1_TXRXCOUPLE_5G_PWRUP,
					0x3);
				write_radio_reg(
					pi,
					RADIO_2057_TX1_TXRXCOUPLE_5G_ATTEN,
					0xaf);

			} else {
				pi->tx_rx_cal_radio_saveregs[0] =
					read_radio_reg(pi,
					    RADIO_2057_TX1_TXRXCOUPLE_2G_PWRUP);
				pi->tx_rx_cal_radio_saveregs[1] =
					read_radio_reg(pi,
					    RADIO_2057_TX1_TXRXCOUPLE_2G_ATTEN);

				write_radio_reg(pi,
					RADIO_2057_TX1_TXRXCOUPLE_2G_PWRUP,
					0x3);
				write_radio_reg(pi,
					RADIO_2057_TX1_TXRXCOUPLE_2G_ATTEN,
					0x7f);
			}
		}

	} else {
		if (rx_core == PHY_CORE_0) {
			pi->tx_rx_cal_radio_saveregs[0] =
				read_radio_reg(pi,
					       RADIO_2056_TX_RXIQCAL_TXMUX |
					       RADIO_2056_TX1);
			pi->tx_rx_cal_radio_saveregs[1] =
				read_radio_reg(pi,
					       RADIO_2056_RX_RXIQCAL_RXMUX |
					       RADIO_2056_RX0);

			if (pi->pubpi.radiorev >= 5) {
				pi->tx_rx_cal_radio_saveregs[2] =
					read_radio_reg(pi,
						       RADIO_2056_RX_RXSPARE2 |
						       RADIO_2056_RX0);
				pi->tx_rx_cal_radio_saveregs[3] =
					read_radio_reg(pi,
						       RADIO_2056_TX_TXSPARE2 |
						       RADIO_2056_TX1);
			}

			if (CHSPEC_IS5G(pi->radio_chanspec)) {

				if (pi->pubpi.radiorev >= 5) {
					pi->tx_rx_cal_radio_saveregs[4] =
						read_radio_reg(pi,
						      RADIO_2056_RX_LNAA_MASTER
						      | RADIO_2056_RX0);

					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAA_MASTER
						| RADIO_2056_RX0, 0x40);

					write_radio_reg(pi,
						RADIO_2056_TX_TXSPARE2 |
						RADIO_2056_TX1, bias_a);

					write_radio_reg(pi,
						RADIO_2056_RX_RXSPARE2 |
						RADIO_2056_RX0, bias_a);
				} else {
					pi->tx_rx_cal_radio_saveregs[4] =
						read_radio_reg(pi,
							RADIO_2056_RX_LNAA_TUNE
							| RADIO_2056_RX0);

					offtune_val =
						(pi->tx_rx_cal_radio_saveregs
						 [2] & 0xF0) >> 8;
					offtune_val =
						(offtune_val <= 0x7) ? 0xF : 0;

					mod_radio_reg(pi,
						      RADIO_2056_RX_LNAA_TUNE |
						      RADIO_2056_RX0, 0xF0,
						      (offtune_val << 8));
				}

				write_radio_reg(pi,
						RADIO_2056_TX_RXIQCAL_TXMUX |
						RADIO_2056_TX1, 0x9);
				write_radio_reg(pi,
						RADIO_2056_RX_RXIQCAL_RXMUX |
						RADIO_2056_RX0, 0x9);
			} else {
				if (pi->pubpi.radiorev >= 5) {
					pi->tx_rx_cal_radio_saveregs[4] =
						read_radio_reg(
						      pi,
						      RADIO_2056_RX_LNAG_MASTER
						    | RADIO_2056_RX0);

					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAG_MASTER
						| RADIO_2056_RX0, 0x40);

					write_radio_reg(
						pi,
						RADIO_2056_TX_TXSPARE2
						|
						RADIO_2056_TX1, bias_g);

					write_radio_reg(
						pi,
						RADIO_2056_RX_RXSPARE2
						|
						RADIO_2056_RX0, bias_g);

				} else {
					pi->tx_rx_cal_radio_saveregs[4] =
						read_radio_reg(
							pi,
							RADIO_2056_RX_LNAG_TUNE
							| RADIO_2056_RX0);

					offtune_val =
						(pi->
						 tx_rx_cal_radio_saveregs[2] &
						 0xF0) >> 8;
					offtune_val =
						(offtune_val <= 0x7) ? 0xF : 0;

					mod_radio_reg(pi,
						      RADIO_2056_RX_LNAG_TUNE |
						      RADIO_2056_RX0, 0xF0,
						      (offtune_val << 8));
				}

				write_radio_reg(pi,
						RADIO_2056_TX_RXIQCAL_TXMUX |
						RADIO_2056_TX1, 0x6);
				write_radio_reg(pi,
						RADIO_2056_RX_RXIQCAL_RXMUX |
						RADIO_2056_RX0, 0x6);
			}

		} else {
			pi->tx_rx_cal_radio_saveregs[0] =
				read_radio_reg(pi,
					       RADIO_2056_TX_RXIQCAL_TXMUX |
					       RADIO_2056_TX0);
			pi->tx_rx_cal_radio_saveregs[1] =
				read_radio_reg(pi,
					       RADIO_2056_RX_RXIQCAL_RXMUX |
					       RADIO_2056_RX1);

			if (pi->pubpi.radiorev >= 5) {
				pi->tx_rx_cal_radio_saveregs[2] =
					read_radio_reg(pi,
						       RADIO_2056_RX_RXSPARE2 |
						       RADIO_2056_RX1);
				pi->tx_rx_cal_radio_saveregs[3] =
					read_radio_reg(pi,
						       RADIO_2056_TX_TXSPARE2 |
						       RADIO_2056_TX0);
			}

			if (CHSPEC_IS5G(pi->radio_chanspec)) {

				if (pi->pubpi.radiorev >= 5) {
					pi->tx_rx_cal_radio_saveregs[4] =
						read_radio_reg(
						       pi,
						       RADIO_2056_RX_LNAA_MASTER
						       | RADIO_2056_RX1);

					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAA_MASTER |
						RADIO_2056_RX1, 0x40);

					write_radio_reg(
						pi,
						RADIO_2056_TX_TXSPARE2
						|
						RADIO_2056_TX0, bias_a);

					write_radio_reg(
						pi,
						RADIO_2056_RX_RXSPARE2
						|
						RADIO_2056_RX1, bias_a);
				} else {
					pi->tx_rx_cal_radio_saveregs[4] =
						read_radio_reg(
							pi,
							RADIO_2056_RX_LNAA_TUNE
							| RADIO_2056_RX1);

					offtune_val =
						(pi->
						 tx_rx_cal_radio_saveregs[2] &
						 0xF0) >> 8;
					offtune_val =
						(offtune_val <= 0x7) ? 0xF : 0;

					mod_radio_reg(pi,
						      RADIO_2056_RX_LNAA_TUNE |
						      RADIO_2056_RX1, 0xF0,
						      (offtune_val << 8));
				}

				write_radio_reg(pi,
						RADIO_2056_TX_RXIQCAL_TXMUX |
						RADIO_2056_TX0, 0x9);
				write_radio_reg(pi,
						RADIO_2056_RX_RXIQCAL_RXMUX |
						RADIO_2056_RX1, 0x9);
			} else {
				if (pi->pubpi.radiorev >= 5) {
					pi->tx_rx_cal_radio_saveregs[4] =
						read_radio_reg(
						      pi,
						      RADIO_2056_RX_LNAG_MASTER
						    | RADIO_2056_RX1);

					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAG_MASTER
						| RADIO_2056_RX1, 0x40);

					write_radio_reg(
						pi,
						RADIO_2056_TX_TXSPARE2
						|
						RADIO_2056_TX0, bias_g);

					write_radio_reg(
						pi,
						RADIO_2056_RX_RXSPARE2
						|
						RADIO_2056_RX1, bias_g);
				} else {
					pi->tx_rx_cal_radio_saveregs[4] =
						read_radio_reg(
							pi,
							RADIO_2056_RX_LNAG_TUNE
							| RADIO_2056_RX1);

					offtune_val =
						(pi->
						 tx_rx_cal_radio_saveregs[2] &
						 0xF0) >> 8;
					offtune_val =
						(offtune_val <= 0x7) ? 0xF : 0;

					mod_radio_reg(pi,
						      RADIO_2056_RX_LNAG_TUNE |
						      RADIO_2056_RX1, 0xF0,
						      (offtune_val << 8));
				}

				write_radio_reg(pi,
						RADIO_2056_TX_RXIQCAL_TXMUX |
						RADIO_2056_TX0, 0x6);
				write_radio_reg(pi,
						RADIO_2056_RX_RXIQCAL_RXMUX |
						RADIO_2056_RX1, 0x6);
			}
		}
	}
}