#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct scsi_qla_host {int dummy; } ;
struct event_arg {int rc; TYPE_7__* sp; TYPE_8__* fcport; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* free ) (TYPE_7__*) ;int /*<<< orphan*/  name; TYPE_8__* fcport; struct scsi_qla_host* vha; } ;
typedef  TYPE_7__ srb_t ;
struct TYPE_16__ {TYPE_5__* ct_sns; } ;
struct TYPE_18__ {int /*<<< orphan*/  node_name; int /*<<< orphan*/  port_name; int /*<<< orphan*/  flags; TYPE_6__ ct_desc; } ;
typedef  TYPE_8__ fc_port_t ;
typedef  int /*<<< orphan*/  ea ;
struct TYPE_11__ {int /*<<< orphan*/ * node_name; } ;
struct TYPE_12__ {TYPE_1__ gnn_id; } ;
struct TYPE_13__ {TYPE_2__ rsp; } ;
struct TYPE_14__ {TYPE_3__ rsp; } ;
struct TYPE_15__ {TYPE_4__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct event_arg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla24xx_handle_gnnid_event (struct scsi_qla_host*,struct event_arg*) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 scalar_t__ wwn_to_u64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla2x00_async_gnnid_sp_done(srb_t *sp, int res)
{
	struct scsi_qla_host *vha = sp->vha;
	fc_port_t *fcport = sp->fcport;
	u8 *node_name = fcport->ct_desc.ct_sns->p.rsp.rsp.gnn_id.node_name;
	struct event_arg ea;
	u64 wwnn;

	fcport->flags &= ~FCF_ASYNC_SENT;
	wwnn = wwn_to_u64(node_name);
	if (wwnn)
		memcpy(fcport->node_name, node_name, WWN_SIZE);

	memset(&ea, 0, sizeof(ea));
	ea.fcport = fcport;
	ea.sp = sp;
	ea.rc = res;

	ql_dbg(ql_dbg_disc, vha, 0x204f,
	    "Async done-%s res %x, WWPN %8phC %8phC\n",
	    sp->name, res, fcport->port_name, fcport->node_name);

	qla24xx_handle_gnnid_event(vha, &ea);

	sp->free(sp);
}