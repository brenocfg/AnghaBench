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
struct sdhci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  cqhci_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sdhci_cqe_irq (struct sdhci_host*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static u32 sdhci_arasan_cqhci_irq(struct sdhci_host *host, u32 intmask)
{
	int cmd_error = 0;
	int data_error = 0;

	if (!sdhci_cqe_irq(host, intmask, &cmd_error, &data_error))
		return intmask;

	cqhci_irq(host->mmc, intmask, cmd_error, data_error);

	return 0;
}