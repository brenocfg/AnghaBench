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
struct mmc_ios {int timing; } ;
struct meson_host {int dummy; } ;

/* Variables and functions */
#define  MMC_TIMING_LEGACY 131 
#define  MMC_TIMING_MMC_DDR52 130 
#define  MMC_TIMING_MMC_HS 129 
#define  MMC_TIMING_SD_HS 128 
 int /*<<< orphan*/  meson_mmc_disable_resampling (struct meson_host*) ; 

__attribute__((used)) static void meson_mmc_check_resampling(struct meson_host *host,
				       struct mmc_ios *ios)
{
	switch (ios->timing) {
	case MMC_TIMING_LEGACY:
	case MMC_TIMING_MMC_HS:
	case MMC_TIMING_SD_HS:
	case MMC_TIMING_MMC_DDR52:
		meson_mmc_disable_resampling(host);
		break;
	}
}