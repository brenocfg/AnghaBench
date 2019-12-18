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
typedef  int u16 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ CLKFBOUT_100_MHZ ; 
 scalar_t__ CLKFBOUT_200_MHZ ; 
 scalar_t__ DIV_REG_100_MHZ ; 
 scalar_t__ DIV_REG_200_MHZ ; 
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_CLOCK_INT_EN ; 
 int SDHCI_PROG_CLOCK_MODE ; 
 int /*<<< orphan*/  SDHCI_VENDOR_PTR_R ; 
 scalar_t__ SDHC_AT_CTRL_R ; 
 scalar_t__ SDHC_CCLK_MMCM_RST ; 
 scalar_t__ SDHC_GPIO_OUT ; 
 scalar_t__ SDHC_MMCM_CLKFBOUT ; 
 scalar_t__ SDHC_MMCM_DIV_REG ; 
 scalar_t__ SDHC_SW_TUNE_EN ; 
 scalar_t__ sdhci_readl (struct sdhci_host*,scalar_t__) ; 
 scalar_t__ sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_set_clock (struct sdhci_host*,unsigned int) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_snps_set_clock(struct sdhci_host *host, unsigned int clock)
{
	u16 clk;
	u32 reg, vendor_ptr;

	vendor_ptr = sdhci_readw(host, SDHCI_VENDOR_PTR_R);

	/* Disable software managed rx tuning */
	reg = sdhci_readl(host, (SDHC_AT_CTRL_R + vendor_ptr));
	reg &= ~SDHC_SW_TUNE_EN;
	sdhci_writel(host, reg, (SDHC_AT_CTRL_R + vendor_ptr));

	if (clock <= 52000000) {
		sdhci_set_clock(host, clock);
	} else {
		/* Assert reset to MMCM */
		reg = sdhci_readl(host, (SDHC_GPIO_OUT + vendor_ptr));
		reg |= SDHC_CCLK_MMCM_RST;
		sdhci_writel(host, reg, (SDHC_GPIO_OUT + vendor_ptr));

		/* Configure MMCM */
		if (clock == 100000000) {
			sdhci_writel(host, DIV_REG_100_MHZ, SDHC_MMCM_DIV_REG);
			sdhci_writel(host, CLKFBOUT_100_MHZ,
					SDHC_MMCM_CLKFBOUT);
		} else {
			sdhci_writel(host, DIV_REG_200_MHZ, SDHC_MMCM_DIV_REG);
			sdhci_writel(host, CLKFBOUT_200_MHZ,
					SDHC_MMCM_CLKFBOUT);
		}

		/* De-assert reset to MMCM */
		reg = sdhci_readl(host, (SDHC_GPIO_OUT + vendor_ptr));
		reg &= ~SDHC_CCLK_MMCM_RST;
		sdhci_writel(host, reg, (SDHC_GPIO_OUT + vendor_ptr));

		/* Enable clock */
		clk = SDHCI_PROG_CLOCK_MODE | SDHCI_CLOCK_INT_EN |
			SDHCI_CLOCK_CARD_EN;
		sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
	}
}