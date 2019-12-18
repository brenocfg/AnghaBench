#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ulp_fw_name; int /*<<< orphan*/  fw_name; } ;
struct TYPE_9__ {TYPE_2__ read_rev; } ;
struct lpfc_mqe {TYPE_3__ un; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_10__ {int mbxCommand; } ;
struct TYPE_7__ {struct lpfc_mqe mqe; TYPE_4__ mb; } ;
struct TYPE_11__ {TYPE_1__ u; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
#define  MBX_READ_REV 128 
 int /*<<< orphan*/  lpfc_sli_pcimem_bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
lpfc_sli4_swap_str(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb = &pmb->u.mb;
	struct lpfc_mqe *mqe;

	switch (mb->mbxCommand) {
	case  MBX_READ_REV:
		 mqe = &pmb->u.mqe;
		lpfc_sli_pcimem_bcopy(mqe->un.read_rev.fw_name,
				 mqe->un.read_rev.fw_name, 16);
		lpfc_sli_pcimem_bcopy(mqe->un.read_rev.ulp_fw_name,
				 mqe->un.read_rev.ulp_fw_name, 16);
		break;
	default:
		break;
	}
	return;
}