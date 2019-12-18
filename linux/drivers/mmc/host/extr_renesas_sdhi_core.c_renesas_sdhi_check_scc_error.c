#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tmio_mmc_host {TYPE_3__* mmc; TYPE_2__* pdata; } ;
struct renesas_sdhi {int dummy; } ;
struct TYPE_4__ {scalar_t__ timing; } ;
struct TYPE_6__ {TYPE_1__ ios; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 scalar_t__ MMC_TIMING_MMC_HS200 ; 
 scalar_t__ MMC_TIMING_MMC_HS400 ; 
 scalar_t__ MMC_TIMING_UHS_SDR104 ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_RVSCNTL ; 
 int SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_RVSREQ ; 
 int SH_MOBILE_SDHI_SCC_RVSREQ_RVSERR ; 
 int TMIO_MMC_HAVE_4TAP_HS400 ; 
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 scalar_t__ mmc_doing_retune (TYPE_3__*) ; 
 int sd_scc_read32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_scc_write32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool renesas_sdhi_check_scc_error(struct tmio_mmc_host *host)
{
	struct renesas_sdhi *priv = host_to_priv(host);
	bool use_4tap = host->pdata->flags & TMIO_MMC_HAVE_4TAP_HS400;

	/*
	 * Skip checking SCC errors when running on 4 taps in HS400 mode as
	 * any retuning would still result in the same 4 taps being used.
	 */
	if (!(host->mmc->ios.timing == MMC_TIMING_UHS_SDR104) &&
	    !(host->mmc->ios.timing == MMC_TIMING_MMC_HS200) &&
	    !(host->mmc->ios.timing == MMC_TIMING_MMC_HS400 && !use_4tap))
		return false;

	if (mmc_doing_retune(host->mmc))
		return false;

	/* Check SCC error */
	if (sd_scc_read32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL) &
	    SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN &&
	    sd_scc_read32(host, priv, SH_MOBILE_SDHI_SCC_RVSREQ) &
	    SH_MOBILE_SDHI_SCC_RVSREQ_RVSERR) {
		/* Clear SCC error */
		sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_RVSREQ, 0);
		return true;
	}

	return false;
}