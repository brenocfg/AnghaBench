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
struct bcm2835_host {int shadow; } ;

/* Variables and functions */
 int SDHCI_COMMAND ; 
 int SDHCI_TRANSFER_MODE ; 
 int bcm2835_mmc_readl (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  bcm2835_mmc_writel (struct bcm2835_host*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm2835_mmc_writew(struct bcm2835_host *host, u16 val, int reg)
{
	u32 oldval = (reg == SDHCI_COMMAND) ? host->shadow :
		bcm2835_mmc_readl(host, reg & ~3);
	u32 word_num = (reg >> 1) & 1;
	u32 word_shift = word_num * 16;
	u32 mask = 0xffff << word_shift;
	u32 newval = (oldval & ~mask) | (val << word_shift);

	if (reg == SDHCI_TRANSFER_MODE)
		host->shadow = newval;
	else
		bcm2835_mmc_writel(host, newval, reg & ~3, 0);

}