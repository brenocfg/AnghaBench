#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_7__ {int entry_type; int /*<<< orphan*/  entry_status; } ;
typedef  TYPE_1__ sts_entry_t ;
typedef  int /*<<< orphan*/  sts_cont_entry_t ;
struct TYPE_8__ {size_t handle_count; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_2__ sts22_entry_t ;
struct TYPE_9__ {size_t handle_count; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_3__ sts21_entry_t ;
struct scsi_qla_host {int dummy; } ;
struct rsp_que {int /*<<< orphan*/  req; } ;
struct mbx_entry {int dummy; } ;

/* Variables and functions */
#define  CT_IOCB_TYPE 133 
#define  MBX_IOCB_TYPE 132 
#define  STATUS_CONT_TYPE 131 
#define  STATUS_TYPE 130 
#define  STATUS_TYPE_21 129 
#define  STATUS_TYPE_22 128 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2x00_ct_entry (struct scsi_qla_host*,int /*<<< orphan*/ ,TYPE_1__*,int const) ; 
 int /*<<< orphan*/  qla2x00_mbx_iocb_entry (struct scsi_qla_host*,int /*<<< orphan*/ ,struct mbx_entry*) ; 
 int /*<<< orphan*/  qla2x00_process_completed_request (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_status_cont_entry (struct rsp_que*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_status_entry (struct scsi_qla_host*,struct rsp_que*,TYPE_1__*) ; 

__attribute__((used)) static void qla2x00_process_response_entry(struct scsi_qla_host *vha,
					   struct rsp_que *rsp,
					   sts_entry_t *pkt)
{
	sts21_entry_t *sts21_entry;
	sts22_entry_t *sts22_entry;
	uint16_t handle_cnt;
	uint16_t cnt;

	switch (pkt->entry_type) {
	case STATUS_TYPE:
		qla2x00_status_entry(vha, rsp, pkt);
		break;
	case STATUS_TYPE_21:
		sts21_entry = (sts21_entry_t *)pkt;
		handle_cnt = sts21_entry->handle_count;
		for (cnt = 0; cnt < handle_cnt; cnt++)
			qla2x00_process_completed_request(vha, rsp->req,
						sts21_entry->handle[cnt]);
		break;
	case STATUS_TYPE_22:
		sts22_entry = (sts22_entry_t *)pkt;
		handle_cnt = sts22_entry->handle_count;
		for (cnt = 0; cnt < handle_cnt; cnt++)
			qla2x00_process_completed_request(vha, rsp->req,
						sts22_entry->handle[cnt]);
		break;
	case STATUS_CONT_TYPE:
		qla2x00_status_cont_entry(rsp, (sts_cont_entry_t *)pkt);
		break;
	case MBX_IOCB_TYPE:
		qla2x00_mbx_iocb_entry(vha, rsp->req, (struct mbx_entry *)pkt);
		break;
	case CT_IOCB_TYPE:
		qla2x00_ct_entry(vha, rsp->req, pkt, CT_IOCB_TYPE);
		break;
	default:
		/* Type Not Supported. */
		ql_log(ql_log_warn, vha, 0x504a,
		       "Received unknown response pkt type %x entry status=%x.\n",
		       pkt->entry_type, pkt->entry_status);
		break;
	}
}