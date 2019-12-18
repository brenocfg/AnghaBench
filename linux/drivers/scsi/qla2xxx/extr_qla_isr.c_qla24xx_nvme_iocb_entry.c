#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct sts_entry_24xx {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  residual_len; int /*<<< orphan*/  nvme_rsp_pyld_len; int /*<<< orphan*/  nvme_ersp_data; int /*<<< orphan*/  state_flags; int /*<<< orphan*/  comp_status; } ;
struct TYPE_13__ {int comp_status; int aen_op; int rsp_pyld_len; struct nvmefc_fcp_req* desc; } ;
struct TYPE_14__ {TYPE_4__ nvme; } ;
struct srb_iocb {TYPE_5__ u; } ;
struct req_que {int dummy; } ;
struct nvmefc_fcp_req {scalar_t__ transferred_length; scalar_t__ payload_length; scalar_t__ rspaddr; } ;
struct TYPE_10__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* done ) (TYPE_6__*,int) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  name; TYPE_3__* vha; TYPE_7__* fcport; TYPE_1__ u; } ;
typedef  TYPE_6__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_16__ {int /*<<< orphan*/  nvme_flag; int /*<<< orphan*/  vha; } ;
typedef  TYPE_7__ fc_port_t ;
struct TYPE_12__ {TYPE_2__* hw; } ;
struct TYPE_11__ {int /*<<< orphan*/  nvme_active_aen_cnt; } ;

/* Variables and functions */
#define  CS_ABORTED 134 
#define  CS_COMPLETE 133 
#define  CS_DATA_UNDERRUN 132 
#define  CS_PORT_BUSY 131 
#define  CS_PORT_LOGGED_OUT 130 
#define  CS_PORT_UNAVAILABLE 129 
#define  CS_RESET 128 
 int /*<<< orphan*/  NVME_FLAG_RESETTING ; 
 int QLA_ABORTED ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int SF_FCP_RSP_DMA ; 
 int SF_NVME_ERSP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int) ; 
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void qla24xx_nvme_iocb_entry(scsi_qla_host_t *vha, struct req_que *req,
    void *tsk, srb_t *sp)
{
	fc_port_t *fcport;
	struct srb_iocb *iocb;
	struct sts_entry_24xx *sts = (struct sts_entry_24xx *)tsk;
	uint16_t        state_flags;
	struct nvmefc_fcp_req *fd;
	uint16_t        ret = QLA_SUCCESS;
	uint16_t	comp_status = le16_to_cpu(sts->comp_status);

	iocb = &sp->u.iocb_cmd;
	fcport = sp->fcport;
	iocb->u.nvme.comp_status = comp_status;
	state_flags  = le16_to_cpu(sts->state_flags);
	fd = iocb->u.nvme.desc;

	if (unlikely(iocb->u.nvme.aen_op))
		atomic_dec(&sp->vha->hw->nvme_active_aen_cnt);

	/*
	 * State flags: Bit 6 and 0.
	 * If 0 is set, we don't care about 6.
	 * both cases resp was dma'd to host buffer
	 * if both are 0, that is good path case.
	 * if six is set and 0 is clear, we need to
	 * copy resp data from status iocb to resp buffer.
	 */
	if (!(state_flags & (SF_FCP_RSP_DMA | SF_NVME_ERSP))) {
		iocb->u.nvme.rsp_pyld_len = 0;
	} else if ((state_flags & SF_FCP_RSP_DMA)) {
		iocb->u.nvme.rsp_pyld_len = le16_to_cpu(sts->nvme_rsp_pyld_len);
	} else if (state_flags & SF_NVME_ERSP) {
		uint32_t *inbuf, *outbuf;
		uint16_t iter;

		inbuf = (uint32_t *)&sts->nvme_ersp_data;
		outbuf = (uint32_t *)fd->rspaddr;
		iocb->u.nvme.rsp_pyld_len = le16_to_cpu(sts->nvme_rsp_pyld_len);
		iter = iocb->u.nvme.rsp_pyld_len >> 2;
		for (; iter; iter--)
			*outbuf++ = swab32(*inbuf++);
	} else { /* unhandled case */
	    ql_log(ql_log_warn, fcport->vha, 0x503a,
		"NVME-%s error. Unhandled state_flags of %x\n",
		sp->name, state_flags);
	}

	fd->transferred_length = fd->payload_length -
	    le32_to_cpu(sts->residual_len);

	if (unlikely(comp_status != CS_COMPLETE))
		ql_log(ql_log_warn, fcport->vha, 0x5060,
		   "NVME-%s ERR Handling - hdl=%x status(%x) tr_len:%x resid=%x  ox_id=%x\n",
		   sp->name, sp->handle, comp_status,
		   fd->transferred_length, le32_to_cpu(sts->residual_len),
		   sts->ox_id);

	/*
	 * If transport error then Failure (HBA rejects request)
	 * otherwise transport will handle.
	 */
	switch (comp_status) {
	case CS_COMPLETE:
		break;

	case CS_RESET:
	case CS_PORT_UNAVAILABLE:
	case CS_PORT_LOGGED_OUT:
		fcport->nvme_flag |= NVME_FLAG_RESETTING;
		/* fall through */
	case CS_ABORTED:
	case CS_PORT_BUSY:
		fd->transferred_length = 0;
		iocb->u.nvme.rsp_pyld_len = 0;
		ret = QLA_ABORTED;
		break;
	case CS_DATA_UNDERRUN:
		break;
	default:
		ret = QLA_FUNCTION_FAILED;
		break;
	}
	sp->done(sp, ret);
}