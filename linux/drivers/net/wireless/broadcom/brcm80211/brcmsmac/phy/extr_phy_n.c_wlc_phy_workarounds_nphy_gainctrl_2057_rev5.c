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
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; } ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS20 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_TBL_ID_GAIN1 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_GAIN2 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_GAINBITS1 ; 
 int /*<<< orphan*/  NPHY_TBL_ID_GAINBITS2 ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_phy_workarounds_nphy_gainctrl_2057_rev5(struct brcms_phy *pi)
{
	s8 lna1_gain_db[] = { 8, 13, 17, 22 };
	s8 lna2_gain_db[] = { -2, 7, 11, 15 };
	s8 tia_gain_db[] = { -4, -1, 2, 5, 5, 5, 5, 5, 5, 5 };
	s8 tia_gainbits[] = {
		0x0, 0x01, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 };

	mod_phy_reg(pi, 0x1c, (0x1 << 13), (1 << 13));
	mod_phy_reg(pi, 0x32, (0x1 << 13), (1 << 13));

	mod_phy_reg(pi, 0x289, (0xff << 0), (0x46 << 0));

	mod_phy_reg(pi, 0x283, (0xff << 0), (0x3c << 0));
	mod_phy_reg(pi, 0x280, (0xff << 0), (0x3c << 0));

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 4, 0x8, 8,
				 lna1_gain_db);
	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 4, 0x8, 8,
				 lna1_gain_db);

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 4, 0x10, 8,
				 lna2_gain_db);
	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 4, 0x10, 8,
				 lna2_gain_db);

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN1, 10, 0x20, 8,
				 tia_gain_db);
	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAIN2, 10, 0x20, 8,
				 tia_gain_db);

	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAINBITS1, 10, 0x20, 8,
				 tia_gainbits);
	wlc_phy_table_write_nphy(pi, NPHY_TBL_ID_GAINBITS2, 10, 0x20, 8,
				 tia_gainbits);

	write_phy_reg(pi, 0x37, 0x74);
	write_phy_reg(pi, 0x2ad, 0x74);
	write_phy_reg(pi, 0x38, 0x18);
	write_phy_reg(pi, 0x2ae, 0x18);

	write_phy_reg(pi, 0x2b, 0xe8);
	write_phy_reg(pi, 0x41, 0xe8);

	if (CHSPEC_IS20(pi->radio_chanspec)) {

		mod_phy_reg(pi, 0x300, (0x3f << 0), (0x12 << 0));
		mod_phy_reg(pi, 0x301, (0x3f << 0), (0x12 << 0));
	} else {

		mod_phy_reg(pi, 0x300, (0x3f << 0), (0x10 << 0));
		mod_phy_reg(pi, 0x301, (0x3f << 0), (0x10 << 0));
	}
}