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
struct dw_mci_exynos_priv_data {scalar_t__ ctrl_type; } ;
struct dw_mci {struct dw_mci_exynos_priv_data* priv; } ;

/* Variables and functions */
 scalar_t__ DW_MCI_TYPE_EXYNOS5420_SMU ; 
 scalar_t__ DW_MCI_TYPE_EXYNOS7_SMU ; 
 int /*<<< orphan*/  MPSBEGIN0 ; 
 int /*<<< orphan*/  MPSCTRL0 ; 
 int /*<<< orphan*/  MPSEND0 ; 
 int SDMMC_ENDING_SEC_NR_MAX ; 
 int SDMMC_MPSCTRL_NON_SECURE_READ_BIT ; 
 int SDMMC_MPSCTRL_NON_SECURE_WRITE_BIT ; 
 int SDMMC_MPSCTRL_SECURE_WRITE_BIT ; 
 int SDMMC_MPSCTRL_VALID ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dw_mci_exynos_config_smu(struct dw_mci *host)
{
	struct dw_mci_exynos_priv_data *priv = host->priv;

	/*
	 * If Exynos is provided the Security management,
	 * set for non-ecryption mode at this time.
	 */
	if (priv->ctrl_type == DW_MCI_TYPE_EXYNOS5420_SMU ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU) {
		mci_writel(host, MPSBEGIN0, 0);
		mci_writel(host, MPSEND0, SDMMC_ENDING_SEC_NR_MAX);
		mci_writel(host, MPSCTRL0, SDMMC_MPSCTRL_SECURE_WRITE_BIT |
			   SDMMC_MPSCTRL_NON_SECURE_READ_BIT |
			   SDMMC_MPSCTRL_VALID |
			   SDMMC_MPSCTRL_NON_SECURE_WRITE_BIT);
	}
}