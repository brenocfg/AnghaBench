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
struct dw_mci {int bus_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDTHRCTL ; 
 int GENCLK_DIV ; 
 int /*<<< orphan*/  MMC_TIMING_LEGACY ; 
 int /*<<< orphan*/  SDCARD_RD_THRESHOLD ; 
 int /*<<< orphan*/  SDMMC_CARD_RD_THR_EN ; 
 int /*<<< orphan*/  SDMMC_SET_THLD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mci_hs_set_timing (struct dw_mci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mci_hi3660_init(struct dw_mci *host)
{
	mci_writel(host, CDTHRCTL, SDMMC_SET_THLD(SDCARD_RD_THRESHOLD,
		    SDMMC_CARD_RD_THR_EN));

	dw_mci_hs_set_timing(host, MMC_TIMING_LEGACY, -1);
	host->bus_hz /= (GENCLK_DIV + 1);

	return 0;
}