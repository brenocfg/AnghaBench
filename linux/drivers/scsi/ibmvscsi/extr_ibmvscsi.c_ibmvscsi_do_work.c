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
struct ibmvscsi_host_data {int action; TYPE_1__* host; int /*<<< orphan*/  dev; int /*<<< orphan*/  request_limit; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
#define  IBMVSCSI_HOST_ACTION_NONE 131 
#define  IBMVSCSI_HOST_ACTION_REENABLE 130 
#define  IBMVSCSI_HOST_ACTION_RESET 129 
#define  IBMVSCSI_HOST_ACTION_UNBLOCK 128 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int ibmvscsi_reenable_crq_queue (int /*<<< orphan*/ *,struct ibmvscsi_host_data*) ; 
 int ibmvscsi_reset_crq_queue (int /*<<< orphan*/ *,struct ibmvscsi_host_data*) ; 
 int ibmvscsi_send_crq (struct ibmvscsi_host_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_enable_interrupts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibmvscsi_do_work(struct ibmvscsi_host_data *hostdata)
{
	unsigned long flags;
	int rc;
	char *action = "reset";

	spin_lock_irqsave(hostdata->host->host_lock, flags);
	switch (hostdata->action) {
	case IBMVSCSI_HOST_ACTION_UNBLOCK:
		rc = 0;
		break;
	case IBMVSCSI_HOST_ACTION_RESET:
		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		rc = ibmvscsi_reset_crq_queue(&hostdata->queue, hostdata);
		spin_lock_irqsave(hostdata->host->host_lock, flags);
		if (!rc)
			rc = ibmvscsi_send_crq(hostdata, 0xC001000000000000LL, 0);
		vio_enable_interrupts(to_vio_dev(hostdata->dev));
		break;
	case IBMVSCSI_HOST_ACTION_REENABLE:
		action = "enable";
		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		rc = ibmvscsi_reenable_crq_queue(&hostdata->queue, hostdata);
		spin_lock_irqsave(hostdata->host->host_lock, flags);
		if (!rc)
			rc = ibmvscsi_send_crq(hostdata, 0xC001000000000000LL, 0);
		break;
	case IBMVSCSI_HOST_ACTION_NONE:
	default:
		spin_unlock_irqrestore(hostdata->host->host_lock, flags);
		return;
	}

	hostdata->action = IBMVSCSI_HOST_ACTION_NONE;

	if (rc) {
		atomic_set(&hostdata->request_limit, -1);
		dev_err(hostdata->dev, "error after %s\n", action);
	}
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);

	scsi_unblock_requests(hostdata->host);
}