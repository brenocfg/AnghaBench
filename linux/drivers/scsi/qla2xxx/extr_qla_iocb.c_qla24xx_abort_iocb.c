#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  req_que_no; int /*<<< orphan*/  cmd_hndl; } ;
struct TYPE_17__ {TYPE_6__ abt; } ;
struct srb_iocb {TYPE_7__ u; } ;
struct req_que {int /*<<< orphan*/  id; } ;
struct abort_entry_24xx {int entry_count; void* req_que_no; int /*<<< orphan*/  vp_index; void* handle_to_abort; int /*<<< orphan*/ * port_id; void* nport_handle; void* handle; int /*<<< orphan*/  entry_type; } ;
struct TYPE_11__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_18__ {TYPE_5__* fcport; int /*<<< orphan*/  handle; TYPE_2__* qpair; TYPE_9__* vha; TYPE_1__ u; } ;
typedef  TYPE_8__ srb_t ;
struct TYPE_19__ {int /*<<< orphan*/  vp_idx; } ;
typedef  TYPE_9__ scsi_qla_host_t ;
struct TYPE_13__ {int /*<<< orphan*/  domain; int /*<<< orphan*/  area; int /*<<< orphan*/  al_pa; } ;
struct TYPE_14__ {TYPE_3__ b; } ;
struct TYPE_15__ {TYPE_4__ d_id; int /*<<< orphan*/  loop_id; } ;
struct TYPE_12__ {struct req_que* req; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_IOCB_TYPE ; 
 int /*<<< orphan*/  MAKE_HANDLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct abort_entry_24xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
qla24xx_abort_iocb(srb_t *sp, struct abort_entry_24xx *abt_iocb)
{
	struct srb_iocb *aio = &sp->u.iocb_cmd;
	scsi_qla_host_t *vha = sp->vha;
	struct req_que *req = sp->qpair->req;

	memset(abt_iocb, 0, sizeof(struct abort_entry_24xx));
	abt_iocb->entry_type = ABORT_IOCB_TYPE;
	abt_iocb->entry_count = 1;
	abt_iocb->handle = cpu_to_le32(MAKE_HANDLE(req->id, sp->handle));
	if (sp->fcport) {
		abt_iocb->nport_handle = cpu_to_le16(sp->fcport->loop_id);
		abt_iocb->port_id[0] = sp->fcport->d_id.b.al_pa;
		abt_iocb->port_id[1] = sp->fcport->d_id.b.area;
		abt_iocb->port_id[2] = sp->fcport->d_id.b.domain;
	}
	abt_iocb->handle_to_abort =
	    cpu_to_le32(MAKE_HANDLE(aio->u.abt.req_que_no,
				    aio->u.abt.cmd_hndl));
	abt_iocb->vp_index = vha->vp_idx;
	abt_iocb->req_que_no = cpu_to_le16(aio->u.abt.req_que_no);
	/* Send the command to the firmware */
	wmb();
}