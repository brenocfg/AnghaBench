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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_omap_host {struct device* dev; } ;
struct sdhci_host {int ier; } ;
struct mmc_ios {int clock; scalar_t__ timing; } ;
struct mmc_host {struct mmc_ios ios; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AC12_SCLK_SEL ; 
 scalar_t__ CAPA2_TSDR50 ; 
 scalar_t__ DLL_SWT ; 
 int EIO ; 
 scalar_t__ MAX_PHASE_DELAY ; 
 scalar_t__ MMC_TIMING_UHS_SDR50 ; 
 int SDHCI_INT_DATA_CRC ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_OMAP_AC12 ; 
 int /*<<< orphan*/  SDHCI_OMAP_CAPA2 ; 
 int /*<<< orphan*/  SDHCI_OMAP_DLL ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_send_tuning (struct mmc_host*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_omap_disable_tuning (struct sdhci_omap_host*) ; 
 scalar_t__ sdhci_omap_readl (struct sdhci_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_omap_set_dll (struct sdhci_omap_host*,scalar_t__) ; 
 int /*<<< orphan*/  sdhci_omap_writel (struct sdhci_omap_host*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sdhci_omap_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdhci_omap_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct sdhci_host *host = mmc_priv(mmc);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);
	struct device *dev = omap_host->dev;
	struct mmc_ios *ios = &mmc->ios;
	u32 start_window = 0, max_window = 0;
	bool dcrc_was_enabled = false;
	u8 cur_match, prev_match = 0;
	u32 length = 0, max_len = 0;
	u32 phase_delay = 0;
	int ret = 0;
	u32 reg;

	pltfm_host = sdhci_priv(host);
	omap_host = sdhci_pltfm_priv(pltfm_host);
	dev = omap_host->dev;

	/* clock tuning is not needed for upto 52MHz */
	if (ios->clock <= 52000000)
		return 0;

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_CAPA2);
	if (ios->timing == MMC_TIMING_UHS_SDR50 && !(reg & CAPA2_TSDR50))
		return 0;

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_DLL);
	reg |= DLL_SWT;
	sdhci_omap_writel(omap_host, SDHCI_OMAP_DLL, reg);

	/*
	 * OMAP5/DRA74X/DRA72x Errata i802:
	 * DCRC error interrupts (MMCHS_STAT[21] DCRC=0x1) can occur
	 * during the tuning procedure. So disable it during the
	 * tuning procedure.
	 */
	if (host->ier & SDHCI_INT_DATA_CRC) {
		host->ier &= ~SDHCI_INT_DATA_CRC;
		dcrc_was_enabled = true;
	}

	while (phase_delay <= MAX_PHASE_DELAY) {
		sdhci_omap_set_dll(omap_host, phase_delay);

		cur_match = !mmc_send_tuning(mmc, opcode, NULL);
		if (cur_match) {
			if (prev_match) {
				length++;
			} else {
				start_window = phase_delay;
				length = 1;
			}
		}

		if (length > max_len) {
			max_window = start_window;
			max_len = length;
		}

		prev_match = cur_match;
		phase_delay += 4;
	}

	if (!max_len) {
		dev_err(dev, "Unable to find match\n");
		ret = -EIO;
		goto tuning_error;
	}

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_AC12);
	if (!(reg & AC12_SCLK_SEL)) {
		ret = -EIO;
		goto tuning_error;
	}

	phase_delay = max_window + 4 * (max_len >> 1);
	sdhci_omap_set_dll(omap_host, phase_delay);

	goto ret;

tuning_error:
	dev_err(dev, "Tuning failed\n");
	sdhci_omap_disable_tuning(omap_host);

ret:
	sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
	/* Reenable forbidden interrupt */
	if (dcrc_was_enabled)
		host->ier |= SDHCI_INT_DATA_CRC;
	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
	return ret;
}