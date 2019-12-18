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
struct zfcp_fsf_req {int status; int /*<<< orphan*/  completion; int /*<<< orphan*/ * data; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; int /*<<< orphan*/  abort_lock; int /*<<< orphan*/  req_list; } ;
struct scsi_cmnd {scalar_t__ host_scribble; TYPE_1__* device; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
struct TYPE_2__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int ZFCP_STATUS_COMMON_RUNNING ; 
 int ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED ; 
 int ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int fc_block_scsi_eh (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_dbf_scsi_abort (char*,struct scsi_cmnd*,struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 
 struct zfcp_fsf_req* zfcp_fsf_abort_fcp_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 struct zfcp_fsf_req* zfcp_reqlist_find (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int zfcp_scsi_eh_abort_handler(struct scsi_cmnd *scpnt)
{
	struct Scsi_Host *scsi_host = scpnt->device->host;
	struct zfcp_adapter *adapter =
		(struct zfcp_adapter *) scsi_host->hostdata[0];
	struct zfcp_fsf_req *old_req, *abrt_req;
	unsigned long flags;
	unsigned long old_reqid = (unsigned long) scpnt->host_scribble;
	int retval = SUCCESS, ret;
	int retry = 3;
	char *dbf_tag;

	/* avoid race condition between late normal completion and abort */
	write_lock_irqsave(&adapter->abort_lock, flags);

	old_req = zfcp_reqlist_find(adapter->req_list, old_reqid);
	if (!old_req) {
		write_unlock_irqrestore(&adapter->abort_lock, flags);
		zfcp_dbf_scsi_abort("abrt_or", scpnt, NULL);
		return FAILED; /* completion could be in progress */
	}
	old_req->data = NULL;

	/* don't access old fsf_req after releasing the abort_lock */
	write_unlock_irqrestore(&adapter->abort_lock, flags);

	while (retry--) {
		abrt_req = zfcp_fsf_abort_fcp_cmnd(scpnt);
		if (abrt_req)
			break;

		zfcp_dbf_scsi_abort("abrt_wt", scpnt, NULL);
		zfcp_erp_wait(adapter);
		ret = fc_block_scsi_eh(scpnt);
		if (ret) {
			zfcp_dbf_scsi_abort("abrt_bl", scpnt, NULL);
			return ret;
		}
		if (!(atomic_read(&adapter->status) &
		      ZFCP_STATUS_COMMON_RUNNING)) {
			zfcp_dbf_scsi_abort("abrt_ru", scpnt, NULL);
			return SUCCESS;
		}
	}
	if (!abrt_req) {
		zfcp_dbf_scsi_abort("abrt_ar", scpnt, NULL);
		return FAILED;
	}

	wait_for_completion(&abrt_req->completion);

	if (abrt_req->status & ZFCP_STATUS_FSFREQ_ABORTSUCCEEDED)
		dbf_tag = "abrt_ok";
	else if (abrt_req->status & ZFCP_STATUS_FSFREQ_ABORTNOTNEEDED)
		dbf_tag = "abrt_nn";
	else {
		dbf_tag = "abrt_fa";
		retval = FAILED;
	}
	zfcp_dbf_scsi_abort(dbf_tag, scpnt, abrt_req);
	zfcp_fsf_req_free(abrt_req);
	return retval;
}