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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct brcms_phy {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int read_phy_reg (struct brcms_phy*,int) ; 

__attribute__((used)) static u32 wlc_phy_txpower_est_power_nphy(struct brcms_phy *pi)
{
	s16 tx0_status, tx1_status;
	u16 estPower1, estPower2;
	u8 pwr0, pwr1, adj_pwr0, adj_pwr1;
	u32 est_pwr;

	estPower1 = read_phy_reg(pi, 0x118);
	estPower2 = read_phy_reg(pi, 0x119);

	if ((estPower1 & (0x1 << 8)) == (0x1 << 8))
		pwr0 = (u8) (estPower1 & (0xff << 0)) >> 0;
	else
		pwr0 = 0x80;

	if ((estPower2 & (0x1 << 8)) == (0x1 << 8))
		pwr1 = (u8) (estPower2 & (0xff << 0)) >> 0;
	else
		pwr1 = 0x80;

	tx0_status = read_phy_reg(pi, 0x1ed);
	tx1_status = read_phy_reg(pi, 0x1ee);

	if ((tx0_status & (0x1 << 15)) == (0x1 << 15))
		adj_pwr0 = (u8) (tx0_status & (0xff << 0)) >> 0;
	else
		adj_pwr0 = 0x80;
	if ((tx1_status & (0x1 << 15)) == (0x1 << 15))
		adj_pwr1 = (u8) (tx1_status & (0xff << 0)) >> 0;
	else
		adj_pwr1 = 0x80;

	est_pwr = (u32) ((pwr0 << 24) | (pwr1 << 16) | (adj_pwr0 << 8) |
			 adj_pwr1);

	return est_pwr;
}