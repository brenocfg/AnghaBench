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
typedef  int u32 ;
struct dw_mci_exynos_priv_data {scalar_t__ ctrl_type; } ;
struct dw_mci {struct dw_mci_exynos_priv_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKSEL ; 
 int /*<<< orphan*/  CLKSEL64 ; 
 scalar_t__ DW_MCI_TYPE_EXYNOS7 ; 
 scalar_t__ DW_MCI_TYPE_EXYNOS7_SMU ; 
 int SDMMC_CLKSEL_UP_SAMPLE (int,int) ; 
 int mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u8 dw_mci_exynos_move_next_clksmpl(struct dw_mci *host)
{
	struct dw_mci_exynos_priv_data *priv = host->priv;
	u32 clksel;
	u8 sample;

	if (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		clksel = mci_readl(host, CLKSEL64);
	else
		clksel = mci_readl(host, CLKSEL);

	sample = (clksel + 1) & 0x7;
	clksel = SDMMC_CLKSEL_UP_SAMPLE(clksel, sample);

	if (priv->ctrl_type == DW_MCI_TYPE_EXYNOS7 ||
		priv->ctrl_type == DW_MCI_TYPE_EXYNOS7_SMU)
		mci_writel(host, CLKSEL64, clksel);
	else
		mci_writel(host, CLKSEL, clksel);

	return sample;
}