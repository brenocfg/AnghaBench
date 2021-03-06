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
struct sdhci_pci_slot {int /*<<< orphan*/  (* hw_reset ) (struct sdhci_host*) ;} ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 struct sdhci_pci_slot* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  stub1 (struct sdhci_host*) ; 

__attribute__((used)) static void sdhci_pci_hw_reset(struct sdhci_host *host)
{
	struct sdhci_pci_slot *slot = sdhci_priv(host);

	if (slot->hw_reset)
		slot->hw_reset(host);
}