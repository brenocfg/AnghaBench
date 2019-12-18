#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ioctl_iocb_entry_fx00 {int result; int /*<<< orphan*/  reply_payload_rcv_len; struct qla_mt_iocb_rsp_fx00* reserved_2; int /*<<< orphan*/  seq_no; int /*<<< orphan*/  status; int /*<<< orphan*/  residuallen; int /*<<< orphan*/  dataword_r_extra; int /*<<< orphan*/  adapid; int /*<<< orphan*/  dataword_r; int /*<<< orphan*/  fw_iotcl_flags; int /*<<< orphan*/  comp_func_num; int /*<<< orphan*/  reserved_0; } ;
typedef  struct ioctl_iocb_entry_fx00 uint8_t ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  req_data; int /*<<< orphan*/  result; int /*<<< orphan*/  fw_flags; int /*<<< orphan*/  seq_number; } ;
struct TYPE_9__ {TYPE_1__ fxiocb; } ;
struct srb_iocb {TYPE_2__ u; } ;
struct req_que {int dummy; } ;
struct qla_mt_iocb_rsp_fx00 {struct ioctl_iocb_entry_fx00* reserved_3; int /*<<< orphan*/  seq_number; int /*<<< orphan*/  status; int /*<<< orphan*/  res_count; int /*<<< orphan*/  reserved_2; int /*<<< orphan*/  adapid; int /*<<< orphan*/  ioctl_data; int /*<<< orphan*/  ioctl_flags; int /*<<< orphan*/  func_type; int /*<<< orphan*/  reserved_1; } ;
struct fc_bsg_reply {int result; int /*<<< orphan*/  reply_payload_rcv_len; struct qla_mt_iocb_rsp_fx00* reserved_2; int /*<<< orphan*/  seq_no; int /*<<< orphan*/  status; int /*<<< orphan*/  residuallen; int /*<<< orphan*/  dataword_r_extra; int /*<<< orphan*/  adapid; int /*<<< orphan*/  dataword_r; int /*<<< orphan*/  fw_iotcl_flags; int /*<<< orphan*/  comp_func_num; int /*<<< orphan*/  reserved_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  payload_len; } ;
struct bsg_job {int reply_len; TYPE_4__ reply_payload; struct ioctl_iocb_entry_fx00* reply; } ;
struct TYPE_10__ {struct bsg_job* bsg_job; struct srb_iocb iocb_cmd; } ;
struct TYPE_12__ {scalar_t__ type; int /*<<< orphan*/  (* done ) (TYPE_5__*,int) ;int /*<<< orphan*/  vha; TYPE_3__ u; } ;
typedef  TYPE_5__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  fstatus ;

/* Variables and functions */
 int DID_OK ; 
 int SRB_FXDISC_RSP_DWRD_VALID ; 
 scalar_t__ SRB_FXIOCB_DCMD ; 
 int /*<<< orphan*/  memcpy (struct ioctl_iocb_entry_fx00*,struct qla_mt_iocb_rsp_fx00*,int) ; 
 int /*<<< orphan*/  memset (struct qla_mt_iocb_rsp_fx00*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ql_dbg_user ; 
 scalar_t__ ql_dbg_verbose ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,int /*<<< orphan*/ ,int,struct ioctl_iocb_entry_fx00*,int) ; 
 TYPE_5__* qla2x00_get_sp_from_handle (int /*<<< orphan*/ *,char const*,struct req_que*,struct ioctl_iocb_entry_fx00*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,int) ; 

__attribute__((used)) static void
qlafx00_ioctl_iosb_entry(scsi_qla_host_t *vha, struct req_que *req,
			 struct ioctl_iocb_entry_fx00 *pkt)
{
	const char func[] = "IOSB_IOCB";
	srb_t *sp;
	struct bsg_job *bsg_job;
	struct fc_bsg_reply *bsg_reply;
	struct srb_iocb *iocb_job;
	int res = 0;
	struct qla_mt_iocb_rsp_fx00 fstatus;
	uint8_t	*fw_sts_ptr;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	if (!sp)
		return;

	if (sp->type == SRB_FXIOCB_DCMD) {
		iocb_job = &sp->u.iocb_cmd;
		iocb_job->u.fxiocb.seq_number = pkt->seq_no;
		iocb_job->u.fxiocb.fw_flags = pkt->fw_iotcl_flags;
		iocb_job->u.fxiocb.result = pkt->status;
		if (iocb_job->u.fxiocb.flags & SRB_FXDISC_RSP_DWRD_VALID)
			iocb_job->u.fxiocb.req_data =
			    pkt->dataword_r;
	} else {
		bsg_job = sp->u.bsg_job;
		bsg_reply = bsg_job->reply;

		memset(&fstatus, 0, sizeof(struct qla_mt_iocb_rsp_fx00));

		fstatus.reserved_1 = pkt->reserved_0;
		fstatus.func_type = pkt->comp_func_num;
		fstatus.ioctl_flags = pkt->fw_iotcl_flags;
		fstatus.ioctl_data = pkt->dataword_r;
		fstatus.adapid = pkt->adapid;
		fstatus.reserved_2 = pkt->dataword_r_extra;
		fstatus.res_count = pkt->residuallen;
		fstatus.status = pkt->status;
		fstatus.seq_number = pkt->seq_no;
		memcpy(fstatus.reserved_3,
		    pkt->reserved_2, 20 * sizeof(uint8_t));

		fw_sts_ptr = bsg_job->reply + sizeof(struct fc_bsg_reply);

		memcpy(fw_sts_ptr, &fstatus, sizeof(fstatus));
		bsg_job->reply_len = sizeof(struct fc_bsg_reply) +
			sizeof(struct qla_mt_iocb_rsp_fx00) + sizeof(uint8_t);

		ql_dump_buffer(ql_dbg_user + ql_dbg_verbose,
		    sp->vha, 0x5080, pkt, sizeof(*pkt));

		ql_dump_buffer(ql_dbg_user + ql_dbg_verbose,
		    sp->vha, 0x5074,
		    fw_sts_ptr, sizeof(fstatus));

		res = bsg_reply->result = DID_OK << 16;
		bsg_reply->reply_payload_rcv_len =
		    bsg_job->reply_payload.payload_len;
	}
	sp->done(sp, res);
}