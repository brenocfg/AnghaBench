#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_work_evt {int /*<<< orphan*/  evt_listp; int /*<<< orphan*/  evt; void* evt_arg2; void* evt_arg1; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  work_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct lpfc_work_evt* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_worker_wake_up (struct lpfc_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
lpfc_workq_post_event(struct lpfc_hba *phba, void *arg1, void *arg2,
		      uint32_t evt)
{
	struct lpfc_work_evt  *evtp;
	unsigned long flags;

	/*
	 * All Mailbox completions and LPFC_ELS_RING rcv ring IOCB events will
	 * be queued to worker thread for processing
	 */
	evtp = kmalloc(sizeof(struct lpfc_work_evt), GFP_ATOMIC);
	if (!evtp)
		return 0;

	evtp->evt_arg1  = arg1;
	evtp->evt_arg2  = arg2;
	evtp->evt       = evt;

	spin_lock_irqsave(&phba->hbalock, flags);
	list_add_tail(&evtp->evt_listp, &phba->work_list);
	spin_unlock_irqrestore(&phba->hbalock, flags);

	lpfc_worker_wake_up(phba);

	return 1;
}