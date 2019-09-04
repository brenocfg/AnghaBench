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
typedef  int u16 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_iproc_host {int shadow_cmd; int shadow_blk; scalar_t__ is_blk_shadowed; scalar_t__ is_cmd_shadowed; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int REG_OFFSET_IN_BITS (int) ; 
 int SDHCI_BLOCK_COUNT ; 
 int SDHCI_BLOCK_SIZE ; 
 int SDHCI_TRANSFER_MODE ; 
 int sdhci_iproc_readl (struct sdhci_host*,int) ; 
 struct sdhci_iproc_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static u16 sdhci_iproc_readw(struct sdhci_host *host, int reg)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_iproc_host *iproc_host = sdhci_pltfm_priv(pltfm_host);
	u32 val;
	u16 word;

	if ((reg == SDHCI_TRANSFER_MODE) && iproc_host->is_cmd_shadowed) {
		/* Get the saved transfer mode */
		val = iproc_host->shadow_cmd;
	} else if ((reg == SDHCI_BLOCK_SIZE || reg == SDHCI_BLOCK_COUNT) &&
		   iproc_host->is_blk_shadowed) {
		/* Get the saved block info */
		val = iproc_host->shadow_blk;
	} else {
		val = sdhci_iproc_readl(host, (reg & ~3));
	}
	word = val >> REG_OFFSET_IN_BITS(reg) & 0xffff;
	return word;
}