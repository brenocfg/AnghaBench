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
typedef  int u32 ;
struct tegra_dsi {int /*<<< orphan*/  mipi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PAD_CONTROL_0 ; 
 int /*<<< orphan*/  DSI_PAD_CONTROL_1 ; 
 int /*<<< orphan*/  DSI_PAD_CONTROL_2 ; 
 int /*<<< orphan*/  DSI_PAD_CONTROL_3 ; 
 int /*<<< orphan*/  DSI_PAD_CONTROL_4 ; 
 int DSI_PAD_LP_DN (int) ; 
 int DSI_PAD_LP_UP (int) ; 
 int DSI_PAD_OUT_CLK (int) ; 
 int DSI_PAD_PREEMP_PD (int) ; 
 int DSI_PAD_PREEMP_PD_CLK (int) ; 
 int DSI_PAD_PREEMP_PU (int) ; 
 int DSI_PAD_PREEMP_PU_CLK (int) ; 
 int DSI_PAD_SLEW_DN (int) ; 
 int DSI_PAD_SLEW_UP (int) ; 
 int /*<<< orphan*/  tegra_dsi_pad_enable (struct tegra_dsi*) ; 
 int /*<<< orphan*/  tegra_dsi_writel (struct tegra_dsi*,int,int /*<<< orphan*/ ) ; 
 int tegra_mipi_calibrate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_dsi_pad_calibrate(struct tegra_dsi *dsi)
{
	u32 value;

	/*
	 * XXX Is this still needed? The module reset is deasserted right
	 * before this function is called.
	 */
	tegra_dsi_writel(dsi, 0, DSI_PAD_CONTROL_0);
	tegra_dsi_writel(dsi, 0, DSI_PAD_CONTROL_1);
	tegra_dsi_writel(dsi, 0, DSI_PAD_CONTROL_2);
	tegra_dsi_writel(dsi, 0, DSI_PAD_CONTROL_3);
	tegra_dsi_writel(dsi, 0, DSI_PAD_CONTROL_4);

	/* start calibration */
	tegra_dsi_pad_enable(dsi);

	value = DSI_PAD_SLEW_UP(0x7) | DSI_PAD_SLEW_DN(0x7) |
		DSI_PAD_LP_UP(0x1) | DSI_PAD_LP_DN(0x1) |
		DSI_PAD_OUT_CLK(0x0);
	tegra_dsi_writel(dsi, value, DSI_PAD_CONTROL_2);

	value = DSI_PAD_PREEMP_PD_CLK(0x3) | DSI_PAD_PREEMP_PU_CLK(0x3) |
		DSI_PAD_PREEMP_PD(0x03) | DSI_PAD_PREEMP_PU(0x3);
	tegra_dsi_writel(dsi, value, DSI_PAD_CONTROL_3);

	return tegra_mipi_calibrate(dsi->mipi);
}