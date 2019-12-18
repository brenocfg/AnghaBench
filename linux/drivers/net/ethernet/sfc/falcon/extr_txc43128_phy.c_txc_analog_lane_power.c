#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ef4_nic {int phy_mode; } ;

/* Variables and functions */
 int PHY_MODE_LOW_POWER ; 
 int /*<<< orphan*/  TXC_ALRGS_ARXCTL ; 
 int /*<<< orphan*/  TXC_ALRGS_ATXCTL ; 
 int TXC_ARXCTL_RXPD0_LBN ; 
 int TXC_ARXCTL_RXPD1_LBN ; 
 int TXC_ARXCTL_RXPD2_LBN ; 
 int TXC_ARXCTL_RXPD3_LBN ; 
 int TXC_ATXCTL_TXPD0_LBN ; 
 int TXC_ATXCTL_TXPD1_LBN ; 
 int TXC_ATXCTL_TXPD2_LBN ; 
 int TXC_ATXCTL_TXPD3_LBN ; 
 int ef4_mdio_read (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_mdio_write (struct ef4_nic*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void txc_analog_lane_power(struct ef4_nic *efx, int mmd)
{
	int txpd = (1 << TXC_ATXCTL_TXPD3_LBN) | (1 << TXC_ATXCTL_TXPD2_LBN)
		| (1 << TXC_ATXCTL_TXPD1_LBN) | (1 << TXC_ATXCTL_TXPD0_LBN);
	int rxpd = (1 << TXC_ARXCTL_RXPD3_LBN) | (1 << TXC_ARXCTL_RXPD2_LBN)
		| (1 << TXC_ARXCTL_RXPD1_LBN) | (1 << TXC_ARXCTL_RXPD0_LBN);
	int txctl = ef4_mdio_read(efx, mmd, TXC_ALRGS_ATXCTL);
	int rxctl = ef4_mdio_read(efx, mmd, TXC_ALRGS_ARXCTL);

	if (!(efx->phy_mode & PHY_MODE_LOW_POWER)) {
		txctl &= ~txpd;
		rxctl &= ~rxpd;
	} else {
		txctl |= txpd;
		rxctl |= rxpd;
	}

	ef4_mdio_write(efx, mmd, TXC_ALRGS_ATXCTL, txctl);
	ef4_mdio_write(efx, mmd, TXC_ALRGS_ARXCTL, rxctl);
}