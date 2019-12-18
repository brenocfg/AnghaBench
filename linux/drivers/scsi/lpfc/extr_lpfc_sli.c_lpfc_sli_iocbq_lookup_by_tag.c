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
typedef  size_t uint16_t ;
struct lpfc_sli_ring {int /*<<< orphan*/  txcmplq_cnt; int /*<<< orphan*/  ring_lock; } ;
struct lpfc_iocbq {int iocb_flag; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {size_t last_iotag; struct lpfc_iocbq** iocbq_lookup; } ;
struct lpfc_hba {scalar_t__ sli_rev; TYPE_1__ sli; int /*<<< orphan*/  hbalock; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int LPFC_IO_ON_TXCMPLQ ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct lpfc_iocbq *
lpfc_sli_iocbq_lookup_by_tag(struct lpfc_hba *phba,
			     struct lpfc_sli_ring *pring, uint16_t iotag)
{
	struct lpfc_iocbq *cmd_iocb = NULL;
	spinlock_t *temp_lock = NULL;
	unsigned long iflag = 0;

	if (phba->sli_rev == LPFC_SLI_REV4)
		temp_lock = &pring->ring_lock;
	else
		temp_lock = &phba->hbalock;

	spin_lock_irqsave(temp_lock, iflag);
	if (iotag != 0 && iotag <= phba->sli.last_iotag) {
		cmd_iocb = phba->sli.iocbq_lookup[iotag];
		if (cmd_iocb->iocb_flag & LPFC_IO_ON_TXCMPLQ) {
			/* remove from txcmpl queue list */
			list_del_init(&cmd_iocb->list);
			cmd_iocb->iocb_flag &= ~LPFC_IO_ON_TXCMPLQ;
			pring->txcmplq_cnt--;
			spin_unlock_irqrestore(temp_lock, iflag);
			return cmd_iocb;
		}
	}

	spin_unlock_irqrestore(temp_lock, iflag);
	lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
			"0372 iotag x%x lookup error: max iotag (x%x) "
			"iocb_flag x%x\n",
			iotag, phba->sli.last_iotag,
			cmd_iocb ? cmd_iocb->iocb_flag : 0xffff);
	return NULL;
}