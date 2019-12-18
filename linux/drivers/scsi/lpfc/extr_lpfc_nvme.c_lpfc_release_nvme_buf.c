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
struct lpfc_sli4_hdw_queue {int /*<<< orphan*/  abts_io_buf_list_lock; int /*<<< orphan*/  abts_nvme_io_bufs; int /*<<< orphan*/  lpfc_abts_io_buf_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  iotag; int /*<<< orphan*/  sli4_xritag; } ;
struct lpfc_io_buf {int flags; int /*<<< orphan*/  list; TYPE_2__ cur_iocbq; struct lpfc_sli4_hdw_queue* hdwq; TYPE_1__* ndlp; } ;
struct lpfc_hba {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NVME_ABTS ; 
 int LPFC_SBUF_BUMP_QDEPTH ; 
 int LPFC_SBUF_XBUSY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_release_io_buf (struct lpfc_hba*,struct lpfc_io_buf*,struct lpfc_sli4_hdw_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lpfc_release_nvme_buf(struct lpfc_hba *phba, struct lpfc_io_buf *lpfc_ncmd)
{
	struct lpfc_sli4_hdw_queue *qp;
	unsigned long iflag = 0;

	if ((lpfc_ncmd->flags & LPFC_SBUF_BUMP_QDEPTH) && lpfc_ncmd->ndlp)
		atomic_dec(&lpfc_ncmd->ndlp->cmd_pending);

	lpfc_ncmd->ndlp = NULL;
	lpfc_ncmd->flags &= ~LPFC_SBUF_BUMP_QDEPTH;

	qp = lpfc_ncmd->hdwq;
	if (lpfc_ncmd->flags & LPFC_SBUF_XBUSY) {
		lpfc_printf_log(phba, KERN_INFO, LOG_NVME_ABTS,
				"6310 XB release deferred for "
				"ox_id x%x on reqtag x%x\n",
				lpfc_ncmd->cur_iocbq.sli4_xritag,
				lpfc_ncmd->cur_iocbq.iotag);

		spin_lock_irqsave(&qp->abts_io_buf_list_lock, iflag);
		list_add_tail(&lpfc_ncmd->list,
			&qp->lpfc_abts_io_buf_list);
		qp->abts_nvme_io_bufs++;
		spin_unlock_irqrestore(&qp->abts_io_buf_list_lock, iflag);
	} else
		lpfc_release_io_buf(phba, (struct lpfc_io_buf *)lpfc_ncmd, qp);
}