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
struct lpfc_hba {scalar_t__ link_state; int /*<<< orphan*/  hb_tmofunc; TYPE_1__* pport; int /*<<< orphan*/  mbox_mem_pool; int /*<<< orphan*/  hbalock; scalar_t__ hb_outstanding; } ;
struct TYPE_2__ {int fc_flag; int load_flag; } ;
typedef  int /*<<< orphan*/  LPFC_MBOXQ_t ;

/* Variables and functions */
 int FC_OFFLINE_MODE ; 
 int FC_UNLOADING ; 
 scalar_t__ LPFC_HBA_ERROR ; 
 int LPFC_HB_MBOX_INTERVAL ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mempool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
lpfc_hb_mbox_cmpl(struct lpfc_hba * phba, LPFC_MBOXQ_t * pmboxq)
{
	unsigned long drvr_flag;

	spin_lock_irqsave(&phba->hbalock, drvr_flag);
	phba->hb_outstanding = 0;
	spin_unlock_irqrestore(&phba->hbalock, drvr_flag);

	/* Check and reset heart-beat timer is necessary */
	mempool_free(pmboxq, phba->mbox_mem_pool);
	if (!(phba->pport->fc_flag & FC_OFFLINE_MODE) &&
		!(phba->link_state == LPFC_HBA_ERROR) &&
		!(phba->pport->load_flag & FC_UNLOADING))
		mod_timer(&phba->hb_tmofunc,
			  jiffies +
			  msecs_to_jiffies(1000 * LPFC_HB_MBOX_INTERVAL));
	return;
}