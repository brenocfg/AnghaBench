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
struct tegra_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_PAD_CONTROL_0 ; 
 int DSI_PAD_CONTROL_VS1_PDIO (int /*<<< orphan*/ ) ; 
 int DSI_PAD_CONTROL_VS1_PULLDN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dsi_writel (struct tegra_dsi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_dsi_pad_enable(struct tegra_dsi *dsi)
{
	u32 value;

	value = DSI_PAD_CONTROL_VS1_PULLDN(0) | DSI_PAD_CONTROL_VS1_PDIO(0);
	tegra_dsi_writel(dsi, value, DSI_PAD_CONTROL_0);

	return 0;
}