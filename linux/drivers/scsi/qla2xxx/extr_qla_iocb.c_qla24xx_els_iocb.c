#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  command_code; } ;
struct TYPE_18__ {int /*<<< orphan*/  els_code; } ;
struct TYPE_20__ {TYPE_3__ h_els; TYPE_2__ r_els; } ;
struct fc_bsg_request {TYPE_4__ rqst_data; } ;
struct els_entry_24xx {int entry_count; void* rx_len; int /*<<< orphan*/  rx_address; void* tx_len; int /*<<< orphan*/  tx_address; void* tx_byte_count; void* rx_byte_count; scalar_t__ control_flags; int /*<<< orphan*/ * port_id; int /*<<< orphan*/  opcode; void* rx_dsd_count; int /*<<< orphan*/  sof_type; int /*<<< orphan*/  vp_index; void* tx_dsd_count; void* nport_handle; int /*<<< orphan*/  handle; scalar_t__ entry_status; scalar_t__ sys_define; int /*<<< orphan*/  entry_type; } ;
struct TYPE_25__ {int /*<<< orphan*/  sg_list; int /*<<< orphan*/  payload_len; int /*<<< orphan*/  sg_cnt; } ;
struct TYPE_24__ {int /*<<< orphan*/  sg_list; int /*<<< orphan*/  payload_len; int /*<<< orphan*/  sg_cnt; } ;
struct bsg_job {TYPE_9__ reply_payload; TYPE_8__ request_payload; struct fc_bsg_request* request; } ;
struct TYPE_17__ {struct bsg_job* bsg_job; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_11__* vha; TYPE_7__* fcport; int /*<<< orphan*/  handle; TYPE_1__ u; } ;
typedef  TYPE_12__ srb_t ;
struct TYPE_21__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  area; int /*<<< orphan*/  al_pa; } ;
struct TYPE_22__ {TYPE_5__ b; } ;
struct TYPE_23__ {TYPE_6__ d_id; int /*<<< orphan*/  loop_id; } ;
struct TYPE_14__ {int /*<<< orphan*/  control_requests; } ;
struct TYPE_15__ {TYPE_10__ qla_stats; int /*<<< orphan*/  vp_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_IOCB_TYPE ; 
 int /*<<< orphan*/  EST_SOFI3 ; 
 scalar_t__ SRB_ELS_CMD_RPT ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_dma_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla24xx_els_iocb(srb_t *sp, struct els_entry_24xx *els_iocb)
{
	struct bsg_job *bsg_job = sp->u.bsg_job;
	struct fc_bsg_request *bsg_request = bsg_job->request;

        els_iocb->entry_type = ELS_IOCB_TYPE;
        els_iocb->entry_count = 1;
        els_iocb->sys_define = 0;
        els_iocb->entry_status = 0;
        els_iocb->handle = sp->handle;
        els_iocb->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	els_iocb->tx_dsd_count = cpu_to_le16(bsg_job->request_payload.sg_cnt);
	els_iocb->vp_index = sp->vha->vp_idx;
        els_iocb->sof_type = EST_SOFI3;
	els_iocb->rx_dsd_count = cpu_to_le16(bsg_job->reply_payload.sg_cnt);

	els_iocb->opcode =
	    sp->type == SRB_ELS_CMD_RPT ?
	    bsg_request->rqst_data.r_els.els_code :
	    bsg_request->rqst_data.h_els.command_code;
        els_iocb->port_id[0] = sp->fcport->d_id.b.al_pa;
        els_iocb->port_id[1] = sp->fcport->d_id.b.area;
        els_iocb->port_id[2] = sp->fcport->d_id.b.domain;
        els_iocb->control_flags = 0;
        els_iocb->rx_byte_count =
            cpu_to_le32(bsg_job->reply_payload.payload_len);
        els_iocb->tx_byte_count =
            cpu_to_le32(bsg_job->request_payload.payload_len);

	put_unaligned_le64(sg_dma_address(bsg_job->request_payload.sg_list),
			   &els_iocb->tx_address);
        els_iocb->tx_len = cpu_to_le32(sg_dma_len
            (bsg_job->request_payload.sg_list));

	put_unaligned_le64(sg_dma_address(bsg_job->reply_payload.sg_list),
			   &els_iocb->rx_address);
        els_iocb->rx_len = cpu_to_le32(sg_dma_len
            (bsg_job->reply_payload.sg_list));

	sp->vha->qla_stats.control_requests++;
}