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
struct sdhci_host {int flags; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_ADMA_ADDRESS ; 
 int /*<<< orphan*/  SDHCI_ADMA_ADDRESS_HI ; 
 int SDHCI_USE_64_BIT_DMA ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_set_adma_addr(struct sdhci_host *host, dma_addr_t addr)
{
	sdhci_writel(host, lower_32_bits(addr), SDHCI_ADMA_ADDRESS);
	if (host->flags & SDHCI_USE_64_BIT_DMA)
		sdhci_writel(host, upper_32_bits(addr), SDHCI_ADMA_ADDRESS_HI);
}