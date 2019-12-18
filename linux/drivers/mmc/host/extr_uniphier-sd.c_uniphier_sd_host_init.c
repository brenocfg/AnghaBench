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
struct uniphier_sd_priv {int caps; } ;
struct tmio_mmc_host {scalar_t__ ctl; } ;

/* Variables and functions */
 int CTL_SD_CARD_CLK_CTL ; 
 int UNIPHIER_SD_CAP_EXTENDED_IP ; 
 int UNIPHIER_SD_CLKCTL_OFFEN ; 
 scalar_t__ UNIPHIER_SD_HOST_MODE ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_sd_host_init(struct tmio_mmc_host *host)
{
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);
	u32 val;

	/*
	 * Connected to 32bit AXI.
	 * This register holds settings for SoC-specific internal bus
	 * connection.  What is worse, the register spec was changed,
	 * breaking the backward compatibility.  Write an appropriate
	 * value depending on a flag associated with a compatible string.
	 */
	if (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP)
		val = 0x00000101;
	else
		val = 0x00000000;

	writel(val, host->ctl + UNIPHIER_SD_HOST_MODE);

	val = 0;
	/*
	 * If supported, the controller can automatically
	 * enable/disable the clock line to the card.
	 */
	if (priv->caps & UNIPHIER_SD_CAP_EXTENDED_IP)
		val |= UNIPHIER_SD_CLKCTL_OFFEN;

	writel(val, host->ctl + (CTL_SD_CARD_CLK_CTL << 1));
}