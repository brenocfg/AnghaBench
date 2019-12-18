#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sli_intr; } ;
struct TYPE_4__ {TYPE_1__ slistat; } ;
struct lpfc_hba {scalar_t__ link_state; TYPE_2__ sli; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ LPFC_LINK_DOWN ; 
 int pci_channel_offline (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int
lpfc_intr_state_check(struct lpfc_hba *phba)
{
	/* If the pci channel is offline, ignore all the interrupts */
	if (unlikely(pci_channel_offline(phba->pcidev)))
		return -EIO;

	/* Update device level interrupt statistics */
	phba->sli.slistat.sli_intr++;

	/* Ignore all interrupts during initialization. */
	if (unlikely(phba->link_state < LPFC_LINK_DOWN))
		return -EIO;

	return 0;
}