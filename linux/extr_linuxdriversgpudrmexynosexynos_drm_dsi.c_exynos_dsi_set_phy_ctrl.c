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
typedef  unsigned int u32 ;
struct exynos_dsi_driver_data {unsigned int* reg_values; scalar_t__ has_freqband; } ;
struct exynos_dsi {struct exynos_dsi_driver_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSIM_PHYCTRL_REG ; 
 int /*<<< orphan*/  DSIM_PHYTIMING1_REG ; 
 int /*<<< orphan*/  DSIM_PHYTIMING2_REG ; 
 int /*<<< orphan*/  DSIM_PHYTIMING_REG ; 
 size_t PHYCTRL_SLEW_UP ; 
 size_t PHYCTRL_ULPS_EXIT ; 
 size_t PHYCTRL_VREG_LP ; 
 size_t PHYTIMING_CLK_POST ; 
 size_t PHYTIMING_CLK_PREPARE ; 
 size_t PHYTIMING_CLK_TRAIL ; 
 size_t PHYTIMING_CLK_ZERO ; 
 size_t PHYTIMING_HS_EXIT ; 
 size_t PHYTIMING_HS_PREPARE ; 
 size_t PHYTIMING_HS_TRAIL ; 
 size_t PHYTIMING_HS_ZERO ; 
 size_t PHYTIMING_LPX ; 
 int /*<<< orphan*/  exynos_dsi_write (struct exynos_dsi*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void exynos_dsi_set_phy_ctrl(struct exynos_dsi *dsi)
{
	const struct exynos_dsi_driver_data *driver_data = dsi->driver_data;
	const unsigned int *reg_values = driver_data->reg_values;
	u32 reg;

	if (driver_data->has_freqband)
		return;

	/* B D-PHY: D-PHY Master & Slave Analog Block control */
	reg = reg_values[PHYCTRL_ULPS_EXIT] | reg_values[PHYCTRL_VREG_LP] |
		reg_values[PHYCTRL_SLEW_UP];
	exynos_dsi_write(dsi, DSIM_PHYCTRL_REG, reg);

	/*
	 * T LPX: Transmitted length of any Low-Power state period
	 * T HS-EXIT: Time that the transmitter drives LP-11 following a HS
	 *	burst
	 */
	reg = reg_values[PHYTIMING_LPX] | reg_values[PHYTIMING_HS_EXIT];
	exynos_dsi_write(dsi, DSIM_PHYTIMING_REG, reg);

	/*
	 * T CLK-PREPARE: Time that the transmitter drives the Clock Lane LP-00
	 *	Line state immediately before the HS-0 Line state starting the
	 *	HS transmission
	 * T CLK-ZERO: Time that the transmitter drives the HS-0 state prior to
	 *	transmitting the Clock.
	 * T CLK_POST: Time that the transmitter continues to send HS clock
	 *	after the last associated Data Lane has transitioned to LP Mode
	 *	Interval is defined as the period from the end of T HS-TRAIL to
	 *	the beginning of T CLK-TRAIL
	 * T CLK-TRAIL: Time that the transmitter drives the HS-0 state after
	 *	the last payload clock bit of a HS transmission burst
	 */
	reg = reg_values[PHYTIMING_CLK_PREPARE] |
		reg_values[PHYTIMING_CLK_ZERO] |
		reg_values[PHYTIMING_CLK_POST] |
		reg_values[PHYTIMING_CLK_TRAIL];

	exynos_dsi_write(dsi, DSIM_PHYTIMING1_REG, reg);

	/*
	 * T HS-PREPARE: Time that the transmitter drives the Data Lane LP-00
	 *	Line state immediately before the HS-0 Line state starting the
	 *	HS transmission
	 * T HS-ZERO: Time that the transmitter drives the HS-0 state prior to
	 *	transmitting the Sync sequence.
	 * T HS-TRAIL: Time that the transmitter drives the flipped differential
	 *	state after last payload data bit of a HS transmission burst
	 */
	reg = reg_values[PHYTIMING_HS_PREPARE] | reg_values[PHYTIMING_HS_ZERO] |
		reg_values[PHYTIMING_HS_TRAIL];
	exynos_dsi_write(dsi, DSIM_PHYTIMING2_REG, reg);
}