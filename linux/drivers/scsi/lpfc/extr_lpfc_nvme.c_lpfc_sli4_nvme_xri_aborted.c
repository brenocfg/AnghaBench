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
typedef  int /*<<< orphan*/  uint16_t ;
struct sli4_wcqe_xri_aborted {int dummy; } ;
struct nvmefc_fcp_req {int /*<<< orphan*/  (* done ) (struct nvmefc_fcp_req*) ;} ;
struct lpfc_nodelist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iotag; } ;
struct lpfc_io_buf {struct nvmefc_fcp_req* nvmeCmd; TYPE_1__ cur_iocbq; struct lpfc_nodelist* ndlp; } ;
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_ABTS ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,struct sli4_wcqe_xri_aborted*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct nvmefc_fcp_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_release_nvme_buf (struct lpfc_hba*,struct lpfc_io_buf*) ; 
 int /*<<< orphan*/  lpfc_sli4_abts_err_handler (struct lpfc_hba*,struct lpfc_nodelist*,struct sli4_wcqe_xri_aborted*) ; 
 int /*<<< orphan*/  lpfc_wcqe_xa_xri ; 
 int /*<<< orphan*/  stub1 (struct nvmefc_fcp_req*) ; 

void
lpfc_sli4_nvme_xri_aborted(struct lpfc_hba *phba,
			   struct sli4_wcqe_xri_aborted *axri,
			   struct lpfc_io_buf *lpfc_ncmd)
{
	uint16_t xri = bf_get(lpfc_wcqe_xa_xri, axri);
	struct nvmefc_fcp_req *nvme_cmd = NULL;
	struct lpfc_nodelist *ndlp = lpfc_ncmd->ndlp;


	if (ndlp)
		lpfc_sli4_abts_err_handler(phba, ndlp, axri);

	lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
			"6311 nvme_cmd %p xri x%x tag x%x abort complete and "
			"xri released\n",
			lpfc_ncmd->nvmeCmd, xri,
			lpfc_ncmd->cur_iocbq.iotag);

	/* Aborted NVME commands are required to not complete
	 * before the abort exchange command fully completes.
	 * Once completed, it is available via the put list.
	 */
	if (lpfc_ncmd->nvmeCmd) {
		nvme_cmd = lpfc_ncmd->nvmeCmd;
		nvme_cmd->done(nvme_cmd);
		lpfc_ncmd->nvmeCmd = NULL;
	}
	lpfc_release_nvme_buf(phba, lpfc_ncmd);
}