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
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RADIO_2064_REG005 ; 
 int /*<<< orphan*/  RADIO_2064_REG007 ; 
 int /*<<< orphan*/  RADIO_2064_REG00B ; 
 int /*<<< orphan*/  RADIO_2064_REG012 ; 
 int /*<<< orphan*/  RADIO_2064_REG025 ; 
 int /*<<< orphan*/  RADIO_2064_REG028 ; 
 int /*<<< orphan*/  RADIO_2064_REG036 ; 
 int /*<<< orphan*/  RADIO_2064_REG03A ; 
 int /*<<< orphan*/  RADIO_2064_REG059 ; 
 int /*<<< orphan*/  RADIO_2064_REG05C ; 
 int /*<<< orphan*/  RADIO_2064_REG078 ; 
 int /*<<< orphan*/  RADIO_2064_REG092 ; 
 int /*<<< orphan*/  RADIO_2064_REG0FC ; 
 int /*<<< orphan*/  RADIO_2064_REG0FD ; 
 int /*<<< orphan*/  RADIO_2064_REG0FF ; 
 int /*<<< orphan*/  RADIO_2064_REG112 ; 
 int /*<<< orphan*/  RADIO_2064_REG113 ; 
 int /*<<< orphan*/  RADIO_2064_REG11A ; 
 int /*<<< orphan*/  RADIO_2064_REG11F ; 
 int /*<<< orphan*/  and_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * iqlo_loopback_rf_regs ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  or_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 
 int read_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wlc_lcnphy_tx_iqlo_loopback(struct brcms_phy *pi, u16 *values_to_save)
{
	u16 vmid;
	int i;
	for (i = 0; i < 20; i++)
		values_to_save[i] =
			read_radio_reg(pi, iqlo_loopback_rf_regs[i]);

	mod_phy_reg(pi, 0x44c, (0x1 << 12), 1 << 12);
	mod_phy_reg(pi, 0x44d, (0x1 << 14), 1 << 14);

	mod_phy_reg(pi, 0x44c, (0x1 << 11), 1 << 11);
	mod_phy_reg(pi, 0x44d, (0x1 << 13), 0 << 13);

	mod_phy_reg(pi, 0x43b, (0x1 << 1), 1 << 1);
	mod_phy_reg(pi, 0x43c, (0x1 << 1), 0 << 1);

	mod_phy_reg(pi, 0x43b, (0x1 << 0), 1 << 0);
	mod_phy_reg(pi, 0x43c, (0x1 << 0), 0 << 0);

	if (LCNREV_IS(pi->pubpi.phy_rev, 2))
		and_radio_reg(pi, RADIO_2064_REG03A, 0xFD);
	else
		and_radio_reg(pi, RADIO_2064_REG03A, 0xF9);
	or_radio_reg(pi, RADIO_2064_REG11A, 0x1);

	or_radio_reg(pi, RADIO_2064_REG036, 0x01);
	or_radio_reg(pi, RADIO_2064_REG11A, 0x18);
	udelay(20);

	if (LCNREV_IS(pi->pubpi.phy_rev, 2)) {
		if (CHSPEC_IS5G(pi->radio_chanspec))
			mod_radio_reg(pi, RADIO_2064_REG03A, 1, 0);
		else
			or_radio_reg(pi, RADIO_2064_REG03A, 1);
	} else {
		if (CHSPEC_IS5G(pi->radio_chanspec))
			mod_radio_reg(pi, RADIO_2064_REG03A, 3, 1);
		else
			or_radio_reg(pi, RADIO_2064_REG03A, 0x3);
	}

	udelay(20);

	write_radio_reg(pi, RADIO_2064_REG025, 0xF);
	if (LCNREV_IS(pi->pubpi.phy_rev, 2)) {
		if (CHSPEC_IS5G(pi->radio_chanspec))
			mod_radio_reg(pi, RADIO_2064_REG028, 0xF, 0x4);
		else
			mod_radio_reg(pi, RADIO_2064_REG028, 0xF, 0x6);
	} else {
		if (CHSPEC_IS5G(pi->radio_chanspec))
			mod_radio_reg(pi, RADIO_2064_REG028, 0x1e, 0x4 << 1);
		else
			mod_radio_reg(pi, RADIO_2064_REG028, 0x1e, 0x6 << 1);
	}

	udelay(20);

	write_radio_reg(pi, RADIO_2064_REG005, 0x8);
	or_radio_reg(pi, RADIO_2064_REG112, 0x80);
	udelay(20);

	or_radio_reg(pi, RADIO_2064_REG0FF, 0x10);
	or_radio_reg(pi, RADIO_2064_REG11F, 0x44);
	udelay(20);

	or_radio_reg(pi, RADIO_2064_REG00B, 0x7);
	or_radio_reg(pi, RADIO_2064_REG113, 0x10);
	udelay(20);

	write_radio_reg(pi, RADIO_2064_REG007, 0x1);
	udelay(20);

	vmid = 0x2A6;
	mod_radio_reg(pi, RADIO_2064_REG0FC, 0x3 << 0, (vmid >> 8) & 0x3);
	write_radio_reg(pi, RADIO_2064_REG0FD, (vmid & 0xff));
	or_radio_reg(pi, RADIO_2064_REG11F, 0x44);
	udelay(20);

	or_radio_reg(pi, RADIO_2064_REG0FF, 0x10);
	udelay(20);
	write_radio_reg(pi, RADIO_2064_REG012, 0x02);
	or_radio_reg(pi, RADIO_2064_REG112, 0x06);
	write_radio_reg(pi, RADIO_2064_REG036, 0x11);
	write_radio_reg(pi, RADIO_2064_REG059, 0xcc);
	write_radio_reg(pi, RADIO_2064_REG05C, 0x2e);
	write_radio_reg(pi, RADIO_2064_REG078, 0xd7);
	write_radio_reg(pi, RADIO_2064_REG092, 0x15);
}