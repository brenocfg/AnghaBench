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
typedef  int u64 ;
typedef  int u32 ;
struct sdhci_host {int flags; } ;
struct sdhci_adma2_64_desc {void* addr_hi; void* addr_lo; void* len; void* cmd; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int SDHCI_USE_64_BIT_DMA ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void sdhci_adma_write_desc(struct sdhci_host *host, void *desc,
				  dma_addr_t addr, int len, unsigned cmd)
{
	struct sdhci_adma2_64_desc *dma_desc = desc;

	/* 32-bit and 64-bit descriptors have these members in same position */
	dma_desc->cmd = cpu_to_le16(cmd);
	dma_desc->len = cpu_to_le16(len);
	dma_desc->addr_lo = cpu_to_le32((u32)addr);

	if (host->flags & SDHCI_USE_64_BIT_DMA)
		dma_desc->addr_hi = cpu_to_le32((u64)addr >> 32);
}