#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/  mbox_mem_pool; } ;
struct TYPE_10__ {scalar_t__ portname; } ;
struct TYPE_11__ {TYPE_2__ varRDnvp; } ;
struct TYPE_12__ {TYPE_3__ un; } ;
struct TYPE_9__ {TYPE_4__ mb; int /*<<< orphan*/  mqe; } ;
struct TYPE_13__ {TYPE_1__ u; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  MBX_POLL ; 
 int MBX_SUCCESS ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_mqe_command ; 
 int /*<<< orphan*/  lpfc_mqe_status ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_read_nv (struct lpfc_hba*,TYPE_5__*) ; 
 int lpfc_sli_issue_mbox (struct lpfc_hba*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rol64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint64_t
lpfc_get_wwpn(struct lpfc_hba *phba)
{
	uint64_t wwn;
	int rc;
	LPFC_MBOXQ_t *mboxq;
	MAILBOX_t *mb;

	mboxq = (LPFC_MBOXQ_t *) mempool_alloc(phba->mbox_mem_pool,
						GFP_KERNEL);
	if (!mboxq)
		return (uint64_t)-1;

	/* First get WWN of HBA instance */
	lpfc_read_nv(phba, mboxq);
	rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_POLL);
	if (rc != MBX_SUCCESS) {
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"6019 Mailbox failed , mbxCmd x%x "
				"READ_NV, mbxStatus x%x\n",
				bf_get(lpfc_mqe_command, &mboxq->u.mqe),
				bf_get(lpfc_mqe_status, &mboxq->u.mqe));
		mempool_free(mboxq, phba->mbox_mem_pool);
		return (uint64_t) -1;
	}
	mb = &mboxq->u.mb;
	memcpy(&wwn, (char *)mb->un.varRDnvp.portname, sizeof(uint64_t));
	/* wwn is WWPN of HBA instance */
	mempool_free(mboxq, phba->mbox_mem_pool);
	if (phba->sli_rev == LPFC_SLI_REV4)
		return be64_to_cpu(wwn);
	else
		return rol64(wwn, 32);
}