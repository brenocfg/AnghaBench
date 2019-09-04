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
struct pxamci_host {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO_INT ; 
 struct pxamci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pxamci_disable_irq (struct pxamci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxamci_enable_irq (struct pxamci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxamci_enable_sdio_irq(struct mmc_host *host, int enable)
{
	struct pxamci_host *pxa_host = mmc_priv(host);

	if (enable)
		pxamci_enable_irq(pxa_host, SDIO_INT);
	else
		pxamci_disable_irq(pxa_host, SDIO_INT);
}