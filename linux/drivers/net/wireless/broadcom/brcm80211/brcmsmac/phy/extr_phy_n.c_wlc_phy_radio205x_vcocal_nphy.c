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
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RADIO_2056_SYN_PLL_MAST3 ; 
 int /*<<< orphan*/  RADIO_2056_SYN_PLL_VCOCAL12 ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_MISC_CAL_RESETN ; 
 int /*<<< orphan*/  RADIO_2057_RFPLL_MISC_EN ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

void wlc_phy_radio205x_vcocal_nphy(struct brcms_phy *pi)
{
	if (NREV_GE(pi->pubpi.phy_rev, 7)) {
		mod_radio_reg(pi, RADIO_2057_RFPLL_MISC_EN, 0x01, 0x0);
		mod_radio_reg(pi, RADIO_2057_RFPLL_MISC_CAL_RESETN, 0x04, 0x0);
		mod_radio_reg(pi, RADIO_2057_RFPLL_MISC_CAL_RESETN, 0x04,
			      (1 << 2));
		mod_radio_reg(pi, RADIO_2057_RFPLL_MISC_EN, 0x01, 0x01);
	} else if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		write_radio_reg(pi, RADIO_2056_SYN_PLL_VCOCAL12, 0x0);
		write_radio_reg(pi, RADIO_2056_SYN_PLL_MAST3, 0x38);
		write_radio_reg(pi, RADIO_2056_SYN_PLL_MAST3, 0x18);
		write_radio_reg(pi, RADIO_2056_SYN_PLL_MAST3, 0x38);
		write_radio_reg(pi, RADIO_2056_SYN_PLL_MAST3, 0x39);
	}

	udelay(300);
}