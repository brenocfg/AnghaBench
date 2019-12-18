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
struct scsi_cmnd {TYPE_2__* device; } ;
struct sas_task {int dummy; } ;
struct sas_internal {TYPE_1__* dft; } ;
struct domain_device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; int /*<<< orphan*/  host_eh_scheduled; int /*<<< orphan*/  transportt; } ;
struct TYPE_4__ {struct Scsi_Host* host; } ;
struct TYPE_3__ {int (* lldd_abort_task ) (struct sas_task*) ;} ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_FAILED ; 
 int TMF_RESP_FUNC_SUCC ; 
 struct sas_task* TO_SAS_TASK (struct scsi_cmnd*) ; 
 struct domain_device* cmd_to_domain_dev (struct scsi_cmnd*) ; 
 scalar_t__ dev_is_sata (struct domain_device*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int stub1 (struct sas_task*) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

int sas_eh_abort_handler(struct scsi_cmnd *cmd)
{
	int res = TMF_RESP_FUNC_FAILED;
	struct sas_task *task = TO_SAS_TASK(cmd);
	struct Scsi_Host *host = cmd->device->host;
	struct domain_device *dev = cmd_to_domain_dev(cmd);
	struct sas_internal *i = to_sas_internal(host->transportt);
	unsigned long flags;

	if (!i->dft->lldd_abort_task)
		return FAILED;

	spin_lock_irqsave(host->host_lock, flags);
	/* We cannot do async aborts for SATA devices */
	if (dev_is_sata(dev) && !host->host_eh_scheduled) {
		spin_unlock_irqrestore(host->host_lock, flags);
		return FAILED;
	}
	spin_unlock_irqrestore(host->host_lock, flags);

	if (task)
		res = i->dft->lldd_abort_task(task);
	else
		pr_notice("no task to abort\n");
	if (res == TMF_RESP_FUNC_SUCC || res == TMF_RESP_FUNC_COMPLETE)
		return SUCCESS;

	return FAILED;
}