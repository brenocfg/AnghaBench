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
typedef  int u8 ;
struct hdmi_phy_data {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {unsigned long max_phy; scalar_t__ ldo_voltage; scalar_t__ bist_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_TXPHY_BIST_CONTROL ; 
 int /*<<< orphan*/  HDMI_TXPHY_DIGITAL_CTRL ; 
 int /*<<< orphan*/  HDMI_TXPHY_POWER_CTRL ; 
 int /*<<< orphan*/  HDMI_TXPHY_TX_CTRL ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  hdmi_phy_configure_lanes (struct hdmi_phy_data*) ; 
 int /*<<< orphan*/  hdmi_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* phy_feat ; 

int hdmi_phy_configure(struct hdmi_phy_data *phy, unsigned long hfbitclk,
	unsigned long lfbitclk)
{
	u8 freqout;

	/*
	 * Read address 0 in order to get the SCP reset done completed
	 * Dummy access performed to make sure reset is done
	 */
	hdmi_read_reg(phy->base, HDMI_TXPHY_TX_CTRL);

	/*
	 * In OMAP5+, the HFBITCLK must be divided by 2 before issuing the
	 * HDMI_PHYPWRCMD_LDOON command.
	*/
	if (phy_feat->bist_ctrl)
		REG_FLD_MOD(phy->base, HDMI_TXPHY_BIST_CONTROL, 1, 11, 11);

	/*
	 * If the hfbitclk != lfbitclk, it means the lfbitclk was configured
	 * to be used for TMDS.
	 */
	if (hfbitclk != lfbitclk)
		freqout = 0;
	else if (hfbitclk / 10 < phy_feat->max_phy)
		freqout = 1;
	else
		freqout = 2;

	/*
	 * Write to phy address 0 to configure the clock
	 * use HFBITCLK write HDMI_TXPHY_TX_CONTROL_FREQOUT field
	 */
	REG_FLD_MOD(phy->base, HDMI_TXPHY_TX_CTRL, freqout, 31, 30);

	/* Write to phy address 1 to start HDMI line (TXVALID and TMDSCLKEN) */
	hdmi_write_reg(phy->base, HDMI_TXPHY_DIGITAL_CTRL, 0xF0000000);

	/* Setup max LDO voltage */
	if (phy_feat->ldo_voltage)
		REG_FLD_MOD(phy->base, HDMI_TXPHY_POWER_CTRL, 0xB, 3, 0);

	hdmi_phy_configure_lanes(phy);

	return 0;
}