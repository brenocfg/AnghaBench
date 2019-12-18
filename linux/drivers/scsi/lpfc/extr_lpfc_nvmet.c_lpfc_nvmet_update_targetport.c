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
struct lpfc_vport {int /*<<< orphan*/  fc_myDID; } ;
struct lpfc_hba {TYPE_1__* targetport; struct lpfc_vport* pport; } ;
struct TYPE_2__ {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
lpfc_nvmet_update_targetport(struct lpfc_hba *phba)
{
	struct lpfc_vport  *vport = phba->pport;

	if (!phba->targetport)
		return 0;

	lpfc_printf_vlog(vport, KERN_INFO, LOG_NVME,
			 "6007 Update NVMET port x%px did x%x\n",
			 phba->targetport, vport->fc_myDID);

	phba->targetport->port_id = vport->fc_myDID;
	return 0;
}