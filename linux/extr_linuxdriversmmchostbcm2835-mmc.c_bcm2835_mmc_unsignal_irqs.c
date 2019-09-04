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
struct bcm2835_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  bcm2835_mmc_readl (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_writel (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm2835_mmc_unsignal_irqs(struct bcm2835_host *host, u32 clear)
{
	u32 ier;

	ier = bcm2835_mmc_readl(host, SDHCI_SIGNAL_ENABLE);
	ier &= ~clear;
	/* change which requests generate IRQs - makes no difference to
	   the content of SDHCI_INT_STATUS, or the need to acknowledge IRQs */
	bcm2835_mmc_writel(host, ier, SDHCI_SIGNAL_ENABLE, 2);
}