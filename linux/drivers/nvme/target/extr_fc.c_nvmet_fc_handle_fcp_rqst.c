#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nvmet_fc_tgtport {TYPE_2__* pe; } ;
struct TYPE_11__ {scalar_t__ sg_cnt; int /*<<< orphan*/ * sg; scalar_t__ transfer_len; int /*<<< orphan*/  port; int /*<<< orphan*/ * cqe; int /*<<< orphan*/ * cmd; } ;
struct TYPE_12__ {int /*<<< orphan*/  cqe; } ;
struct nvme_fc_cmd_iu {int flags; int /*<<< orphan*/  sqe; int /*<<< orphan*/  data_len; } ;
struct nvmet_fc_fcp_iod {scalar_t__ io_dir; TYPE_4__ req; scalar_t__ offset; scalar_t__ data_sg_cnt; int /*<<< orphan*/ * data_sg; TYPE_3__* queue; TYPE_7__ rspiubuf; struct nvme_fc_cmd_iu cmdiubuf; TYPE_1__* fcpreq; } ;
struct TYPE_10__ {int /*<<< orphan*/  sqtail; int /*<<< orphan*/  nvme_sq; int /*<<< orphan*/  nvme_cq; } ;
struct TYPE_9__ {int /*<<< orphan*/  port; } ;
struct TYPE_8__ {int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int FCNVME_CMD_FLAGS_READ ; 
 int FCNVME_CMD_FLAGS_WRITE ; 
 int /*<<< orphan*/  NVMET_FCOP_WRITEDATA ; 
 scalar_t__ NVMET_FCP_NODATA ; 
 scalar_t__ NVMET_FCP_READ ; 
 scalar_t__ NVMET_FCP_WRITE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_is_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_fc_abort_op (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*) ; 
 int nvmet_fc_alloc_tgt_pgs (struct nvmet_fc_fcp_iod*) ; 
 int /*<<< orphan*/  nvmet_fc_tgt_fcp_ops ; 
 int /*<<< orphan*/  nvmet_fc_transfer_fcp_data (struct nvmet_fc_tgtport*,struct nvmet_fc_fcp_iod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_fc_xmt_fcp_op_done ; 
 int /*<<< orphan*/  nvmet_req_complete (TYPE_4__*,int) ; 
 int /*<<< orphan*/  nvmet_req_execute (TYPE_4__*) ; 
 int nvmet_req_init (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nvmet_fc_handle_fcp_rqst(struct nvmet_fc_tgtport *tgtport,
			struct nvmet_fc_fcp_iod *fod)
{
	struct nvme_fc_cmd_iu *cmdiu = &fod->cmdiubuf;
	u32 xfrlen = be32_to_cpu(cmdiu->data_len);
	int ret;

	/*
	 * if there is no nvmet mapping to the targetport there
	 * shouldn't be requests. just terminate them.
	 */
	if (!tgtport->pe)
		goto transport_error;

	/*
	 * Fused commands are currently not supported in the linux
	 * implementation.
	 *
	 * As such, the implementation of the FC transport does not
	 * look at the fused commands and order delivery to the upper
	 * layer until we have both based on csn.
	 */

	fod->fcpreq->done = nvmet_fc_xmt_fcp_op_done;

	if (cmdiu->flags & FCNVME_CMD_FLAGS_WRITE) {
		fod->io_dir = NVMET_FCP_WRITE;
		if (!nvme_is_write(&cmdiu->sqe))
			goto transport_error;
	} else if (cmdiu->flags & FCNVME_CMD_FLAGS_READ) {
		fod->io_dir = NVMET_FCP_READ;
		if (nvme_is_write(&cmdiu->sqe))
			goto transport_error;
	} else {
		fod->io_dir = NVMET_FCP_NODATA;
		if (xfrlen)
			goto transport_error;
	}

	fod->req.cmd = &fod->cmdiubuf.sqe;
	fod->req.cqe = &fod->rspiubuf.cqe;
	fod->req.port = tgtport->pe->port;

	/* clear any response payload */
	memset(&fod->rspiubuf, 0, sizeof(fod->rspiubuf));

	fod->data_sg = NULL;
	fod->data_sg_cnt = 0;

	ret = nvmet_req_init(&fod->req,
				&fod->queue->nvme_cq,
				&fod->queue->nvme_sq,
				&nvmet_fc_tgt_fcp_ops);
	if (!ret) {
		/* bad SQE content or invalid ctrl state */
		/* nvmet layer has already called op done to send rsp. */
		return;
	}

	fod->req.transfer_len = xfrlen;

	/* keep a running counter of tail position */
	atomic_inc(&fod->queue->sqtail);

	if (fod->req.transfer_len) {
		ret = nvmet_fc_alloc_tgt_pgs(fod);
		if (ret) {
			nvmet_req_complete(&fod->req, ret);
			return;
		}
	}
	fod->req.sg = fod->data_sg;
	fod->req.sg_cnt = fod->data_sg_cnt;
	fod->offset = 0;

	if (fod->io_dir == NVMET_FCP_WRITE) {
		/* pull the data over before invoking nvmet layer */
		nvmet_fc_transfer_fcp_data(tgtport, fod, NVMET_FCOP_WRITEDATA);
		return;
	}

	/*
	 * Reads or no data:
	 *
	 * can invoke the nvmet_layer now. If read data, cmd completion will
	 * push the data
	 */
	nvmet_req_execute(&fod->req);
	return;

transport_error:
	nvmet_fc_abort_op(tgtport, fod);
}