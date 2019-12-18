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
struct TYPE_2__ {int radiorev; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/ * tx_rx_cal_radio_saveregs; TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;

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
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_rxcal_radio_cleanup_nphy(struct brcms_phy *pi, u8 rx_core)
{
	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		if (rx_core == PHY_CORE_0) {
			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				write_radio_reg(
					pi,
					RADIO_2057_TX0_TXRXCOUPLE_5G_PWRUP,
					pi->
					tx_rx_cal_radio_saveregs[0]);
				write_radio_reg(
					pi,
					RADIO_2057_TX0_TXRXCOUPLE_5G_ATTEN,
					pi->
					tx_rx_cal_radio_saveregs[1]);

			} else {
				write_radio_reg(
					pi,
					RADIO_2057_TX0_TXRXCOUPLE_2G_PWRUP,
					pi->
					tx_rx_cal_radio_saveregs[0]);
				write_radio_reg(
					pi,
					RADIO_2057_TX0_TXRXCOUPLE_2G_ATTEN,
					pi->
					tx_rx_cal_radio_saveregs[1]);
			}

		} else {
			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				write_radio_reg(
					pi,
					RADIO_2057_TX1_TXRXCOUPLE_5G_PWRUP,
					pi->
					tx_rx_cal_radio_saveregs[0]);
				write_radio_reg(
					pi,
					RADIO_2057_TX1_TXRXCOUPLE_5G_ATTEN,
					pi->
					tx_rx_cal_radio_saveregs[1]);

			} else {
				write_radio_reg(
					pi,
					RADIO_2057_TX1_TXRXCOUPLE_2G_PWRUP,
					pi->
					tx_rx_cal_radio_saveregs[0]);
				write_radio_reg(
					pi,
					RADIO_2057_TX1_TXRXCOUPLE_2G_ATTEN,
					pi->
					tx_rx_cal_radio_saveregs[1]);
			}
		}

	} else {
		if (rx_core == PHY_CORE_0) {
			write_radio_reg(pi,
					RADIO_2056_TX_RXIQCAL_TXMUX |
					RADIO_2056_TX1,
					pi->tx_rx_cal_radio_saveregs[0]);

			write_radio_reg(pi,
					RADIO_2056_RX_RXIQCAL_RXMUX |
					RADIO_2056_RX0,
					pi->tx_rx_cal_radio_saveregs[1]);

			if (pi->pubpi.radiorev >= 5) {
				write_radio_reg(pi,
						RADIO_2056_RX_RXSPARE2 |
						RADIO_2056_RX0,
						pi->
						tx_rx_cal_radio_saveregs[2]);

				write_radio_reg(pi,
						RADIO_2056_TX_TXSPARE2 |
						RADIO_2056_TX1,
						pi->
						tx_rx_cal_radio_saveregs[3]);
			}

			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				if (pi->pubpi.radiorev >= 5)
					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAA_MASTER
						| RADIO_2056_RX0,
						pi->
						tx_rx_cal_radio_saveregs
						[4]);
				else
					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAA_TUNE
						| RADIO_2056_RX0,
						pi->
						tx_rx_cal_radio_saveregs
						[4]);
			} else {
				if (pi->pubpi.radiorev >= 5)
					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAG_MASTER
						| RADIO_2056_RX0,
						pi->
						tx_rx_cal_radio_saveregs
						[4]);
				else
					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAG_TUNE
						| RADIO_2056_RX0,
						pi->
						tx_rx_cal_radio_saveregs
						[4]);
			}

		} else {
			write_radio_reg(pi,
					RADIO_2056_TX_RXIQCAL_TXMUX |
					RADIO_2056_TX0,
					pi->tx_rx_cal_radio_saveregs[0]);

			write_radio_reg(pi,
					RADIO_2056_RX_RXIQCAL_RXMUX |
					RADIO_2056_RX1,
					pi->tx_rx_cal_radio_saveregs[1]);

			if (pi->pubpi.radiorev >= 5) {
				write_radio_reg(pi,
						RADIO_2056_RX_RXSPARE2 |
						RADIO_2056_RX1,
						pi->
						tx_rx_cal_radio_saveregs[2]);

				write_radio_reg(pi,
						RADIO_2056_TX_TXSPARE2 |
						RADIO_2056_TX0,
						pi->
						tx_rx_cal_radio_saveregs[3]);
			}

			if (CHSPEC_IS5G(pi->radio_chanspec)) {
				if (pi->pubpi.radiorev >= 5)
					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAA_MASTER
						| RADIO_2056_RX1,
						pi->
						tx_rx_cal_radio_saveregs
						[4]);
				else
					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAA_TUNE
						| RADIO_2056_RX1,
						pi->
						tx_rx_cal_radio_saveregs
						[4]);
			} else {
				if (pi->pubpi.radiorev >= 5)
					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAG_MASTER
						| RADIO_2056_RX1,
						pi->
						tx_rx_cal_radio_saveregs
						[4]);
				else
					write_radio_reg(
						pi,
						RADIO_2056_RX_LNAG_TUNE
						| RADIO_2056_RX1,
						pi->
						tx_rx_cal_radio_saveregs
						[4]);
			}
		}
	}
}