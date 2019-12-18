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
struct sdhci_host {scalar_t__ v4_mode; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_DMA_ADDRESS ; 
 int /*<<< orphan*/  sdhci_set_adma_addr (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_set_sdma_addr(struct sdhci_host *host, dma_addr_t addr)
{
	if (host->v4_mode)
		sdhci_set_adma_addr(host, addr);
	else
		sdhci_writel(host, addr, SDHCI_DMA_ADDRESS);
}