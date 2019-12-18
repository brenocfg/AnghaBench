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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_HLWD_WRITE_DELAY ; 
 int /*<<< orphan*/  sdhci_be32bs_writel (struct sdhci_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_hlwd_writel(struct sdhci_host *host, u32 val, int reg)
{
	sdhci_be32bs_writel(host, val, reg);
	udelay(SDHCI_HLWD_WRITE_DELAY);
}