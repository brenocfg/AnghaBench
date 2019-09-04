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
struct mmc_ios {int clock; } ;
struct dw_mci_exynos_priv_data {int /*<<< orphan*/  hs400_timing; } ;
struct dw_mci {struct dw_mci_exynos_priv_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_mci_exynos_adjust_clock (struct dw_mci*,int) ; 
 int /*<<< orphan*/  dw_mci_exynos_set_clksel_timing (struct dw_mci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mci_exynos_prepare_hs400_tuning(struct dw_mci *host,
					struct mmc_ios *ios)
{
	struct dw_mci_exynos_priv_data *priv = host->priv;

	dw_mci_exynos_set_clksel_timing(host, priv->hs400_timing);
	dw_mci_exynos_adjust_clock(host, (ios->clock) << 1);

	return 0;
}