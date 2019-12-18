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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_pmc {int /*<<< orphan*/  dev; scalar_t__ clk; } ;
typedef  enum tegra_io_pad { ____Placeholder_tegra_io_pad } tegra_io_pad ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (int,unsigned long) ; 
 int /*<<< orphan*/  DPD_SAMPLE ; 
 unsigned long DPD_SAMPLE_ENABLE ; 
 int ENODEV ; 
 int /*<<< orphan*/  SEL_DPD_TIM ; 
 unsigned long clk_get_rate (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int tegra_io_pad_get_dpd_register_bit (struct tegra_pmc*,int,unsigned long*,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_pmc_writel (struct tegra_pmc*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_io_pad_prepare(struct tegra_pmc *pmc, enum tegra_io_pad id,
				unsigned long *request, unsigned long *status,
				u32 *mask)
{
	unsigned long rate, value;
	int err;

	err = tegra_io_pad_get_dpd_register_bit(pmc, id, request, status, mask);
	if (err)
		return err;

	if (pmc->clk) {
		rate = clk_get_rate(pmc->clk);
		if (!rate) {
			dev_err(pmc->dev, "failed to get clock rate\n");
			return -ENODEV;
		}

		tegra_pmc_writel(pmc, DPD_SAMPLE_ENABLE, DPD_SAMPLE);

		/* must be at least 200 ns, in APB (PCLK) clock cycles */
		value = DIV_ROUND_UP(1000000000, rate);
		value = DIV_ROUND_UP(200, value);
		tegra_pmc_writel(pmc, value, SEL_DPD_TIM);
	}

	return 0;
}