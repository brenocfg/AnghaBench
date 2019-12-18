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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool tegra_sdhci_configure_card_clk(struct sdhci_host *host, bool enable)
{
	bool status;
	u32 reg;

	reg = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	status = !!(reg & SDHCI_CLOCK_CARD_EN);

	if (status == enable)
		return status;

	if (enable)
		reg |= SDHCI_CLOCK_CARD_EN;
	else
		reg &= ~SDHCI_CLOCK_CARD_EN;

	sdhci_writew(host, reg, SDHCI_CLOCK_CONTROL);

	return status;
}