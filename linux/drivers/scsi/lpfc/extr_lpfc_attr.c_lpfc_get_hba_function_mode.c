#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lpfc_hba {int /*<<< orphan*/  hba_flag; TYPE_1__* pcidev; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBA_FCOE_MODE ; 
 scalar_t__ PCI_DEVICE_ID_SKYHAWK ; 

__attribute__((used)) static void
lpfc_get_hba_function_mode(struct lpfc_hba *phba)
{
	/* If it's a SkyHawk FCoE adapter */
	if (phba->pcidev->device == PCI_DEVICE_ID_SKYHAWK)
		phba->hba_flag |= HBA_FCOE_MODE;
	else
		phba->hba_flag &= ~HBA_FCOE_MODE;
}