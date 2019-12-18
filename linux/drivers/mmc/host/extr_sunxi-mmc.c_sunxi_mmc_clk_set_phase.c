#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sunxi_mmc_host {TYPE_2__* cfg; int /*<<< orphan*/  clk_output; int /*<<< orphan*/  clk_sample; int /*<<< orphan*/  mmc; scalar_t__ use_new_timings; } ;
struct mmc_ios {scalar_t__ timing; scalar_t__ bus_width; } ;
struct TYPE_4__ {TYPE_1__* clk_delays; } ;
struct TYPE_3__ {int /*<<< orphan*/  output; int /*<<< orphan*/  sample; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MMC_BUS_WIDTH_8 ; 
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 int SDXC_CLK_25M ; 
 int SDXC_CLK_400K ; 
 int SDXC_CLK_50M ; 
 int SDXC_CLK_50M_DDR ; 
 int SDXC_CLK_50M_DDR_8BIT ; 
 int /*<<< orphan*/  clk_set_phase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_mmc_clk_set_phase(struct sunxi_mmc_host *host,
				   struct mmc_ios *ios, u32 rate)
{
	int index;

	/* clk controller delays not used under new timings mode */
	if (host->use_new_timings)
		return 0;

	/* some old controllers don't support delays */
	if (!host->cfg->clk_delays)
		return 0;

	/* determine delays */
	if (rate <= 400000) {
		index = SDXC_CLK_400K;
	} else if (rate <= 25000000) {
		index = SDXC_CLK_25M;
	} else if (rate <= 52000000) {
		if (ios->timing != MMC_TIMING_UHS_DDR50 &&
		    ios->timing != MMC_TIMING_MMC_DDR52) {
			index = SDXC_CLK_50M;
		} else if (ios->bus_width == MMC_BUS_WIDTH_8) {
			index = SDXC_CLK_50M_DDR_8BIT;
		} else {
			index = SDXC_CLK_50M_DDR;
		}
	} else {
		dev_dbg(mmc_dev(host->mmc), "Invalid clock... returning\n");
		return -EINVAL;
	}

	clk_set_phase(host->clk_sample, host->cfg->clk_delays[index].sample);
	clk_set_phase(host->clk_output, host->cfg->clk_delays[index].output);

	return 0;
}