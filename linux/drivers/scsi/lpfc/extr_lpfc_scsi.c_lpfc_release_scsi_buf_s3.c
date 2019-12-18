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
struct TYPE_2__ {int /*<<< orphan*/  iocb_flag; } ;
struct lpfc_io_buf {int /*<<< orphan*/  list; TYPE_1__ cur_iocbq; int /*<<< orphan*/ * pCmd; scalar_t__ prot_seg_cnt; scalar_t__ seg_cnt; } ;
struct lpfc_hba {int /*<<< orphan*/  scsi_buf_list_put_lock; int /*<<< orphan*/  lpfc_scsi_buf_list_put; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_IO_FCP ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lpfc_release_scsi_buf_s3(struct lpfc_hba *phba, struct lpfc_io_buf *psb)
{
	unsigned long iflag = 0;

	psb->seg_cnt = 0;
	psb->prot_seg_cnt = 0;

	spin_lock_irqsave(&phba->scsi_buf_list_put_lock, iflag);
	psb->pCmd = NULL;
	psb->cur_iocbq.iocb_flag = LPFC_IO_FCP;
	list_add_tail(&psb->list, &phba->lpfc_scsi_buf_list_put);
	spin_unlock_irqrestore(&phba->scsi_buf_list_put_lock, iflag);
}