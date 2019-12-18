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
struct pci_dev {int dummy; } ;
struct ipr_ioa_cfg {int hrrq_num; scalar_t__ sdt_state; TYPE_2__* host; int /*<<< orphan*/  queue; int /*<<< orphan*/  used_res_q; scalar_t__ reset_work_q; int /*<<< orphan*/  work_q; scalar_t__ in_reset_reload; int /*<<< orphan*/  reset_wait_q; TYPE_1__* hrrq; } ;
struct TYPE_4__ {int /*<<< orphan*/ * host_lock; } ;
struct TYPE_3__ {int removing_ioa; int /*<<< orphan*/  _lock; } ;

/* Variables and functions */
 scalar_t__ ABORT_DUMP ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPR_SHUTDOWN_NORMAL ; 
 int /*<<< orphan*/  LEAVE ; 
 scalar_t__ WAIT_FOR_DUMP ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  ipr_driver_lock ; 
 int /*<<< orphan*/  ipr_free_all_resources (struct ipr_ioa_cfg*) ; 
 int /*<<< orphan*/  ipr_initiate_ioa_bringdown (struct ipr_ioa_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct ipr_ioa_cfg* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void __ipr_remove(struct pci_dev *pdev)
{
	unsigned long host_lock_flags = 0;
	struct ipr_ioa_cfg *ioa_cfg = pci_get_drvdata(pdev);
	int i;
	unsigned long driver_lock_flags;
	ENTER;

	spin_lock_irqsave(ioa_cfg->host->host_lock, host_lock_flags);
	while (ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, host_lock_flags);
		wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, host_lock_flags);
	}

	for (i = 0; i < ioa_cfg->hrrq_num; i++) {
		spin_lock(&ioa_cfg->hrrq[i]._lock);
		ioa_cfg->hrrq[i].removing_ioa = 1;
		spin_unlock(&ioa_cfg->hrrq[i]._lock);
	}
	wmb();
	ipr_initiate_ioa_bringdown(ioa_cfg, IPR_SHUTDOWN_NORMAL);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, host_lock_flags);
	wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);
	flush_work(&ioa_cfg->work_q);
	if (ioa_cfg->reset_work_q)
		flush_workqueue(ioa_cfg->reset_work_q);
	INIT_LIST_HEAD(&ioa_cfg->used_res_q);
	spin_lock_irqsave(ioa_cfg->host->host_lock, host_lock_flags);

	spin_lock_irqsave(&ipr_driver_lock, driver_lock_flags);
	list_del(&ioa_cfg->queue);
	spin_unlock_irqrestore(&ipr_driver_lock, driver_lock_flags);

	if (ioa_cfg->sdt_state == ABORT_DUMP)
		ioa_cfg->sdt_state = WAIT_FOR_DUMP;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, host_lock_flags);

	ipr_free_all_resources(ioa_cfg);

	LEAVE;
}