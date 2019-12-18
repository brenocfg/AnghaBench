#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_22__ {int /*<<< orphan*/  rsp_info_len; int /*<<< orphan*/  comp_status; } ;
typedef  TYPE_8__ sts_entry_t ;
struct req_que {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  status; } ;
struct TYPE_16__ {TYPE_1__ ctels_reply; } ;
struct fc_bsg_reply {void* reply_payload_rcv_len; TYPE_2__ reply_data; } ;
struct ct_sns_rsp {int dummy; } ;
struct TYPE_17__ {void* payload_len; } ;
struct bsg_job {int reply_len; TYPE_3__ reply_payload; struct fc_bsg_reply* reply; } ;
struct TYPE_18__ {scalar_t__ rsp; } ;
struct TYPE_19__ {TYPE_4__ ctarg; } ;
struct TYPE_20__ {TYPE_5__ u; } ;
struct TYPE_21__ {TYPE_6__ iocb_cmd; struct bsg_job* bsg_job; } ;
struct TYPE_23__ {int type; int /*<<< orphan*/  (* done ) (TYPE_9__*,int) ;int /*<<< orphan*/  name; TYPE_7__ u; } ;
typedef  TYPE_9__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
typedef  int /*<<< orphan*/  ms_iocb_entry_t ;

/* Variables and functions */
 void* CS_COMPLETE ; 
 void* CS_DATA_UNDERRUN ; 
 int DID_ERROR ; 
 int DID_OK ; 
 int /*<<< orphan*/  FC_CTELS_STATUS_OK ; 
#define  SRB_CT_CMD 129 
#define  SRB_CT_PTHRU_CMD 128 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ql_dbg_async ; 
 scalar_t__ ql_dbg_buffer ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,int /*<<< orphan*/ *,int,TYPE_8__*,int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,char const*,void*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla2x00_chk_ms_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ct_sns_rsp*,int /*<<< orphan*/ ) ; 
 TYPE_9__* qla2x00_get_sp_from_handle (int /*<<< orphan*/ *,char const*,struct req_que*,TYPE_8__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*,int) ; 

__attribute__((used)) static void
qla2x00_ct_entry(scsi_qla_host_t *vha, struct req_que *req,
    sts_entry_t *pkt, int iocb_type)
{
	const char func[] = "CT_IOCB";
	const char *type;
	srb_t *sp;
	struct bsg_job *bsg_job;
	struct fc_bsg_reply *bsg_reply;
	uint16_t comp_status;
	int res = 0;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	if (!sp)
		return;

	switch (sp->type) {
	case SRB_CT_CMD:
	    bsg_job = sp->u.bsg_job;
	    bsg_reply = bsg_job->reply;

	    type = "ct pass-through";

	    comp_status = le16_to_cpu(pkt->comp_status);

	    /*
	     * return FC_CTELS_STATUS_OK and leave the decoding of the ELS/CT
	     * fc payload  to the caller
	     */
	    bsg_reply->reply_data.ctels_reply.status = FC_CTELS_STATUS_OK;
	    bsg_job->reply_len = sizeof(struct fc_bsg_reply);

	    if (comp_status != CS_COMPLETE) {
		    if (comp_status == CS_DATA_UNDERRUN) {
			    res = DID_OK << 16;
			    bsg_reply->reply_payload_rcv_len =
				le16_to_cpu(pkt->rsp_info_len);

			    ql_log(ql_log_warn, vha, 0x5048,
				"CT pass-through-%s error comp_status=0x%x total_byte=0x%x.\n",
				type, comp_status,
				bsg_reply->reply_payload_rcv_len);
		    } else {
			    ql_log(ql_log_warn, vha, 0x5049,
				"CT pass-through-%s error comp_status=0x%x.\n",
				type, comp_status);
			    res = DID_ERROR << 16;
			    bsg_reply->reply_payload_rcv_len = 0;
		    }
		    ql_dump_buffer(ql_dbg_async + ql_dbg_buffer, vha, 0x5035,
			pkt, sizeof(*pkt));
	    } else {
		    res = DID_OK << 16;
		    bsg_reply->reply_payload_rcv_len =
			bsg_job->reply_payload.payload_len;
		    bsg_job->reply_len = 0;
	    }
	    break;
	case SRB_CT_PTHRU_CMD:
	    /*
	     * borrowing sts_entry_24xx.comp_status.
	     * same location as ct_entry_24xx.comp_status
	     */
	     res = qla2x00_chk_ms_status(vha, (ms_iocb_entry_t *)pkt,
		 (struct ct_sns_rsp *)sp->u.iocb_cmd.u.ctarg.rsp,
		 sp->name);
	     break;
	}

	sp->done(sp, res);
}