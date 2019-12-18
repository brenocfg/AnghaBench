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
struct sdhci_sprd_host {int /*<<< orphan*/  clk_sdio; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 struct sdhci_sprd_host* TO_SPRD_HOST (struct sdhci_host*) ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 unsigned int clk_round_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int sdhci_sprd_get_max_clock(struct sdhci_host *host)
{
	struct sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);

	return clk_round_rate(sprd_host->clk_sdio, ULONG_MAX);
}