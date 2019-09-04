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
struct tmio_mmc_host {int dummy; } ;
struct renesas_sdhi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_RVSCNTL ; 
 int SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_RVSREQ ; 
 int SH_MOBILE_SDHI_SCC_RVSREQ_RVSERR ; 
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 int sd_scc_read32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_scc_write32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool renesas_sdhi_check_scc_error(struct tmio_mmc_host *host)
{
	struct renesas_sdhi *priv = host_to_priv(host);

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