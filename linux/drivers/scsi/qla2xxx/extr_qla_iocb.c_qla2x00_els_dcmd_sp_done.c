#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  comp; } ;
struct TYPE_12__ {TYPE_3__ els_logo; } ;
struct srb_iocb {TYPE_4__ u; } ;
struct scsi_qla_host {int dummy; } ;
struct TYPE_13__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_14__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  name; struct scsi_qla_host* vha; TYPE_5__ u; TYPE_7__* fcport; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_9__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_10__ {TYPE_1__ b; } ;
struct TYPE_15__ {TYPE_2__ d_id; } ;
typedef  TYPE_7__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_io ; 

__attribute__((used)) static void qla2x00_els_dcmd_sp_done(srb_t *sp, int res)
{
	fc_port_t *fcport = sp->fcport;
	struct srb_iocb *lio = &sp->u.iocb_cmd;
	struct scsi_qla_host *vha = sp->vha;

	ql_dbg(ql_dbg_io, vha, 0x3072,
	    "%s hdl=%x, portid=%02x%02x%02x done\n",
	    sp->name, sp->handle, fcport->d_id.b.domain,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa);

	complete(&lio->u.els_logo.comp);
}