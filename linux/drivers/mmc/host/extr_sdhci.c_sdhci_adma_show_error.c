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
struct sdhci_host {int flags; scalar_t__ desc_sz; scalar_t__ adma_addr; void* adma_table; } ;
struct sdhci_adma2_64_desc {int len; int cmd; int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  addr_hi; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADMA2_END ; 
 int /*<<< orphan*/  SDHCI_DUMP (char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int SDHCI_USE_64_BIT_DMA ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_host*) ; 

__attribute__((used)) static void sdhci_adma_show_error(struct sdhci_host *host)
{
	void *desc = host->adma_table;
	dma_addr_t dma = host->adma_addr;

	sdhci_dumpregs(host);

	while (true) {
		struct sdhci_adma2_64_desc *dma_desc = desc;

		if (host->flags & SDHCI_USE_64_BIT_DMA)
			SDHCI_DUMP("%08llx: DMA 0x%08x%08x, LEN 0x%04x, Attr=0x%02x\n",
			    (unsigned long long)dma,
			    le32_to_cpu(dma_desc->addr_hi),
			    le32_to_cpu(dma_desc->addr_lo),
			    le16_to_cpu(dma_desc->len),
			    le16_to_cpu(dma_desc->cmd));
		else
			SDHCI_DUMP("%08llx: DMA 0x%08x, LEN 0x%04x, Attr=0x%02x\n",
			    (unsigned long long)dma,
			    le32_to_cpu(dma_desc->addr_lo),
			    le16_to_cpu(dma_desc->len),
			    le16_to_cpu(dma_desc->cmd));

		desc += host->desc_sz;
		dma += host->desc_sz;

		if (dma_desc->cmd & cpu_to_le16(ADMA2_END))
			break;
	}
}