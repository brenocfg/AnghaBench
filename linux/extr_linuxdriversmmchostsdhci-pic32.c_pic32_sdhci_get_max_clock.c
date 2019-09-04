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
struct sdhci_host {int dummy; } ;
struct pic32_sdhci_priv {int /*<<< orphan*/  base_clk; } ;

/* Variables and functions */
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct pic32_sdhci_priv* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static unsigned int pic32_sdhci_get_max_clock(struct sdhci_host *host)
{
	struct pic32_sdhci_priv *sdhci_pdata = sdhci_priv(host);

	return clk_get_rate(sdhci_pdata->base_clk);
}