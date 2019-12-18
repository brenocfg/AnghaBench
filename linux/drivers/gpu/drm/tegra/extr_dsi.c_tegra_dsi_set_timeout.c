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
struct tegra_dsi {struct tegra_dsi* slave; } ;

/* Variables and functions */
 int DSI_TALLY_HTX (int /*<<< orphan*/ ) ; 
 int DSI_TALLY_LRX (int /*<<< orphan*/ ) ; 
 int DSI_TALLY_TA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_TIMEOUT_0 ; 
 int /*<<< orphan*/  DSI_TIMEOUT_1 ; 
 int DSI_TIMEOUT_HTX (unsigned int) ; 
 int DSI_TIMEOUT_LRX (int) ; 
 int DSI_TIMEOUT_PR (unsigned int) ; 
 int DSI_TIMEOUT_TA (int) ; 
 int /*<<< orphan*/  DSI_TO_TALLY ; 
 int /*<<< orphan*/  tegra_dsi_writel (struct tegra_dsi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_dsi_set_timeout(struct tegra_dsi *dsi, unsigned long bclk,
				  unsigned int vrefresh)
{
	unsigned int timeout;
	u32 value;

	/* one frame high-speed transmission timeout */
	timeout = (bclk / vrefresh) / 512;
	value = DSI_TIMEOUT_LRX(0x2000) | DSI_TIMEOUT_HTX(timeout);
	tegra_dsi_writel(dsi, value, DSI_TIMEOUT_0);

	/* 2 ms peripheral timeout for panel */
	timeout = 2 * bclk / 512 * 1000;
	value = DSI_TIMEOUT_PR(timeout) | DSI_TIMEOUT_TA(0x2000);
	tegra_dsi_writel(dsi, value, DSI_TIMEOUT_1);

	value = DSI_TALLY_TA(0) | DSI_TALLY_LRX(0) | DSI_TALLY_HTX(0);
	tegra_dsi_writel(dsi, value, DSI_TO_TALLY);

	if (dsi->slave)
		tegra_dsi_set_timeout(dsi->slave, bclk, vrefresh);
}