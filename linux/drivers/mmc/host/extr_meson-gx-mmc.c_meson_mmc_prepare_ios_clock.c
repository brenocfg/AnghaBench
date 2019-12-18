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
struct mmc_ios {int timing; int /*<<< orphan*/  clock; } ;
struct meson_host {int dummy; } ;

/* Variables and functions */
#define  MMC_TIMING_MMC_DDR52 129 
#define  MMC_TIMING_UHS_DDR50 128 
 int meson_mmc_clk_set (struct meson_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meson_mmc_prepare_ios_clock(struct meson_host *host,
				       struct mmc_ios *ios)
{
	bool ddr;

	switch (ios->timing) {
	case MMC_TIMING_MMC_DDR52:
	case MMC_TIMING_UHS_DDR50:
		ddr = true;
		break;

	default:
		ddr = false;
		break;
	}

	return meson_mmc_clk_set(host, ios->clock, ddr);
}