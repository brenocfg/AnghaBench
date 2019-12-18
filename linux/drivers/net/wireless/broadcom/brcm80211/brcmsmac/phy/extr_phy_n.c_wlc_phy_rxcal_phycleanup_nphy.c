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
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/ * tx_rx_cal_phy_saveregs; TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PHY_CORE_0 ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_rxcal_phycleanup_nphy(struct brcms_phy *pi, u8 rx_core)
{

	write_phy_reg(pi, 0xa2, pi->tx_rx_cal_phy_saveregs[0]);
	write_phy_reg(pi, (rx_core == PHY_CORE_0) ? 0xa6 : 0xa7,
		      pi->tx_rx_cal_phy_saveregs[1]);
	write_phy_reg(pi, (rx_core == PHY_CORE_0) ? 0x8f : 0xa5,
		      pi->tx_rx_cal_phy_saveregs[2]);
	write_phy_reg(pi, 0x91, pi->tx_rx_cal_phy_saveregs[3]);
	write_phy_reg(pi, 0x92, pi->tx_rx_cal_phy_saveregs[4]);

	write_phy_reg(pi, 0x7a, pi->tx_rx_cal_phy_saveregs[5]);
	write_phy_reg(pi, 0x7d, pi->tx_rx_cal_phy_saveregs[6]);
	write_phy_reg(pi, 0xe7, pi->tx_rx_cal_phy_saveregs[7]);
	write_phy_reg(pi, 0xec, pi->tx_rx_cal_phy_saveregs[8]);
	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		write_phy_reg(pi, 0x342, pi->tx_rx_cal_phy_saveregs[11]);
		write_phy_reg(pi, 0x343, pi->tx_rx_cal_phy_saveregs[12]);
		write_phy_reg(pi, 0x346, pi->tx_rx_cal_phy_saveregs[13]);
		write_phy_reg(pi, 0x347, pi->tx_rx_cal_phy_saveregs[14]);
	}

	write_phy_reg(pi, 0x297, pi->tx_rx_cal_phy_saveregs[9]);
	write_phy_reg(pi, 0x29b, pi->tx_rx_cal_phy_saveregs[10]);
}