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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct exynos_dsi_driver_data {scalar_t__ has_freqband; scalar_t__ plltmr_reg; int /*<<< orphan*/ * reg_values; } ;
struct exynos_dsi {unsigned long pll_clk_rate; int /*<<< orphan*/  dev; scalar_t__ reg_base; struct exynos_dsi_driver_data* driver_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long const*) ; 
 int DSIM_FREQ_BAND (int) ; 
 int /*<<< orphan*/  DSIM_PLLCTRL_REG ; 
 int DSIM_PLL_EN ; 
 int DSIM_PLL_M (int /*<<< orphan*/ ) ; 
 int DSIM_PLL_P (int /*<<< orphan*/ ) ; 
 int DSIM_PLL_S (int /*<<< orphan*/ ) ; 
 int DSIM_PLL_STABLE ; 
 int /*<<< orphan*/  DSIM_STATUS_REG ; 
#define  MHZ 128 
 size_t PLL_TIMER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long exynos_dsi_pll_find_pms (struct exynos_dsi*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int exynos_dsi_read (struct exynos_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_dsi_write (struct exynos_dsi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned long exynos_dsi_set_pll(struct exynos_dsi *dsi,
					unsigned long freq)
{
	const struct exynos_dsi_driver_data *driver_data = dsi->driver_data;
	unsigned long fin, fout;
	int timeout;
	u8 p, s;
	u16 m;
	u32 reg;

	fin = dsi->pll_clk_rate;
	fout = exynos_dsi_pll_find_pms(dsi, fin, freq, &p, &m, &s);
	if (!fout) {
		dev_err(dsi->dev,
			"failed to find PLL PMS for requested frequency\n");
		return 0;
	}
	dev_dbg(dsi->dev, "PLL freq %lu, (p %d, m %d, s %d)\n", fout, p, m, s);

	writel(driver_data->reg_values[PLL_TIMER],
			dsi->reg_base + driver_data->plltmr_reg);

	reg = DSIM_PLL_EN | DSIM_PLL_P(p) | DSIM_PLL_M(m) | DSIM_PLL_S(s);

	if (driver_data->has_freqband) {
		static const unsigned long freq_bands[] = {
			100 * MHZ, 120 * MHZ, 160 * MHZ, 200 * MHZ,
			270 * MHZ, 320 * MHZ, 390 * MHZ, 450 * MHZ,
			510 * MHZ, 560 * MHZ, 640 * MHZ, 690 * MHZ,
			770 * MHZ, 870 * MHZ, 950 * MHZ,
		};
		int band;

		for (band = 0; band < ARRAY_SIZE(freq_bands); ++band)
			if (fout < freq_bands[band])
				break;

		dev_dbg(dsi->dev, "band %d\n", band);

		reg |= DSIM_FREQ_BAND(band);
	}

	exynos_dsi_write(dsi, DSIM_PLLCTRL_REG, reg);

	timeout = 1000;
	do {
		if (timeout-- == 0) {
			dev_err(dsi->dev, "PLL failed to stabilize\n");
			return 0;
		}
		reg = exynos_dsi_read(dsi, DSIM_STATUS_REG);
	} while ((reg & DSIM_PLL_STABLE) == 0);

	return fout;
}