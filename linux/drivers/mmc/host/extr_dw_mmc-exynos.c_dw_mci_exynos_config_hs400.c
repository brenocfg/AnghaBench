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
typedef  scalar_t__ u32 ;
struct dw_mci_exynos_priv_data {scalar_t__ ctrl_type; scalar_t__ saved_dqs_en; scalar_t__ saved_strobe_ctrl; int /*<<< orphan*/  dqs_delay; } ;
struct dw_mci {int /*<<< orphan*/  dev; struct dw_mci_exynos_priv_data* priv; } ;

/* Variables and functions */
 scalar_t__ DATA_STROBE_EN ; 
 scalar_t__ DQS_CTRL_RD_DELAY (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DW_MCI_TYPE_EXYNOS5420 ; 
 int /*<<< orphan*/  HS400_DLINE_CTRL ; 
 int /*<<< orphan*/  HS400_DQS_EN ; 
 scalar_t__ MMC_TIMING_MMC_HS400 ; 
 scalar_t__ MMC_TIMING_UHS_SDR104 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dw_mci_exynos_config_hs400(struct dw_mci *host, u32 timing)
{
	struct dw_mci_exynos_priv_data *priv = host->priv;
	u32 dqs, strobe;

	/*
	 * Not supported to configure register
	 * related to HS400
	 */
	if (priv->ctrl_type < DW_MCI_TYPE_EXYNOS5420) {
		if (timing == MMC_TIMING_MMC_HS400)
			dev_warn(host->dev,
				 "cannot configure HS400, unsupported chipset\n");
		return;
	}

	dqs = priv->saved_dqs_en;
	strobe = priv->saved_strobe_ctrl;

	if (timing == MMC_TIMING_MMC_HS400) {
		dqs |= DATA_STROBE_EN;
		strobe = DQS_CTRL_RD_DELAY(strobe, priv->dqs_delay);
	} else if (timing == MMC_TIMING_UHS_SDR104) {
		dqs &= 0xffffff00;
	} else {
		dqs &= ~DATA_STROBE_EN;
	}

	mci_writel(host, HS400_DQS_EN, dqs);
	mci_writel(host, HS400_DLINE_CTRL, strobe);
}