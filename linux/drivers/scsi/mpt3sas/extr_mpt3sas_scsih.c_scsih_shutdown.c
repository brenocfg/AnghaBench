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
struct workqueue_struct {int dummy; } ;
struct pci_dev {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct MPT3SAS_ADAPTER {int remove_host; int /*<<< orphan*/  ioc_pg1_copy; scalar_t__ is_aero_ioc; int /*<<< orphan*/  fw_event_lock; struct workqueue_struct* firmware_event_thread; } ;
typedef  int /*<<< orphan*/  Mpi2ConfigReply_t ;

/* Variables and functions */
 int /*<<< orphan*/  _scsih_flush_running_cmds (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  _scsih_fw_event_cleanup_queue (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  _scsih_ir_shutdown (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  mpt3sas_base_detach (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  mpt3sas_config_set_ioc_pg1 (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt3sas_wait_for_commands_to_complete (struct MPT3SAS_ADAPTER*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 struct MPT3SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
scsih_shutdown(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct MPT3SAS_ADAPTER *ioc = shost_priv(shost);
	struct workqueue_struct	*wq;
	unsigned long flags;
	Mpi2ConfigReply_t mpi_reply;

	ioc->remove_host = 1;

	mpt3sas_wait_for_commands_to_complete(ioc);
	_scsih_flush_running_cmds(ioc);

	_scsih_fw_event_cleanup_queue(ioc);

	spin_lock_irqsave(&ioc->fw_event_lock, flags);
	wq = ioc->firmware_event_thread;
	ioc->firmware_event_thread = NULL;
	spin_unlock_irqrestore(&ioc->fw_event_lock, flags);
	if (wq)
		destroy_workqueue(wq);
	/*
	 * Copy back the unmodified ioc page1 so that on next driver load,
	 * current modified changes on ioc page1 won't take effect.
	 */
	if (ioc->is_aero_ioc)
		mpt3sas_config_set_ioc_pg1(ioc, &mpi_reply,
				&ioc->ioc_pg1_copy);

	_scsih_ir_shutdown(ioc);
	mpt3sas_base_detach(ioc);
}