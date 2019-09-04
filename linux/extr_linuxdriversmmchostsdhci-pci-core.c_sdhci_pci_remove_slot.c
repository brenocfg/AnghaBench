#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sdhci_pci_slot {TYPE_4__* host; TYPE_3__* data; TYPE_2__* chip; } ;
struct TYPE_9__ {scalar_t__ ioaddr; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* cleanup ) (TYPE_3__*) ;} ;
struct TYPE_7__ {TYPE_1__* fixes; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* remove_slot ) (struct sdhci_pci_slot*,int) ;} ;

/* Variables and functions */
 scalar_t__ SDHCI_INT_STATUS ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  sdhci_free_host (TYPE_4__*) ; 
 int /*<<< orphan*/  sdhci_pci_remove_own_cd (struct sdhci_pci_slot*) ; 
 int /*<<< orphan*/  sdhci_remove_host (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub1 (struct sdhci_pci_slot*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void sdhci_pci_remove_slot(struct sdhci_pci_slot *slot)
{
	int dead;
	u32 scratch;

	sdhci_pci_remove_own_cd(slot);

	dead = 0;
	scratch = readl(slot->host->ioaddr + SDHCI_INT_STATUS);
	if (scratch == (u32)-1)
		dead = 1;

	sdhci_remove_host(slot->host, dead);

	if (slot->chip->fixes && slot->chip->fixes->remove_slot)
		slot->chip->fixes->remove_slot(slot, dead);

	if (slot->data && slot->data->cleanup)
		slot->data->cleanup(slot->data);

	sdhci_free_host(slot->host);
}