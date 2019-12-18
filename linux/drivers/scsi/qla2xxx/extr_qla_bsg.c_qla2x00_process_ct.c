#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int uint16_t ;
struct qla_hw_data {TYPE_8__* pdev; } ;
struct TYPE_26__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_27__ {TYPE_5__ b; } ;
struct fc_port {int loop_id; TYPE_6__ d_id; TYPE_11__* vha; } ;
struct TYPE_24__ {int preamble_word1; int preamble_word2; int /*<<< orphan*/ * port_id; } ;
struct TYPE_25__ {TYPE_3__ h_ct; } ;
struct fc_bsg_request {TYPE_4__ rqst_data; } ;
struct TYPE_30__ {int sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct TYPE_28__ {int sg_cnt; int /*<<< orphan*/  sg_list; } ;
struct bsg_job {TYPE_9__ reply_payload; TYPE_7__ request_payload; struct fc_bsg_request* request; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_23__ {struct bsg_job* bsg_job; } ;
struct TYPE_20__ {char* name; int /*<<< orphan*/  done; int /*<<< orphan*/  free; TYPE_2__ u; int /*<<< orphan*/  iocbs; int /*<<< orphan*/  type; } ;
typedef  TYPE_10__ srb_t ;
struct TYPE_22__ {int /*<<< orphan*/  online; } ;
struct TYPE_21__ {int mgmt_svr_loop_id; TYPE_1__ flags; struct qla_hw_data* hw; } ;
typedef  TYPE_11__ scsi_qla_host_t ;
struct TYPE_29__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EAGAIN ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NPH_SNS ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_CT_CMD ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int dma_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* fc_bsg_to_shost (struct bsg_job*) ; 
 int /*<<< orphan*/  kfree (struct fc_port*) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_11__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_user ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_11__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_calc_ct_iocbs (int) ; 
 struct fc_port* qla2x00_alloc_fcport (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_bsg_job_done ; 
 int /*<<< orphan*/  qla2x00_bsg_sp_free ; 
 TYPE_10__* qla2x00_get_sp (TYPE_11__*,struct fc_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_rel_sp (TYPE_10__*) ; 
 int qla2x00_start_sp (TYPE_10__*) ; 
 TYPE_11__* shost_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int
qla2x00_process_ct(struct bsg_job *bsg_job)
{
	srb_t *sp;
	struct fc_bsg_request *bsg_request = bsg_job->request;
	struct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qla_host_t *vha = shost_priv(host);
	struct qla_hw_data *ha = vha->hw;
	int rval = (DID_ERROR << 16);
	int req_sg_cnt, rsp_sg_cnt;
	uint16_t loop_id;
	struct fc_port *fcport;
	char  *type = "FC_BSG_HST_CT";

	req_sg_cnt =
		dma_map_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
			bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	if (!req_sg_cnt) {
		ql_log(ql_log_warn, vha, 0x700f,
		    "dma_map_sg return %d for request\n", req_sg_cnt);
		rval = -ENOMEM;
		goto done;
	}

	rsp_sg_cnt = dma_map_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
	if (!rsp_sg_cnt) {
		ql_log(ql_log_warn, vha, 0x7010,
		    "dma_map_sg return %d for reply\n", rsp_sg_cnt);
		rval = -ENOMEM;
		goto done;
	}

	if ((req_sg_cnt !=  bsg_job->request_payload.sg_cnt) ||
	    (rsp_sg_cnt != bsg_job->reply_payload.sg_cnt)) {
		ql_log(ql_log_warn, vha, 0x7011,
		    "request_sg_cnt: %x dma_request_sg_cnt: %x reply_sg_cnt:%x "
		    "dma_reply_sg_cnt: %x\n", bsg_job->request_payload.sg_cnt,
		    req_sg_cnt, bsg_job->reply_payload.sg_cnt, rsp_sg_cnt);
		rval = -EAGAIN;
		goto done_unmap_sg;
	}

	if (!vha->flags.online) {
		ql_log(ql_log_warn, vha, 0x7012,
		    "Host is not online.\n");
		rval = -EIO;
		goto done_unmap_sg;
	}

	loop_id =
		(bsg_request->rqst_data.h_ct.preamble_word1 & 0xFF000000)
			>> 24;
	switch (loop_id) {
	case 0xFC:
		loop_id = cpu_to_le16(NPH_SNS);
		break;
	case 0xFA:
		loop_id = vha->mgmt_svr_loop_id;
		break;
	default:
		ql_dbg(ql_dbg_user, vha, 0x7013,
		    "Unknown loop id: %x.\n", loop_id);
		rval = -EINVAL;
		goto done_unmap_sg;
	}

	/* Allocate a dummy fcport structure, since functions preparing the
	 * IOCB and mailbox command retrieves port specific information
	 * from fcport structure. For Host based ELS commands there will be
	 * no fcport structure allocated
	 */
	fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
	if (!fcport) {
		ql_log(ql_log_warn, vha, 0x7014,
		    "Failed to allocate fcport.\n");
		rval = -ENOMEM;
		goto done_unmap_sg;
	}

	/* Initialize all required  fields of fcport */
	fcport->vha = vha;
	fcport->d_id.b.al_pa = bsg_request->rqst_data.h_ct.port_id[0];
	fcport->d_id.b.area = bsg_request->rqst_data.h_ct.port_id[1];
	fcport->d_id.b.domain = bsg_request->rqst_data.h_ct.port_id[2];
	fcport->loop_id = loop_id;

	/* Alloc SRB structure */
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp) {
		ql_log(ql_log_warn, vha, 0x7015,
		    "qla2x00_get_sp failed.\n");
		rval = -ENOMEM;
		goto done_free_fcport;
	}

	sp->type = SRB_CT_CMD;
	sp->name = "bsg_ct";
	sp->iocbs = qla24xx_calc_ct_iocbs(req_sg_cnt + rsp_sg_cnt);
	sp->u.bsg_job = bsg_job;
	sp->free = qla2x00_bsg_sp_free;
	sp->done = qla2x00_bsg_job_done;

	ql_dbg(ql_dbg_user, vha, 0x7016,
	    "bsg rqst type: %s else type: %x - "
	    "loop-id=%x portid=%02x%02x%02x.\n", type,
	    (bsg_request->rqst_data.h_ct.preamble_word2 >> 16),
	    fcport->loop_id, fcport->d_id.b.domain, fcport->d_id.b.area,
	    fcport->d_id.b.al_pa);

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0x7017,
		    "qla2x00_start_sp failed=%d.\n", rval);
		qla2x00_rel_sp(sp);
		rval = -EIO;
		goto done_free_fcport;
	}
	return rval;

done_free_fcport:
	kfree(fcport);
done_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev, bsg_job->request_payload.sg_list,
		bsg_job->request_payload.sg_cnt, DMA_TO_DEVICE);
	dma_unmap_sg(&ha->pdev->dev, bsg_job->reply_payload.sg_list,
		bsg_job->reply_payload.sg_cnt, DMA_FROM_DEVICE);
done:
	return rval;
}