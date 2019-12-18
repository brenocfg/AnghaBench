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
struct mmc_host {int dummy; } ;
struct dw_mci_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dw_mci_enable_sdio_irq (struct dw_mci_slot*,int) ; 
 struct dw_mci_slot* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void dw_mci_ack_sdio_irq(struct mmc_host *mmc)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);

	__dw_mci_enable_sdio_irq(slot, 1);
}