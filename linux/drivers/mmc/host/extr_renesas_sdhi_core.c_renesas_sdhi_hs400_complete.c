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
struct tmio_mmc_host {int tap_set; TYPE_1__* pdata; } ;
struct renesas_sdhi {int scc_tappos_hs400; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CLK_CTL_SCLKEN ; 
 int /*<<< orphan*/  CTL_SDIF_MODE ; 
 int /*<<< orphan*/  CTL_SD_CARD_CLK_CTL ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_CKSEL ; 
 int SH_MOBILE_SDHI_SCC_CKSEL_DTSEL ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_DT2FF ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_DTCNTL ; 
 int SH_MOBILE_SDHI_SCC_DTCNTL_TAPEN ; 
 int SH_MOBILE_SDHI_SCC_DTCNTL_TAPNUM_SHIFT ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_TAPSET ; 
 int /*<<< orphan*/  SH_MOBILE_SDHI_SCC_TMPPORT2 ; 
 int SH_MOBILE_SDHI_SCC_TMPPORT2_HS400EN ; 
 int SH_MOBILE_SDHI_SCC_TMPPORT2_HS400OSEL ; 
 int TMIO_MMC_HAVE_4TAP_HS400 ; 
 struct renesas_sdhi* host_to_priv (struct tmio_mmc_host*) ; 
 int sd_ctrl_read16 (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_ctrl_write16 (struct tmio_mmc_host*,int /*<<< orphan*/ ,int) ; 
 int sd_scc_read32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_scc_write32 (struct tmio_mmc_host*,struct renesas_sdhi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void renesas_sdhi_hs400_complete(struct tmio_mmc_host *host)
{
	struct renesas_sdhi *priv = host_to_priv(host);

	sd_ctrl_write16(host, CTL_SD_CARD_CLK_CTL, ~CLK_CTL_SCLKEN &
		sd_ctrl_read16(host, CTL_SD_CARD_CLK_CTL));

	/* Set HS400 mode */
	sd_ctrl_write16(host, CTL_SDIF_MODE, 0x0001 |
			sd_ctrl_read16(host, CTL_SDIF_MODE));

	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_DT2FF,
		       priv->scc_tappos_hs400);

	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT2,
		       (SH_MOBILE_SDHI_SCC_TMPPORT2_HS400EN |
			SH_MOBILE_SDHI_SCC_TMPPORT2_HS400OSEL) |
			sd_scc_read32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT2));

	/* Set the sampling clock selection range of HS400 mode */
	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_DTCNTL,
		       SH_MOBILE_SDHI_SCC_DTCNTL_TAPEN |
		       0x4 << SH_MOBILE_SDHI_SCC_DTCNTL_TAPNUM_SHIFT);


	if (host->pdata->flags & TMIO_MMC_HAVE_4TAP_HS400)
		sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_TAPSET,
			       host->tap_set / 2);

	sd_scc_write32(host, priv, SH_MOBILE_SDHI_SCC_CKSEL,
		       SH_MOBILE_SDHI_SCC_CKSEL_DTSEL |
		       sd_scc_read32(host, priv, SH_MOBILE_SDHI_SCC_CKSEL));

	sd_ctrl_write16(host, CTL_SD_CARD_CLK_CTL, CLK_CTL_SCLKEN |
			sd_ctrl_read16(host, CTL_SD_CARD_CLK_CTL));
}