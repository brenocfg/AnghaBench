#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct sts_entry_fx00 {int comp_status; int scsi_status; size_t handle; size_t sense_len; int /*<<< orphan*/ * data; int /*<<< orphan*/  residual_len; } ;
struct scsi_cmnd {unsigned int underflow; int /*<<< orphan*/  cmnd; TYPE_1__* device; int /*<<< orphan*/  sense_buffer; } ;
struct rsp_que {int /*<<< orphan*/ * status_srb; } ;
struct req_que {size_t num_outstanding_cmds; TYPE_2__** outstanding_cmds; } ;
struct qla_hw_data {struct req_que** req_q_map; } ;
struct TYPE_16__ {scalar_t__ type; int /*<<< orphan*/  (* done ) (TYPE_2__*,int) ;TYPE_4__* fcport; } ;
typedef  TYPE_2__ srb_t ;
struct TYPE_17__ {int /*<<< orphan*/  host_no; int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
typedef  size_t int32_t ;
struct TYPE_18__ {int /*<<< orphan*/  tgt_id; int /*<<< orphan*/  vha; int /*<<< orphan*/  state; } ;
typedef  TYPE_4__ fc_port_t ;
typedef  int __le16 ;
struct TYPE_15__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
#define  CS_ABORTED 138 
#define  CS_COMPLETE 137 
 scalar_t__ CS_DATA_OVERRUN ; 
#define  CS_DATA_UNDERRUN 136 
#define  CS_INCOMPLETE 135 
#define  CS_PORT_BUSY 134 
#define  CS_PORT_CONFIG_CHG 133 
#define  CS_PORT_LOGGED_OUT 132 
#define  CS_PORT_UNAVAILABLE 131 
#define  CS_QUEUE_FULL 130 
#define  CS_RESET 129 
#define  CS_TIMEOUT 128 
 int DID_ERROR ; 
 int DID_OK ; 
 int DID_RESET ; 
 int DID_TRANSPORT_DISRUPTED ; 
 int /*<<< orphan*/  FCS_ONLINE ; 
 struct scsi_cmnd* GET_CMD_SP (TYPE_2__*) ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 int /*<<< orphan*/  IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLAFX00 (struct qla_hw_data*) ; 
 size_t LSW (size_t) ; 
 size_t MSW (size_t) ; 
 scalar_t__ SAM_STAT_BUSY ; 
 scalar_t__ SAM_STAT_TASK_SET_FULL ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 scalar_t__ SRB_TM_CMD ; 
 scalar_t__ SS_CHECK_CONDITION ; 
 scalar_t__ SS_MASK ; 
 scalar_t__ SS_RESIDUAL_OVER ; 
 scalar_t__ SS_RESIDUAL_UNDER ; 
 scalar_t__ SS_SENSE_LEN_VALID ; 
 scalar_t__ STATUS_MASK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int cpu_to_le16 (size_t) ; 
 int le16_to_cpu (int) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_3__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_io ; 
 int /*<<< orphan*/  qla2x00_mark_device_lost (int /*<<< orphan*/ ,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  qla2x00_process_completed_request (TYPE_3__*,struct req_que*,size_t) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (TYPE_3__*) ; 
 int /*<<< orphan*/  qlafx00_handle_sense (TYPE_2__*,int /*<<< orphan*/ *,size_t,size_t,struct rsp_que*,int) ; 
 int /*<<< orphan*/  qlafx00_tm_iocb_entry (TYPE_3__*,struct req_que*,void*,TYPE_2__*,int,int) ; 
 size_t scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,size_t) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void
qlafx00_status_entry(scsi_qla_host_t *vha, struct rsp_que *rsp, void *pkt)
{
	srb_t		*sp;
	fc_port_t	*fcport;
	struct scsi_cmnd *cp;
	struct sts_entry_fx00 *sts;
	__le16		comp_status;
	__le16		scsi_status;
	__le16		lscsi_status;
	int32_t		resid;
	uint32_t	sense_len, par_sense_len, rsp_info_len, resid_len,
	    fw_resid_len;
	uint8_t		*rsp_info = NULL, *sense_data = NULL;
	struct qla_hw_data *ha = vha->hw;
	uint32_t hindex, handle;
	uint16_t que;
	struct req_que *req;
	int logit = 1;
	int res = 0;

	sts = (struct sts_entry_fx00 *) pkt;

	comp_status = sts->comp_status;
	scsi_status = sts->scsi_status & cpu_to_le16((uint16_t)SS_MASK);
	hindex = sts->handle;
	handle = LSW(hindex);

	que = MSW(hindex);
	req = ha->req_q_map[que];

	/* Validate handle. */
	if (handle < req->num_outstanding_cmds)
		sp = req->outstanding_cmds[handle];
	else
		sp = NULL;

	if (sp == NULL) {
		ql_dbg(ql_dbg_io, vha, 0x3034,
		    "Invalid status handle (0x%x).\n", handle);

		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		return;
	}

	if (sp->type == SRB_TM_CMD) {
		req->outstanding_cmds[handle] = NULL;
		qlafx00_tm_iocb_entry(vha, req, pkt, sp,
		    scsi_status, comp_status);
		return;
	}

	/* Fast path completion. */
	if (comp_status == CS_COMPLETE && scsi_status == 0) {
		qla2x00_process_completed_request(vha, req, handle);
		return;
	}

	req->outstanding_cmds[handle] = NULL;
	cp = GET_CMD_SP(sp);
	if (cp == NULL) {
		ql_dbg(ql_dbg_io, vha, 0x3048,
		    "Command already returned (0x%x/%p).\n",
		    handle, sp);

		return;
	}

	lscsi_status = scsi_status & cpu_to_le16((uint16_t)STATUS_MASK);

	fcport = sp->fcport;

	sense_len = par_sense_len = rsp_info_len = resid_len =
		fw_resid_len = 0;
	if (scsi_status & cpu_to_le16((uint16_t)SS_SENSE_LEN_VALID))
		sense_len = sts->sense_len;
	if (scsi_status & cpu_to_le16(((uint16_t)SS_RESIDUAL_UNDER
	    | (uint16_t)SS_RESIDUAL_OVER)))
		resid_len = le32_to_cpu(sts->residual_len);
	if (comp_status == cpu_to_le16((uint16_t)CS_DATA_UNDERRUN))
		fw_resid_len = le32_to_cpu(sts->residual_len);
	rsp_info = sense_data = sts->data;
	par_sense_len = sizeof(sts->data);

	/* Check for overrun. */
	if (comp_status == CS_COMPLETE &&
	    scsi_status & cpu_to_le16((uint16_t)SS_RESIDUAL_OVER))
		comp_status = cpu_to_le16((uint16_t)CS_DATA_OVERRUN);

	/*
	 * Based on Host and scsi status generate status code for Linux
	 */
	switch (le16_to_cpu(comp_status)) {
	case CS_COMPLETE:
	case CS_QUEUE_FULL:
		if (scsi_status == 0) {
			res = DID_OK << 16;
			break;
		}
		if (scsi_status & cpu_to_le16(((uint16_t)SS_RESIDUAL_UNDER
		    | (uint16_t)SS_RESIDUAL_OVER))) {
			resid = resid_len;
			scsi_set_resid(cp, resid);

			if (!lscsi_status &&
			    ((unsigned)(scsi_bufflen(cp) - resid) <
			     cp->underflow)) {
				ql_dbg(ql_dbg_io, fcport->vha, 0x3050,
				    "Mid-layer underflow "
				    "detected (0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16;
				break;
			}
		}
		res = DID_OK << 16 | le16_to_cpu(lscsi_status);

		if (lscsi_status ==
		    cpu_to_le16((uint16_t)SAM_STAT_TASK_SET_FULL)) {
			ql_dbg(ql_dbg_io, fcport->vha, 0x3051,
			    "QUEUE FULL detected.\n");
			break;
		}
		logit = 0;
		if (lscsi_status != cpu_to_le16((uint16_t)SS_CHECK_CONDITION))
			break;

		memset(cp->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		if (!(scsi_status & cpu_to_le16((uint16_t)SS_SENSE_LEN_VALID)))
			break;

		qlafx00_handle_sense(sp, sense_data, par_sense_len, sense_len,
		    rsp, res);
		break;

	case CS_DATA_UNDERRUN:
		/* Use F/W calculated residual length. */
		if (IS_FWI2_CAPABLE(ha) || IS_QLAFX00(ha))
			resid = fw_resid_len;
		else
			resid = resid_len;
		scsi_set_resid(cp, resid);
		if (scsi_status & cpu_to_le16((uint16_t)SS_RESIDUAL_UNDER)) {
			if ((IS_FWI2_CAPABLE(ha) || IS_QLAFX00(ha))
			    && fw_resid_len != resid_len) {
				ql_dbg(ql_dbg_io, fcport->vha, 0x3052,
				    "Dropped frame(s) detected "
				    "(0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16 |
				    le16_to_cpu(lscsi_status);
				goto check_scsi_status;
			}

			if (!lscsi_status &&
			    ((unsigned)(scsi_bufflen(cp) - resid) <
			    cp->underflow)) {
				ql_dbg(ql_dbg_io, fcport->vha, 0x3053,
				    "Mid-layer underflow "
				    "detected (0x%x of 0x%x bytes, "
				    "cp->underflow: 0x%x).\n",
				    resid, scsi_bufflen(cp), cp->underflow);

				res = DID_ERROR << 16;
				break;
			}
		} else if (lscsi_status !=
		    cpu_to_le16((uint16_t)SAM_STAT_TASK_SET_FULL) &&
		    lscsi_status != cpu_to_le16((uint16_t)SAM_STAT_BUSY)) {
			/*
			 * scsi status of task set and busy are considered
			 * to be task not completed.
			 */

			ql_dbg(ql_dbg_io, fcport->vha, 0x3054,
			    "Dropped frame(s) detected (0x%x "
			    "of 0x%x bytes).\n", resid,
			    scsi_bufflen(cp));

			res = DID_ERROR << 16 | le16_to_cpu(lscsi_status);
			goto check_scsi_status;
		} else {
			ql_dbg(ql_dbg_io, fcport->vha, 0x3055,
			    "scsi_status: 0x%x, lscsi_status: 0x%x\n",
			    scsi_status, lscsi_status);
		}

		res = DID_OK << 16 | le16_to_cpu(lscsi_status);
		logit = 0;

check_scsi_status:
		/*
		 * Check to see if SCSI Status is non zero. If so report SCSI
		 * Status.
		 */
		if (lscsi_status != 0) {
			if (lscsi_status ==
			    cpu_to_le16((uint16_t)SAM_STAT_TASK_SET_FULL)) {
				ql_dbg(ql_dbg_io, fcport->vha, 0x3056,
				    "QUEUE FULL detected.\n");
				logit = 1;
				break;
			}
			if (lscsi_status !=
			    cpu_to_le16((uint16_t)SS_CHECK_CONDITION))
				break;

			memset(cp->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
			if (!(scsi_status &
			    cpu_to_le16((uint16_t)SS_SENSE_LEN_VALID)))
				break;

			qlafx00_handle_sense(sp, sense_data, par_sense_len,
			    sense_len, rsp, res);
		}
		break;

	case CS_PORT_LOGGED_OUT:
	case CS_PORT_CONFIG_CHG:
	case CS_PORT_BUSY:
	case CS_INCOMPLETE:
	case CS_PORT_UNAVAILABLE:
	case CS_TIMEOUT:
	case CS_RESET:

		/*
		 * We are going to have the fc class block the rport
		 * while we try to recover so instruct the mid layer
		 * to requeue until the class decides how to handle this.
		 */
		res = DID_TRANSPORT_DISRUPTED << 16;

		ql_dbg(ql_dbg_io, fcport->vha, 0x3057,
		    "Port down status: port-state=0x%x.\n",
		    atomic_read(&fcport->state));

		if (atomic_read(&fcport->state) == FCS_ONLINE)
			qla2x00_mark_device_lost(fcport->vha, fcport, 1, 1);
		break;

	case CS_ABORTED:
		res = DID_RESET << 16;
		break;

	default:
		res = DID_ERROR << 16;
		break;
	}

	if (logit)
		ql_dbg(ql_dbg_io, fcport->vha, 0x3058,
		    "FCP command status: 0x%x-0x%x (0x%x) nexus=%ld:%d:%llu "
		    "tgt_id: 0x%x lscsi_status: 0x%x cdb=%10phN len=0x%x "
		    "rsp_info=%p resid=0x%x fw_resid=0x%x sense_len=0x%x, "
		    "par_sense_len=0x%x, rsp_info_len=0x%x\n",
		    comp_status, scsi_status, res, vha->host_no,
		    cp->device->id, cp->device->lun, fcport->tgt_id,
		    lscsi_status, cp->cmnd, scsi_bufflen(cp),
		    rsp_info, resid_len, fw_resid_len, sense_len,
		    par_sense_len, rsp_info_len);

	if (rsp->status_srb == NULL)
		sp->done(sp, res);
	else
		WARN_ON_ONCE(true);
}