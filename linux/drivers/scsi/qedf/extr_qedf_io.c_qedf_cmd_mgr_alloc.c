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
typedef  scalar_t__ u16 ;
struct scsi_sgl_task_params {int dummy; } ;
struct scsi_sge {int dummy; } ;
struct qedf_ioreq {void* sgl_task_params; void* task_params; void* sense_buffer; int /*<<< orphan*/  sense_buffer_dma; int /*<<< orphan*/  rrq_work; scalar_t__ xid; int /*<<< orphan*/  timeout_work; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; TYPE_1__* pdev; int /*<<< orphan*/  num_queues; } ;
struct qedf_cmd_mgr {int /*<<< orphan*/  free_list_cnt; struct io_bdt** io_bdt_pool; struct qedf_ioreq* cmds; int /*<<< orphan*/  lock; struct qedf_ctx* qedf; } ;
struct io_bdt {void* bd_tbl; int /*<<< orphan*/  bd_tbl_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ FCOE_PARAMS_NUM_TASKS ; 
 scalar_t__ FC_XID_UNKNOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int QEDF_MAX_BDS_PER_CMD ; 
 int QEDF_SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct io_bdt* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct io_bdt** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_cmd_mgr_free (struct qedf_cmd_mgr*) ; 
 int /*<<< orphan*/  qedf_cmd_timeout ; 
 int /*<<< orphan*/  qedf_handle_rrq ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct qedf_cmd_mgr* vzalloc (int) ; 

struct qedf_cmd_mgr *qedf_cmd_mgr_alloc(struct qedf_ctx *qedf)
{
	struct qedf_cmd_mgr *cmgr;
	struct io_bdt *bdt_info;
	struct qedf_ioreq *io_req;
	u16 xid;
	int i;
	int num_ios;
	u16 min_xid = 0;
	u16 max_xid = (FCOE_PARAMS_NUM_TASKS - 1);

	/* Make sure num_queues is already set before calling this function */
	if (!qedf->num_queues) {
		QEDF_ERR(&(qedf->dbg_ctx), "num_queues is not set.\n");
		return NULL;
	}

	if (max_xid <= min_xid || max_xid == FC_XID_UNKNOWN) {
		QEDF_WARN(&(qedf->dbg_ctx), "Invalid min_xid 0x%x and "
			   "max_xid 0x%x.\n", min_xid, max_xid);
		return NULL;
	}

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "min xid 0x%x, max xid "
		   "0x%x.\n", min_xid, max_xid);

	num_ios = max_xid - min_xid + 1;

	cmgr = vzalloc(sizeof(struct qedf_cmd_mgr));
	if (!cmgr) {
		QEDF_WARN(&(qedf->dbg_ctx), "Failed to alloc cmd mgr.\n");
		return NULL;
	}

	cmgr->qedf = qedf;
	spin_lock_init(&cmgr->lock);

	/*
	 * Initialize I/O request fields.
	 */
	xid = 0;

	for (i = 0; i < num_ios; i++) {
		io_req = &cmgr->cmds[i];
		INIT_DELAYED_WORK(&io_req->timeout_work, qedf_cmd_timeout);

		io_req->xid = xid++;

		INIT_DELAYED_WORK(&io_req->rrq_work, qedf_handle_rrq);

		/* Allocate DMA memory to hold sense buffer */
		io_req->sense_buffer = dma_alloc_coherent(&qedf->pdev->dev,
		    QEDF_SCSI_SENSE_BUFFERSIZE, &io_req->sense_buffer_dma,
		    GFP_KERNEL);
		if (!io_req->sense_buffer) {
			QEDF_ERR(&qedf->dbg_ctx,
				 "Failed to alloc sense buffer.\n");
			goto mem_err;
		}

		/* Allocate task parameters to pass to f/w init funcions */
		io_req->task_params = kzalloc(sizeof(*io_req->task_params),
					      GFP_KERNEL);
		if (!io_req->task_params) {
			QEDF_ERR(&(qedf->dbg_ctx),
				 "Failed to allocate task_params for xid=0x%x\n",
				 i);
			goto mem_err;
		}

		/*
		 * Allocate scatter/gather list info to pass to f/w init
		 * functions.
		 */
		io_req->sgl_task_params = kzalloc(
		    sizeof(struct scsi_sgl_task_params), GFP_KERNEL);
		if (!io_req->sgl_task_params) {
			QEDF_ERR(&(qedf->dbg_ctx),
				 "Failed to allocate sgl_task_params for xid=0x%x\n",
				 i);
			goto mem_err;
		}
	}

	/* Allocate pool of io_bdts - one for each qedf_ioreq */
	cmgr->io_bdt_pool = kmalloc_array(num_ios, sizeof(struct io_bdt *),
	    GFP_KERNEL);

	if (!cmgr->io_bdt_pool) {
		QEDF_WARN(&(qedf->dbg_ctx), "Failed to alloc io_bdt_pool.\n");
		goto mem_err;
	}

	for (i = 0; i < num_ios; i++) {
		cmgr->io_bdt_pool[i] = kmalloc(sizeof(struct io_bdt),
		    GFP_KERNEL);
		if (!cmgr->io_bdt_pool[i]) {
			QEDF_WARN(&(qedf->dbg_ctx),
				  "Failed to alloc io_bdt_pool[%d].\n", i);
			goto mem_err;
		}
	}

	for (i = 0; i < num_ios; i++) {
		bdt_info = cmgr->io_bdt_pool[i];
		bdt_info->bd_tbl = dma_alloc_coherent(&qedf->pdev->dev,
		    QEDF_MAX_BDS_PER_CMD * sizeof(struct scsi_sge),
		    &bdt_info->bd_tbl_dma, GFP_KERNEL);
		if (!bdt_info->bd_tbl) {
			QEDF_WARN(&(qedf->dbg_ctx),
				  "Failed to alloc bdt_tbl[%d].\n", i);
			goto mem_err;
		}
	}
	atomic_set(&cmgr->free_list_cnt, num_ios);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
	    "cmgr->free_list_cnt=%d.\n",
	    atomic_read(&cmgr->free_list_cnt));

	return cmgr;

mem_err:
	qedf_cmd_mgr_free(cmgr);
	return NULL;
}