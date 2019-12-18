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
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int SDHCI_INT_ENABLE ; 
 int SDHCI_MAX_CURRENT ; 
 int SDHCI_SIGNAL_ENABLE ; 
 int SDHCI_SPRD_INT_SIGNAL_MASK ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void sdhci_sprd_writel(struct sdhci_host *host, u32 val, int reg)
{
	/* SDHCI_MAX_CURRENT is reserved on Spreadtrum's platform */
	if (unlikely(reg == SDHCI_MAX_CURRENT))
		return;

	if (unlikely(reg == SDHCI_SIGNAL_ENABLE || reg == SDHCI_INT_ENABLE))
		val = val & SDHCI_SPRD_INT_SIGNAL_MASK;

	writel_relaxed(val, host->ioaddr + reg);
}