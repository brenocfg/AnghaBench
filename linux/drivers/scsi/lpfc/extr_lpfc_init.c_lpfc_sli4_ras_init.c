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
struct TYPE_4__ {int ras_hwsupport; int ras_enabled; } ;
struct lpfc_hba {TYPE_2__ ras_fwlog; int /*<<< orphan*/  cfg_ras_fwlog_buffsize; TYPE_1__* pcidev; int /*<<< orphan*/  cfg_ras_fwlog_func; } ;
struct TYPE_3__ {int device; int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
#define  PCI_DEVICE_ID_LANCER_G6_FC 129 
#define  PCI_DEVICE_ID_LANCER_G7_FC 128 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 

void
lpfc_sli4_ras_init(struct lpfc_hba *phba)
{
	switch (phba->pcidev->device) {
	case PCI_DEVICE_ID_LANCER_G6_FC:
	case PCI_DEVICE_ID_LANCER_G7_FC:
		phba->ras_fwlog.ras_hwsupport = true;
		if (phba->cfg_ras_fwlog_func == PCI_FUNC(phba->pcidev->devfn) &&
		    phba->cfg_ras_fwlog_buffsize)
			phba->ras_fwlog.ras_enabled = true;
		else
			phba->ras_fwlog.ras_enabled = false;
		break;
	default:
		phba->ras_fwlog.ras_hwsupport = false;
	}
}