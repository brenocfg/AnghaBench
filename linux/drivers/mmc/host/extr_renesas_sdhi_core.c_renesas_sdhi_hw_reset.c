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
struct tmio_mmc_host {TYPE_1__* pdata; } ;
struct renesas_sdhi {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CLK_CTL_SCLKEN ; 
 int /*<<< orphan*/  CTL_IRQ_MASK ; 
 int /*<<< orphan*/  CTL_SD_CARD_CLK_CTL ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_RVSCNTL ; 
 int SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN ; 
 int /*<<< orphan*/  TMIO_MASK_INIT_RCAR2 ; 
 int TMIO_MMC_MIN_RCAR2 ; 
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  renesas_sdhi_reset_hs400_mode (struct tmio_mmc_host*,struct renesas_sdhi*) ; 
 int /*<<< orphan*/  renesas_sdhi_reset_scc (struct tmio_mmc_host*,struct renesas_sdhi*) ; 
 int sd_ctrl_read16 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_ctrl_write32_as_16_and_16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sd_scc_read32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_scc_write32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void renesas_sdhi_hw_reset(struct tmio_mmc_host *host)
{
	struct renesas_sdhi *priv;

	priv = host_to_priv(host);

	renesas_sdhi_reset_scc(host, priv);
	renesas_sdhi_reset_hs400_mode(host, priv);

	sd_ctrl_write16(host, CTL_SD_CARD_CLK_CTL, CLK_CTL_SCLKEN |
			sd_ctrl_read16(host, CTL_SD_CARD_CLK_CTL));

	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL,
		       ~SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN &
		       sd_scc_read32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL));

	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL,
		       ~SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN &
		       sd_scc_read32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL));

	if (host->pdata->flags & TMIO_MMC_MIN_RCAR2)
		sd_ctrl_write32_as_16_and_16(host, CTL_IRQ_MASK,
					     TMIO_MASK_INIT_RCAR2);
}