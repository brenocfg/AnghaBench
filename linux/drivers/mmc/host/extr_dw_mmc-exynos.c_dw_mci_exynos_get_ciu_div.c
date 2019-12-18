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
typedef  scalar_t__ u8 ;
struct dw_mci_exynos_priv_data {scalar_t__ ctrl_type; } ;
struct dw_mci {struct dw_mci_exynos_priv_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKSEL ; 
 int /*<<< orphan*/  CLKSEL64 ; 
 scalar_t__ DW_MCI_TYPE_EXYNOS4210 ; 
 scalar_t__ DW_MCI_TYPE_EXYNOS4412 ; 
 scalar_t__ DW_MCI_TYPE_EXYNOS7 ; 
 scalar_t__ DW_MCI_TYPE_EXYNOS7_SMU ; 
 scalar_t__ EXYNOS4210_FIXED_CIU_CLK_DIV ; 
 scalar_t__ EXYNOS4412_FIXED_CIU_CLK_DIV ; 
 scalar_t__ SDMMC_CLKSEL_GET_DIV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 dw_mci_exynos_get_ciu_div(struct dw_mci *host)
{
	struct dw_mci_exynos_priv_data *priv = host->priv;

	if (priv->ctrl_type == DW_MCI_TYPE_EXYNOS4412)
		return EXYNOS4412_FIXED_CIU_CLK_DIV;
	else if (priv->ctrl_type == DW_MCI_TYPE_EXYNOS4210)
		return EXYNOS4210_FIXED_CIU_CLK_DIV;
	else if (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
			priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		return SDMMC_CLKSEL_GET_DIV(mci_readl(host, CLKSEL64)) + 1;
	else
		return SDMMC_CLKSEL_GET_DIV(mci_readl(host, CLKSEL)) + 1;
}