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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_host {int /*<<< orphan*/  mmc; scalar_t__ ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 sdhci_iproc_readl(struct sdhci_host *host, int reg)
{
	u32 val = readl(host->ioaddr + reg);

	pr_debug("%s: readl [0x%02x] 0x%08x\n",
		 mmc_hostname(host->mmc), reg, val);
	return val;
}