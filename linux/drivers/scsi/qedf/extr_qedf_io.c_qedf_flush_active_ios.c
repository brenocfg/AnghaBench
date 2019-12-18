#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qedf_rport {int lun_reset_lun; int /*<<< orphan*/  flags; int /*<<< orphan*/  num_active_ios; TYPE_4__* rport; TYPE_3__* rdata; int /*<<< orphan*/  ios_to_queue; struct qedf_ctx* qedf; } ;
struct qedf_ioreq {int lun; int /*<<< orphan*/  cmd_type; TYPE_1__* sc_cmd; int /*<<< orphan*/  flags; int /*<<< orphan*/  xid; int /*<<< orphan*/  refcount; struct qedf_rport* fcport; int /*<<< orphan*/  abts_done; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  rrq_work; int /*<<< orphan*/  state; scalar_t__ alloc; } ;
struct qedf_ctx {int /*<<< orphan*/  flush_mutex; int /*<<< orphan*/  dbg_ctx; struct qedf_cmd_mgr* cmd_mgr; } ;
struct qedf_cmd_mgr {struct qedf_ioreq* cmds; int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  scsi_target_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_7__ {TYPE_2__ ids; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int FCOE_PARAMS_NUM_TASKS ; 
 scalar_t__ QEDFC_CMD_ST_RRQ_WAIT ; 
 int /*<<< orphan*/  QEDF_ABTS ; 
 int /*<<< orphan*/  QEDF_CMD_DIRTY ; 
 int /*<<< orphan*/  QEDF_CMD_IN_ABORT ; 
 int /*<<< orphan*/  QEDF_CMD_OUTSTANDING ; 
 int /*<<< orphan*/  QEDF_ELS ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int /*<<< orphan*/  QEDF_RPORT_IN_LUN_RESET ; 
 int /*<<< orphan*/  QEDF_RPORT_IN_TARGET_RESET ; 
 int /*<<< orphan*/  QEDF_RPORT_SESSION_READY ; 
 int /*<<< orphan*/  QEDF_RPORT_UPLOADING_CONNECTION ; 
 int /*<<< orphan*/  QEDF_SCSI_CMD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedf_flush_els_req (struct qedf_ctx*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  qedf_initiate_cleanup (struct qedf_ioreq*,int) ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qedf_flush_active_ios(struct qedf_rport *fcport, int lun)
{
	struct qedf_ioreq *io_req;
	struct qedf_ctx *qedf;
	struct qedf_cmd_mgr *cmd_mgr;
	int i, rc;
	unsigned long flags;
	int flush_cnt = 0;
	int wait_cnt = 100;
	int refcount = 0;

	if (!fcport) {
		QEDF_ERR(NULL, "fcport is NULL\n");
		return;
	}

	/* Check that fcport is still offloaded */
	if (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) {
		QEDF_ERR(NULL, "fcport is no longer offloaded.\n");
		return;
	}

	qedf = fcport->qedf;

	if (!qedf) {
		QEDF_ERR(NULL, "qedf is NULL.\n");
		return;
	}

	/* Only wait for all commands to be queued in the Upload context */
	if (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags) &&
	    (lun == -1)) {
		while (atomic_read(&fcport->ios_to_queue)) {
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
				  "Waiting for %d I/Os to be queued\n",
				  atomic_read(&fcport->ios_to_queue));
			if (wait_cnt == 0) {
				QEDF_ERR(NULL,
					 "%d IOs request could not be queued\n",
					 atomic_read(&fcport->ios_to_queue));
			}
			msleep(20);
			wait_cnt--;
		}
	}

	cmd_mgr = qedf->cmd_mgr;

	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
		  "Flush active i/o's num=0x%x fcport=0x%p port_id=0x%06x scsi_id=%d.\n",
		  atomic_read(&fcport->num_active_ios), fcport,
		  fcport->rdata->ids.port_id, fcport->rport->scsi_target_id);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO, "Locking flush mutex.\n");

	mutex_lock(&qedf->flush_mutex);
	if (lun == -1) {
		set_bit(QEDF_RPORT_IN_TARGET_RESET, &fcport->flags);
	} else {
		set_bit(QEDF_RPORT_IN_LUN_RESET, &fcport->flags);
		fcport->lun_reset_lun = lun;
	}

	for (i = 0; i < FCOE_PARAMS_NUM_TASKS; i++) {
		io_req = &cmd_mgr->cmds[i];

		if (!io_req)
			continue;
		if (!io_req->fcport)
			continue;

		spin_lock_irqsave(&cmd_mgr->lock, flags);

		if (io_req->alloc) {
			if (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags)) {
				if (io_req->cmd_type == QEDF_SCSI_CMD)
					QEDF_ERR(&qedf->dbg_ctx,
						 "Allocated but not queued, xid=0x%x\n",
						 io_req->xid);
			}
			spin_unlock_irqrestore(&cmd_mgr->lock, flags);
		} else {
			spin_unlock_irqrestore(&cmd_mgr->lock, flags);
			continue;
		}

		if (io_req->fcport != fcport)
			continue;

		/* In case of ABTS, CMD_OUTSTANDING is cleared on ABTS response,
		 * but RRQ is still pending.
		 * Workaround: Within qedf_send_rrq, we check if the fcport is
		 * NULL, and we drop the ref on the io_req to clean it up.
		 */
		if (!test_bit(QEDF_CMD_OUTSTANDING, &io_req->flags)) {
			refcount = kref_read(&io_req->refcount);
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
				  "Not outstanding, xid=0x%x, cmd_type=%d refcount=%d.\n",
				  io_req->xid, io_req->cmd_type, refcount);
			/* If RRQ work has been queue, try to cancel it and
			 * free the io_req
			 */
			if (atomic_read(&io_req->state) ==
			    QEDFC_CMD_ST_RRQ_WAIT) {
				if (cancel_delayed_work_sync
				    (&io_req->rrq_work)) {
					QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
						  "Putting reference for pending RRQ work xid=0x%x.\n",
						  io_req->xid);
					/* ID: 003 */
					kref_put(&io_req->refcount,
						 qedf_release_cmd);
				}
			}
			continue;
		}

		/* Only consider flushing ELS during target reset */
		if (io_req->cmd_type == QEDF_ELS &&
		    lun == -1) {
			rc = kref_get_unless_zero(&io_req->refcount);
			if (!rc) {
				QEDF_ERR(&(qedf->dbg_ctx),
				    "Could not get kref for ELS io_req=0x%p xid=0x%x.\n",
				    io_req, io_req->xid);
				continue;
			}
			flush_cnt++;
			qedf_flush_els_req(qedf, io_req);
			/*
			 * Release the kref and go back to the top of the
			 * loop.
			 */
			goto free_cmd;
		}

		if (io_req->cmd_type == QEDF_ABTS) {
			/* ID: 004 */
			rc = kref_get_unless_zero(&io_req->refcount);
			if (!rc) {
				QEDF_ERR(&(qedf->dbg_ctx),
				    "Could not get kref for abort io_req=0x%p xid=0x%x.\n",
				    io_req, io_req->xid);
				continue;
			}
			if (lun != -1 && io_req->lun != lun)
				goto free_cmd;

			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
			    "Flushing abort xid=0x%x.\n", io_req->xid);

			if (cancel_delayed_work_sync(&io_req->rrq_work)) {
				QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
					  "Putting ref for cancelled RRQ work xid=0x%x.\n",
					  io_req->xid);
				kref_put(&io_req->refcount, qedf_release_cmd);
			}

			if (cancel_delayed_work_sync(&io_req->timeout_work)) {
				QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
					  "Putting ref for cancelled tmo work xid=0x%x.\n",
					  io_req->xid);
				qedf_initiate_cleanup(io_req, true);
				/* Notify eh_abort handler that ABTS is
				 * complete
				 */
				complete(&io_req->abts_done);
				clear_bit(QEDF_CMD_IN_ABORT, &io_req->flags);
				/* ID: 002 */
				kref_put(&io_req->refcount, qedf_release_cmd);
			}
			flush_cnt++;
			goto free_cmd;
		}

		if (!io_req->sc_cmd)
			continue;
		if (!io_req->sc_cmd->device) {
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
				  "Device backpointer NULL for sc_cmd=%p.\n",
				  io_req->sc_cmd);
			/* Put reference for non-existent scsi_cmnd */
			io_req->sc_cmd = NULL;
			qedf_initiate_cleanup(io_req, false);
			kref_put(&io_req->refcount, qedf_release_cmd);
			continue;
		}
		if (lun > -1) {
			if (io_req->lun != lun)
				continue;
		}

		/*
		 * Use kref_get_unless_zero in the unlikely case the command
		 * we're about to flush was completed in the normal SCSI path
		 */
		rc = kref_get_unless_zero(&io_req->refcount);
		if (!rc) {
			QEDF_ERR(&(qedf->dbg_ctx), "Could not get kref for "
			    "io_req=0x%p xid=0x%x\n", io_req, io_req->xid);
			continue;
		}

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Cleanup xid=0x%x.\n", io_req->xid);
		flush_cnt++;

		/* Cleanup task and return I/O mid-layer */
		qedf_initiate_cleanup(io_req, true);

free_cmd:
		kref_put(&io_req->refcount, qedf_release_cmd);	/* ID: 004 */
	}

	wait_cnt = 60;
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
		  "Flushed 0x%x I/Os, active=0x%x.\n",
		  flush_cnt, atomic_read(&fcport->num_active_ios));
	/* Only wait for all commands to complete in the Upload context */
	if (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags) &&
	    (lun == -1)) {
		while (atomic_read(&fcport->num_active_ios)) {
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO,
				  "Flushed 0x%x I/Os, active=0x%x cnt=%d.\n",
				  flush_cnt,
				  atomic_read(&fcport->num_active_ios),
				  wait_cnt);
			if (wait_cnt == 0) {
				QEDF_ERR(&qedf->dbg_ctx,
					 "Flushed %d I/Os, active=%d.\n",
					 flush_cnt,
					 atomic_read(&fcport->num_active_ios));
				for (i = 0; i < FCOE_PARAMS_NUM_TASKS; i++) {
					io_req = &cmd_mgr->cmds[i];
					if (io_req->fcport &&
					    io_req->fcport == fcport) {
						refcount =
						kref_read(&io_req->refcount);
						set_bit(QEDF_CMD_DIRTY,
							&io_req->flags);
						QEDF_ERR(&qedf->dbg_ctx,
							 "Outstanding io_req =%p xid=0x%x flags=0x%lx, sc_cmd=%p refcount=%d cmd_type=%d.\n",
							 io_req, io_req->xid,
							 io_req->flags,
							 io_req->sc_cmd,
							 refcount,
							 io_req->cmd_type);
					}
				}
				WARN_ON(1);
				break;
			}
			msleep(500);
			wait_cnt--;
		}
	}

	clear_bit(QEDF_RPORT_IN_LUN_RESET, &fcport->flags);
	clear_bit(QEDF_RPORT_IN_TARGET_RESET, &fcport->flags);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_IO, "Unlocking flush mutex.\n");
	mutex_unlock(&qedf->flush_mutex);
}