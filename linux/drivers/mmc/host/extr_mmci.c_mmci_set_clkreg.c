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
struct variant_data {int clkreg; int clkreg_enable; int clkreg_8bit_bus_enable; int clkreg_neg_edge_enable; scalar_t__ st_clkdiv; scalar_t__ explicit_mclk_control; } ;
struct mmci_host {int cclk; int mclk; TYPE_2__* mmc; struct variant_data* variant; } ;
struct TYPE_3__ {scalar_t__ bus_width; scalar_t__ timing; } ;
struct TYPE_4__ {int actual_clock; TYPE_1__ ios; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,unsigned int) ; 
 int MCI_4BIT_BUS ; 
 int MCI_CLK_BYPASS ; 
 int MCI_CLK_ENABLE ; 
 int MCI_ST_UX500_NEG_EDGE ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_BUS_WIDTH_8 ; 
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 int /*<<< orphan*/  mmci_write_clkreg (struct mmci_host*,int) ; 

__attribute__((used)) static void mmci_set_clkreg(struct mmci_host *host, unsigned int desired)
{
	struct variant_data *variant = host->variant;
	u32 clk = variant->clkreg;

	/* Make sure cclk reflects the current calculated clock */
	host->cclk = 0;

	if (desired) {
		if (variant->explicit_mclk_control) {
			host->cclk = host->mclk;
		} else if (desired >= host->mclk) {
			clk = MCI_CLK_BYPASS;
			if (variant->st_clkdiv)
				clk |= MCI_ST_UX500_NEG_EDGE;
			host->cclk = host->mclk;
		} else if (variant->st_clkdiv) {
			/*
			 * DB8500 TRM says f = mclk / (clkdiv + 2)
			 * => clkdiv = (mclk / f) - 2
			 * Round the divider up so we don't exceed the max
			 * frequency
			 */
			clk = DIV_ROUND_UP(host->mclk, desired) - 2;
			if (clk >= 256)
				clk = 255;
			host->cclk = host->mclk / (clk + 2);
		} else {
			/*
			 * PL180 TRM says f = mclk / (2 * (clkdiv + 1))
			 * => clkdiv = mclk / (2 * f) - 1
			 */
			clk = host->mclk / (2 * desired) - 1;
			if (clk >= 256)
				clk = 255;
			host->cclk = host->mclk / (2 * (clk + 1));
		}

		clk |= variant->clkreg_enable;
		clk |= MCI_CLK_ENABLE;
		/* This hasn't proven to be worthwhile */
		/* clk |= MCI_CLK_PWRSAVE; */
	}

	/* Set actual clock for debug */
	host->mmc->actual_clock = host->cclk;

	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4)
		clk |= MCI_4BIT_BUS;
	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_8)
		clk |= variant->clkreg_8bit_bus_enable;

	if (host->mmc->ios.timing == MMC_TIMING_UHS_DDR50 ||
	    host->mmc->ios.timing == MMC_TIMING_MMC_DDR52)
		clk |= variant->clkreg_neg_edge_enable;

	mmci_write_clkreg(host, clk);
}