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
typedef  int u32 ;
struct mcde_dsi {int /*<<< orphan*/  dev; scalar_t__ regs; TYPE_1__* mdsi; int /*<<< orphan*/  hs_clk; } ;
struct TYPE_2__ {int mode_flags; int lanes; } ;

/* Variables and functions */
 scalar_t__ DSI_CMD_MODE_CTL ; 
 int DSI_CMD_MODE_CTL_IF1_ID_MASK ; 
 int DSI_CMD_MODE_CTL_TE_TIMEOUT_SHIFT ; 
 scalar_t__ DSI_DPHY_LANES_TRIM ; 
 int DSI_DPHY_LANES_TRIM_DPHY_SPECS_90_81B_0_90 ; 
 scalar_t__ DSI_MCTL_DPHY_STATIC ; 
 int DSI_MCTL_DPHY_STATIC_UI_X4_MASK ; 
 int DSI_MCTL_DPHY_STATIC_UI_X4_SHIFT ; 
 scalar_t__ DSI_MCTL_DPHY_TIMEOUT ; 
 int DSI_MCTL_DPHY_TIMEOUT_CLK_DIV_SHIFT ; 
 int DSI_MCTL_DPHY_TIMEOUT_HSTX_TO_VAL_SHIFT ; 
 int DSI_MCTL_DPHY_TIMEOUT_LPRX_TO_VAL_SHIFT ; 
 scalar_t__ DSI_MCTL_INTEGRATION_MODE ; 
 scalar_t__ DSI_MCTL_MAIN_DATA_CTL ; 
 int DSI_MCTL_MAIN_DATA_CTL_BTA_EN ; 
 int DSI_MCTL_MAIN_DATA_CTL_HOST_EOT_GEN ; 
 int DSI_MCTL_MAIN_DATA_CTL_LINK_EN ; 
 int DSI_MCTL_MAIN_DATA_CTL_READ_EN ; 
 int DSI_MCTL_MAIN_DATA_CTL_REG_TE_EN ; 
 scalar_t__ DSI_MCTL_MAIN_EN ; 
 int DSI_MCTL_MAIN_EN_CKLANE_EN ; 
 int DSI_MCTL_MAIN_EN_DAT1_EN ; 
 int DSI_MCTL_MAIN_EN_DAT2_EN ; 
 int DSI_MCTL_MAIN_EN_IF1_EN ; 
 int DSI_MCTL_MAIN_EN_PLL_START ; 
 scalar_t__ DSI_MCTL_MAIN_PHY_CTL ; 
 int DSI_MCTL_MAIN_PHY_CTL_CLK_CONTINUOUS ; 
 int DSI_MCTL_MAIN_PHY_CTL_CLK_ULPM_EN ; 
 int DSI_MCTL_MAIN_PHY_CTL_DAT1_ULPM_EN ; 
 int DSI_MCTL_MAIN_PHY_CTL_DAT2_ULPM_EN ; 
 int DSI_MCTL_MAIN_PHY_CTL_LANE2_EN ; 
 int DSI_MCTL_MAIN_PHY_CTL_WAIT_BURST_TIME_SHIFT ; 
 scalar_t__ DSI_MCTL_MAIN_STS ; 
 int DSI_MCTL_MAIN_STS_CLKLANE_READY ; 
 int DSI_MCTL_MAIN_STS_DAT1_READY ; 
 int DSI_MCTL_MAIN_STS_DAT2_READY ; 
 int DSI_MCTL_MAIN_STS_PLL_LOCK ; 
 scalar_t__ DSI_MCTL_ULPOUT_TIME ; 
 int DSI_MCTL_ULPOUT_TIME_CKLANE_ULPOUT_TIME_SHIFT ; 
 int DSI_MCTL_ULPOUT_TIME_DATA_ULPOUT_TIME_SHIFT ; 
 int MIPI_DSI_CLOCK_NON_CONTINUOUS ; 
 int MIPI_DSI_MODE_EOT_PACKET ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mcde_dsi_start(struct mcde_dsi *d)
{
	unsigned long hs_freq;
	u32 val;
	int i;

	/* No integration mode */
	writel(0, d->regs + DSI_MCTL_INTEGRATION_MODE);

	/* Enable the DSI port, from drivers/video/mcde/dsilink_v2.c */
	val = DSI_MCTL_MAIN_DATA_CTL_LINK_EN |
		DSI_MCTL_MAIN_DATA_CTL_BTA_EN |
		DSI_MCTL_MAIN_DATA_CTL_READ_EN |
		DSI_MCTL_MAIN_DATA_CTL_REG_TE_EN;
	if (d->mdsi->mode_flags & MIPI_DSI_MODE_EOT_PACKET)
		val |= DSI_MCTL_MAIN_DATA_CTL_HOST_EOT_GEN;
	writel(val, d->regs + DSI_MCTL_MAIN_DATA_CTL);

	/* Set a high command timeout, clear other fields */
	val = 0x3ff << DSI_CMD_MODE_CTL_TE_TIMEOUT_SHIFT;
	writel(val, d->regs + DSI_CMD_MODE_CTL);

	/*
	 * UI_X4 is described as "unit interval times four"
	 * I guess since DSI packets are 4 bytes wide, one unit
	 * is one byte.
	 */
	hs_freq = clk_get_rate(d->hs_clk);
	hs_freq /= 1000000; /* MHz */
	val = 4000 / hs_freq;
	dev_dbg(d->dev, "UI value: %d\n", val);
	val <<= DSI_MCTL_DPHY_STATIC_UI_X4_SHIFT;
	val &= DSI_MCTL_DPHY_STATIC_UI_X4_MASK;
	writel(val, d->regs + DSI_MCTL_DPHY_STATIC);

	/*
	 * Enable clocking: 0x0f (something?) between each burst,
	 * enable the second lane if needed, enable continuous clock if
	 * needed, enable switch into ULPM (ultra-low power mode) on
	 * all the lines.
	 */
	val = 0x0f << DSI_MCTL_MAIN_PHY_CTL_WAIT_BURST_TIME_SHIFT;
	if (d->mdsi->lanes == 2)
		val |= DSI_MCTL_MAIN_PHY_CTL_LANE2_EN;
	if (!(d->mdsi->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS))
		val |= DSI_MCTL_MAIN_PHY_CTL_CLK_CONTINUOUS;
	val |= DSI_MCTL_MAIN_PHY_CTL_CLK_ULPM_EN |
		DSI_MCTL_MAIN_PHY_CTL_DAT1_ULPM_EN |
		DSI_MCTL_MAIN_PHY_CTL_DAT2_ULPM_EN;
	writel(val, d->regs + DSI_MCTL_MAIN_PHY_CTL);

	val = (1 << DSI_MCTL_ULPOUT_TIME_CKLANE_ULPOUT_TIME_SHIFT) |
		(1 << DSI_MCTL_ULPOUT_TIME_DATA_ULPOUT_TIME_SHIFT);
	writel(val, d->regs + DSI_MCTL_ULPOUT_TIME);

	writel(DSI_DPHY_LANES_TRIM_DPHY_SPECS_90_81B_0_90,
	       d->regs + DSI_DPHY_LANES_TRIM);

	/* High PHY timeout */
	val = (0x0f << DSI_MCTL_DPHY_TIMEOUT_CLK_DIV_SHIFT) |
		(0x3fff << DSI_MCTL_DPHY_TIMEOUT_HSTX_TO_VAL_SHIFT) |
		(0x3fff << DSI_MCTL_DPHY_TIMEOUT_LPRX_TO_VAL_SHIFT);
	writel(val, d->regs + DSI_MCTL_DPHY_TIMEOUT);

	val = DSI_MCTL_MAIN_EN_PLL_START |
		DSI_MCTL_MAIN_EN_CKLANE_EN |
		DSI_MCTL_MAIN_EN_DAT1_EN |
		DSI_MCTL_MAIN_EN_IF1_EN;
	if (d->mdsi->lanes == 2)
		val |= DSI_MCTL_MAIN_EN_DAT2_EN;
	writel(val, d->regs + DSI_MCTL_MAIN_EN);

	/* Wait for the PLL to lock and the clock and data lines to come up */
	i = 0;
	val = DSI_MCTL_MAIN_STS_PLL_LOCK |
		DSI_MCTL_MAIN_STS_CLKLANE_READY |
		DSI_MCTL_MAIN_STS_DAT1_READY;
	if (d->mdsi->lanes == 2)
		val |= DSI_MCTL_MAIN_STS_DAT2_READY;
	while ((readl(d->regs + DSI_MCTL_MAIN_STS) & val) != val) {
		/* Sleep for a millisecond */
		usleep_range(1000, 1500);
		if (i++ == 100) {
			dev_warn(d->dev, "DSI lanes did not start up\n");
			return;
		}
	}

	/* TODO needed? */

	/* Command mode, clear IF1 ID */
	val = readl(d->regs + DSI_CMD_MODE_CTL);
	/*
	 * If we enable low-power mode here, with
	 * val |= DSI_CMD_MODE_CTL_IF1_LP_EN
	 * then display updates become really slow.
	 */
	val &= ~DSI_CMD_MODE_CTL_IF1_ID_MASK;
	writel(val, d->regs + DSI_CMD_MODE_CTL);

	/* Wait for DSI PHY to initialize */
	usleep_range(100, 200);
	dev_info(d->dev, "DSI link enabled\n");
}