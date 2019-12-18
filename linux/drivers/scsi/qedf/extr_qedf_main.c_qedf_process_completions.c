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
typedef  int u32 ;
typedef  int u16 ;
struct status_block_e4 {int* pi_array; } ;
struct qedf_ioreq {unsigned int cpu; int /*<<< orphan*/  int_cpu; } ;
struct qedf_io_work {int /*<<< orphan*/  work; int /*<<< orphan*/ * fp; struct qedf_ctx* qedf; int /*<<< orphan*/  cqe; } ;
struct qedf_fastpath {size_t sb_id; size_t cq_num_entries; struct qedf_ctx* qedf; int /*<<< orphan*/  completions; struct qed_sb_info* sb_info; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  io_mempool; TYPE_1__* cmd_mgr; struct global_queue** global_queues; } ;
struct qed_sb_info {struct status_block_e4* sb_virt; } ;
struct global_queue {int cq_prod_idx; size_t cq_cons_idx; struct fcoe_cqe* cq; } ;
struct fcoe_cqe {int cqe_data; } ;
struct TYPE_2__ {struct qedf_ioreq* cmds; } ;

/* Variables and functions */
 int FCOE_CQE_CQE_TYPE_MASK ; 
 int FCOE_CQE_CQE_TYPE_SHIFT ; 
 int FCOE_CQE_TASK_ID_MASK ; 
 int FCOE_UNSOLIC_CQE_TYPE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t QEDF_FCOE_PARAMS_GL_RQ_PI ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_UNSOL ; 
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fcoe_cqe*,int) ; 
 struct qedf_io_work* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qedf_io_work*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedf_fp_io_handler ; 
 int /*<<< orphan*/  qedf_io_wq ; 
 int /*<<< orphan*/  qedf_process_unsol_compl (struct qedf_ctx*,size_t,struct fcoe_cqe*) ; 
 int /*<<< orphan*/  queue_work_on (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static bool qedf_process_completions(struct qedf_fastpath *fp)
{
	struct qedf_ctx *qedf = fp->qedf;
	struct qed_sb_info *sb_info = fp->sb_info;
	struct status_block_e4 *sb = sb_info->sb_virt;
	struct global_queue *que;
	u16 prod_idx;
	struct fcoe_cqe *cqe;
	struct qedf_io_work *io_work;
	int num_handled = 0;
	unsigned int cpu;
	struct qedf_ioreq *io_req = NULL;
	u16 xid;
	u16 new_cqes;
	u32 comp_type;

	/* Get the current firmware producer index */
	prod_idx = sb->pi_array[QEDF_FCOE_PARAMS_GL_RQ_PI];

	/* Get the pointer to the global CQ this completion is on */
	que = qedf->global_queues[fp->sb_id];

	/* Calculate the amount of new elements since last processing */
	new_cqes = (prod_idx >= que->cq_prod_idx) ?
	    (prod_idx - que->cq_prod_idx) :
	    0x10000 - que->cq_prod_idx + prod_idx;

	/* Save producer index */
	que->cq_prod_idx = prod_idx;

	while (new_cqes) {
		fp->completions++;
		num_handled++;
		cqe = &que->cq[que->cq_cons_idx];

		comp_type = (cqe->cqe_data >> FCOE_CQE_CQE_TYPE_SHIFT) &
		    FCOE_CQE_CQE_TYPE_MASK;

		/*
		 * Process unsolicited CQEs directly in the interrupt handler
		 * sine we need the fastpath ID
		 */
		if (comp_type == FCOE_UNSOLIC_CQE_TYPE) {
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_UNSOL,
			   "Unsolicated CQE.\n");
			qedf_process_unsol_compl(qedf, fp->sb_id, cqe);
			/*
			 * Don't add a work list item.  Increment consumer
			 * consumer index and move on.
			 */
			goto inc_idx;
		}

		xid = cqe->cqe_data & FCOE_CQE_TASK_ID_MASK;
		io_req = &qedf->cmd_mgr->cmds[xid];

		/*
		 * Figure out which percpu thread we should queue this I/O
		 * on.
		 */
		if (!io_req)
			/* If there is not io_req assocated with this CQE
			 * just queue it on CPU 0
			 */
			cpu = 0;
		else {
			cpu = io_req->cpu;
			io_req->int_cpu = smp_processor_id();
		}

		io_work = mempool_alloc(qedf->io_mempool, GFP_ATOMIC);
		if (!io_work) {
			QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate "
				   "work for I/O completion.\n");
			continue;
		}
		memset(io_work, 0, sizeof(struct qedf_io_work));

		INIT_WORK(&io_work->work, qedf_fp_io_handler);

		/* Copy contents of CQE for deferred processing */
		memcpy(&io_work->cqe, cqe, sizeof(struct fcoe_cqe));

		io_work->qedf = fp->qedf;
		io_work->fp = NULL; /* Only used for unsolicited frames */

		queue_work_on(cpu, qedf_io_wq, &io_work->work);

inc_idx:
		que->cq_cons_idx++;
		if (que->cq_cons_idx == fp->cq_num_entries)
			que->cq_cons_idx = 0;
		new_cqes--;
	}

	return true;
}