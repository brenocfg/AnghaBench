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
struct msdc_host {int hs400_mode; scalar_t__ base; int /*<<< orphan*/  hs400_ds_delay; scalar_t__ top_base; } ;
struct mmc_ios {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ EMMC50_CFG3 ; 
 int /*<<< orphan*/  EMMC50_CFG3_OUTS_WR ; 
 scalar_t__ EMMC50_PAD_DS_TUNE ; 
 scalar_t__ MSDC_PATCH_BIT2 ; 
 int /*<<< orphan*/  MSDC_PATCH_BIT2_CFGCRCSTS ; 
 scalar_t__ PAD_DS_TUNE ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdr_set_field (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int msdc_prepare_hs400_tuning(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct msdc_host *host = mmc_priv(mmc);
	host->hs400_mode = true;

	if (host->top_base)
		writel(host->hs400_ds_delay,
		       host->top_base + EMMC50_PAD_DS_TUNE);
	else
		writel(host->hs400_ds_delay, host->base + PAD_DS_TUNE);
	/* hs400 mode must set it to 0 */
	sdr_clr_bits(host->base + MSDC_PATCH_BIT2, MSDC_PATCH_BIT2_CFGCRCSTS);
	/* to improve read performance, set outstanding to 2 */
	sdr_set_field(host->base + EMMC50_CFG3, EMMC50_CFG3_OUTS_WR, 2);

	return 0;
}