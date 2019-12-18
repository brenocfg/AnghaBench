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
typedef  int u32 ;
struct uniphier_sd_priv {unsigned int clk_rate; int caps; } ;
struct tmio_mmc_host {scalar_t__ ctl; } ;

/* Variables and functions */
 int CLK_CTL_DIV_MASK ; 
 int CLK_CTL_SCLKEN ; 
 int CTL_SD_CARD_CLK_CTL ; 
 int UNIPHIER_SD_CAP_EXTENDED_IP ; 
 int UNIPHIER_SD_CLK_CTL_DIV1 ; 
 int UNIPHIER_SD_CLK_CTL_DIV1024 ; 
 int readl (scalar_t__) ; 
 int roundup_pow_of_two (unsigned long) ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_sd_set_clock(struct tmio_mmc_host *host,
				  unsigned int clock)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);
	unsigned long divisor;
	u32 tmp;

	tmp = readl(host->ctl + (CTL_SD_CARD_CLK_CTL << 1));

	/* stop the clock before changing its rate to avoid a glitch signal */
	tmp &= ~CLK_CTL_SCLKEN;
	writel(tmp, host->ctl + (CTL_SD_CARD_CLK_CTL << 1));

	if (clock == 0)
		return;

	tmp &= ~UNIPHIER_SD_CLK_CTL_DIV1024;
	tmp &= ~UNIPHIER_SD_CLK_CTL_DIV1;
	tmp &= ~CLK_CTL_DIV_MASK;

	divisor = priv->clk_rate / clock;

	/*
	 * In the original IP, bit[7:0] represents the divisor.
	 * bit7 set: 1/512, ... bit0 set:1/4, all bits clear: 1/2
	 *
	 * The IP does not define a way to achieve 1/1.  For UniPhier variants,
	 * bit10 is used for 1/1.  Newer versions of UniPhier variants use
	 * bit16 for 1/1024.
	 */
	if (divisor <= 1)
		tmp |= UNIPHIER_SD_CLK_CTL_DIV1;
	else if (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP && divisor > 512)
		tmp |= UNIPHIER_SD_CLK_CTL_DIV1024;
	else
		tmp |= roundup_pow_of_two(divisor) >> 2;

	writel(tmp, host->ctl + (CTL_SD_CARD_CLK_CTL << 1));

	tmp |= CLK_CTL_SCLKEN;
	writel(tmp, host->ctl + (CTL_SD_CARD_CLK_CTL << 1));
}